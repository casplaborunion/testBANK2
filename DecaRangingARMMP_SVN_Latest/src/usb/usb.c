// -------------------------------------------------------------------------------------------------------------------
//
//  File: main.c -
//
//  Copyright 2011 (c) DecaWave Ltd, Dublin, Ireland.
//
//  All rights reserved.
//
//  Author: Zoran Skrba, March 2012
//
// -------------------------------------------------------------------------------------------------------------------

/* Includes */
#include "compiler.h"
#include "port.h"

#include "instance.h"
#include "deca_types.h"
#include "deca_spi.h"

#include "usbd_cdc_core.h"
#include "usbd_usr.h"
#include "usb_conf.h"
#include "usbd_desc.h"
#include "usbd_cdc_vcp.h"

/** @defgroup USB_VCP_Private_Variables
  * @{
  */

#ifdef USB_OTG_HS_INTERNAL_DMA_ENABLED
  #if defined ( __ICCARM__ ) /*!< IAR Compiler */
    #pragma data_alignment=4
  #endif
#endif /* USB_OTG_HS_INTERNAL_DMA_ENABLED */

__ALIGN_BEGIN USB_OTG_CORE_HANDLE    USB_OTG_dev __ALIGN_END ;

#define SOFTWARE_VER_STRINGUSB "EVB1000 USB2SPI 2.0"


typedef enum applicationModes{STAND_ALONE, USB_TO_SPI, USB_PRINT_ONLY, NUM_APP_MODES} APP_MODE;

int application_mode = STAND_ALONE;
int localSPIspeed = -1;

//USB to SPI data buffers
int local_buff_length = 0;
uint8_t local_buff[10000];
uint16_t local_buff_offset = 0;
int tx_buff_length = 0;
uint8_t tx_buff[10000];
int local_have_data = 0;

extern uint32_t APP_Rx_length;

void configSPIspeed(int high)
{
	if(localSPIspeed != high)
	{
		localSPIspeed = high;

		if(high)
			SPI_ConfigFastRate(SPI_BaudRatePrescaler_4);  //max SPI
		else
			SPI_ConfigFastRate(SPI_BaudRatePrescaler_16);  //max SPI before PLLs configured is ~4M
	}
}
#pragma GCC optimize ("O3")
int process_usbmessage(void)
{
	int result = 0;
	switch(application_mode)
	{
		case STAND_ALONE:
		{
			if(local_buff_length == 5)
			{
				//d (from "deca")
				if((local_buff[0] == 100) && (result == 0)) //d (from "deca")
				{
					if(local_buff[4] == 63)
					{
						int i = sizeof(SOFTWARE_VER_STRINGUSB);
						//change mode to  USB_TO_SPI and send a reply "y"
						tx_buff[0] = 121;
						memcpy(&tx_buff[1], SOFTWARE_VER_STRINGUSB, i);
						tx_buff[i+2] = 0;
						tx_buff_length = i + 2;
						application_mode = USB_TO_SPI;
						result = 2;
						//led_off(LED_ALL);
						led_on(LED_PC7); //turn on LED to indicate connection to PC application
					}
				}
			}
		}
		break;


		case USB_TO_SPI:
		{
			//first byte specifies the SPI speed and SPI read/write operation
			//bit 0 = 1 for write, 0 for read
			//bit 1 = 1 for high speed, 0 for low speed

			//<STX>   <ETX>
			//
			//to read from the device (e.g. 4 bytes), total length is = 1 + 1 + length_of_command (2) + length_of_data_to_read (2) + header length (1/2) + 1
			//
			//to write to the device (e.g. 4 bytes),  total length is = 1 + 1 + length_of_command (2) + length_of_data_to_write (2) + header length (1/2) + data length + 1
			//
			//LBS comes first:   0x2, 0x2, 0x7, 0x0, 0x04, 0x00, 0x3

			if(local_buff_length)
			{
				//0x2 = STX - start of SPI transaction data
				if(local_buff[0] == 0x2)
				{
					//configure SPI speed
					configSPIspeed(((local_buff[1]>>1) & 0x1));

					if((local_buff[1] & 0x1) == 0) //SPI read
					{
						int msglength = local_buff[2] + (local_buff[3]<<8);
						int datalength = local_buff[4] + (local_buff[5]<<8);

						//led_on(LED_PC6);
						tx_buff[0] = 0x2;
						tx_buff[datalength+2] = 0x3;

						//max data we can read in a single SPI transaction is 4093 as the USB/VCP tx buffer is only 4096 bytes long
						if((local_buff[msglength-1] != 0x3) || (datalength > 4093))
						{
							tx_buff[1] = 0x1; // if no ETX (0x3) indicate error
						}
						else
						{
							// do the read from the SPI
							readfromspi(msglength-7, &local_buff[6], datalength, &tx_buff[2]);  // result is stored in the buffer

							tx_buff[1] = 0x0; // no error
						}

						tx_buff_length = datalength + 3;
						result = 2;
					}

					if((local_buff[1] & 0x1) == 1) //SPI write
					{
						int msglength = local_buff[2] + (local_buff[3]<<8);
						int datalength = local_buff[4] + (local_buff[5]<<8);
						int headerlength = msglength - 7 - datalength;

						if(local_buff_length == msglength) //we got the whole message (sent from the PC)
						{
							local_buff_offset = 0;

							led_off(LED_PC6);
							tx_buff[0] = 0x2;
							tx_buff[2] = 0x3;
	
							if(local_buff[msglength-1] != 0x3)
							{
								tx_buff[1] = 0x1; // if no ETX (0x3) indicate error
							}
							else
							{
								// do the write to the SPI
								writetospi(headerlength, &local_buff[6], datalength, &local_buff[6+headerlength]);  // result is stored in the buffer
	
								tx_buff[1] = 0x0; // no error
							}
	
							tx_buff_length = 3;
							result = 2;
						}
						else //wait for the whole message
						{
							led_on(LED_PC6);
						}
					}
				}

				if((local_buff[0] == 100) && (result == 0)) //d (from "deca")
				{
					if(local_buff[4] == 63)
					{
						int i = sizeof(SOFTWARE_VER_STRINGUSB);
						//change mode to  USB_TO_SPI and send a reply "y"
						tx_buff[0] = 121;
						memcpy(&tx_buff[1], SOFTWARE_VER_STRINGUSB, i);
						tx_buff[i+2] = 0;
						tx_buff_length = i + 2;
						application_mode = USB_TO_SPI;
						result = 2;
						//led_off(LED_ALL);
						led_on(LED_PC7); //turn on LED to indicate connection to PC application
					}

				}

				if((local_buff[0] == 114) && (result == 0)) //r - flush the USB buffers...
				{
					DCD_EP_Flush(&USB_OTG_dev, CDC_IN_EP);
					result = 0;
				}
			}
		}
		break;

		case USB_PRINT_ONLY:
			if(local_buff_length)
			{
				//d (from "deca")
				if((local_buff[0] == 100) && (result == 0)) //d (from "deca")
				{
					if(local_buff[4] == 63)
					{
						int i = sizeof(SOFTWARE_VER_STRINGUSB);
						//change mode to  USB_TO_SPI and send a reply "n"
						tx_buff[0] = 110;
						memcpy(&tx_buff[1], SOFTWARE_VER_STRINGUSB, i);
						tx_buff[i+2] = 0;
						tx_buff_length = i + 2;
						result = 2;
						//led_off(LED_ALL);
						//led_on(LED_PC7); //turn on LED to indicate connection to PC application
					}
				}
			}
			break;

		default:
			break;
	}

	return result;
}
#pragma GCC optimize ("O3")
void send_usbmessage(uint8 *string, int len)
{
	if(local_have_data == 0)
	{
		memcpy(&tx_buff[0], string, len);
		tx_buff[len] = '\r';
		tx_buff[len+1] = '\n';
		tx_buff[len+1] = 0;
		tx_buff_length = len + 2;

		local_have_data = 2;
	}
}
/**
**===========================================================================
**
**  Abstract: main program
**
**===========================================================================
*/

