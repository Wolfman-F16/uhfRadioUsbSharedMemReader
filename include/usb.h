/*
 * usb.h
 *
 *  Created on: 29.09.2012
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2011 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef USB_H_
#define USB_H_

#include <inttypes.h>
#include <lusb0_usb.h>
#include "string"

typedef enum  {
	ENGLISH = 0x0409
} LOCALE_e;

usb_dev_handle* USB_OpenDevice(uint16_t, uint16_t, std::string );
int USB_SendData(usb_dev_handle *, uint8_t , uint16_t *);
int USB_SendLargeData(usb_dev_handle * , uint8_t , char * );

#endif /* USB_H_ */
