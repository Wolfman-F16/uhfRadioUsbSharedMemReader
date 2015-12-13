/*
 * uhfRadio.h
 *
 *  Created on: 29.09.2012
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2011 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef UHFRADIO_H_
#define UHFRADIO_H_

#include <inttypes.h>

#define VENDOR_ID 	0x16c0
#define PRODUCT_ID	0x27db
#define PRODUCT_NAME 	"UHF-Radio"

#define USB_DATA_TX 							0x0d

int convert(uint16_t buffer[2], char *freq, char *chan);
int convert(uint16_t pBuffer[2], uint32_t pFreq, uint32_t pChan);

#endif /* UHFRADIO_H_ */