void usb_printconfig(void)
{
	application_mode = USB_PRINT_ONLY;
}


int usb_init(void)
{
	uint32 devID = 0;

	memset(local_buff, 10000, 0);
	led_off(LED_ALL); //to display error....

	// enable the USB functionality

	#ifdef USE_USB_OTG_HS
	USBD_Init(&USB_OTG_dev,USB_OTG_HS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
	#else
	USBD_Init(&USB_OTG_dev,USB_OTG_FS_CORE_ID,&USR_desc,&USBD_CDC_cb,&USR_cb);
	#endif

    SPI_ConfigFastRate(SPI_BaudRatePrescaler_16);  //max SPI before PLLs configured is ~4M
    localSPIspeed = 0;

    //this is called here to wake up the device (i.e. if it was in sleep mode before the restart)
	port_SPIx_clear_chip_select();	//CS low
	Sleep(1);	//200 us to wake up then waits 5ms for DW1000 XTAL to stabilise
	port_SPIx_set_chip_select();  //CS high
	Sleep(5);

    devID = dwt_readdevid() ;
    if(DWT_DEVICE_ID != devID)
    {
        // SPI not working or Unsupported Device ID
    	led_on(LED_ALL); //to display error....
    }

    return 0;
}

static int i = 0;
void usb_run(void)
{

	// My assumption is we will get a trigger when USB is connected to a host and we can support host command to disable ARM
	// control of DW1000 (e.g. running DecaRanging) and operates as USB to SPI converter for PC DecaRanging Applications.
	// (If this does not work we use a switch on an IO port to select between USB2SPI pass-through and native-DecaRanging functions.

    // Do nothing in foreground -- allow USB application to run, I guess on the basis of USB interrupts?

    // loop forever, doing nothing except giving a bit of a LED flash every so often
    {
    	//if(application_mode == STAND_ALONE)
		{
    		i++ ;
			if (i == 0x0D0000) led_on(LED_PC8);
			if (i == 0x0E0000) led_off(LED_PC8);
			if (i == 0x0F0000) led_on(LED_PC8);
			if (i == 0x100000)
			{
				led_off(LED_PC8);
				i = 0;
			}
		}

        if(local_have_data == 1)
        {
        	local_have_data = process_usbmessage();
        }
        else if(local_have_data == 2) //have data to send (over USB)
        {
        		VCP_DataTx(tx_buff, tx_buff_length);
			local_have_data = 0;
        }

	  }
}



