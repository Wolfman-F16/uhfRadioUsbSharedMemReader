/*
 * usb.cpp
 *
 *  Created on: 29.09.2012
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2011 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include <cstdio>

#include "usb.h"

/* Used to get descriptor strings for device identification */
static int32_t usbGetDescriptorString(usb_dev_handle *pDevice,
		uint32_t pIdx,
		int32_t pLangId,
		uint8_t *pBuffer,
		uint32_t pBuflen) {
	uint8_t buffer[256];
	int32_t rval;
	uint32_t i;

	// make standard request GET_DESCRIPTOR, type string and given index
	// (e.g. dev->iProduct)
	rval = usb_control_msg(
			pDevice,
				USB_TYPE_STANDARD | USB_RECIP_DEVICE | USB_ENDPOINT_IN,
				USB_REQ_GET_DESCRIPTOR,
				(USB_DT_STRING << 8) + pIdx,
				pLangId,
				(char*)buffer,
				sizeof(buffer),
				1000);

	if (rval < 0) // error
		return rval;

	// rval should be bytes read, but buffer[0] contains the actual response size
	if ((uint8_t) buffer[0] < rval)
		rval = (uint8_t) buffer[0]; // string is shorter than bytes read

	if (buffer[1] != USB_DT_STRING) // second byte is the data type
		return 0; // invalid return type

	// we're dealing with UTF-16LE here so actual chars is half of rval,
	// and index 0 doesn't count
	rval /= 2;

	/* lossy conversion to ISO Latin1 */
	for (i = 1; i < (uint8_t)rval && i < pBuflen; i++) {
		if (buffer[2 * i + 1] == 0)
			pBuffer[i - 1] = buffer[2 * i];
		else
			pBuffer[i - 1] = '?'; /* outside of ISO Latin1 range */
	}
	pBuffer[i - 1] = 0;

	return i - 1;
}

/**
 * opens usb device. device handle must be closed after finishing operation!
 */
usb_dev_handle* USB_OpenDevice(uint16_t pVendorId, uint16_t pProductId, std::string pProductName) {
	int32_t result;
	struct usb_bus *bus = 0;
	struct usb_device *dev = 0;
	usb_dev_handle *device = 0;

	uint8_t buffer[64];

	usb_init();
#if _DEBUG_
	usb_set_debug(3); //set verbosity level to 3, as suggested in the documentation
#endif
	result = usb_find_busses();
	if (result < 0) {
		printf("Error: No Busses found %d\n", result);;
		return 0;
	}
	result = usb_find_devices();
	if (result < 0) {
		printf("Error: Get Devices failed.\n");;
	}
	printf("%d Devices found.\n", result );

	bus = usb_get_busses();
	if (bus == 0) {
		printf("Error: Failed to get busses\n");;
		return 0;
	}

	while (bus) {
#if _DEBUG_
		printf("%s at location %d\n", bus->dirname , bus->location );
#endif
		dev = bus->devices;
		if (dev == 0) {
			printf("Error: Failed to get devices\n\nCheck that UHF-Radio is connected or\n");
			printf("maybe no filter installed for device UHF-Radio\n\n");
			return 0;
			/* note> UHF Radio uses VendorId 0x16C0 and ProductId 0x27DB 				*/
			/* install-filter install --device=USB\Vid_16c0.Pid_27db.Rev_0100 	*/
		} else {
			while (dev) {
				// IDENTIFY DEVICE
				device = usb_open(dev);
				usbGetDescriptorString(device, dev->descriptor.iProduct, ENGLISH, buffer, sizeof(buffer));
				printf("Product name:\t%s\n", buffer );
				if (strncmp(pProductName.c_str(), (char*)buffer, sizeof(buffer)) == 0) {
					return device;
				} else {
					usb_close(device);
				}
				dev = dev->next;
			}
		}
		bus = bus->next;
	}
	return 0;
}

/**
 * sends data via usb. Max 4Byte
 */
uint32_t USB_SendData(usb_dev_handle *pDevice, uint8_t pRequest, uint16_t pValue[2]) {
	int32_t r;
	uint8_t buffer[16];

	r = usb_control_msg(
			pDevice,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_ENDPOINT_IN,
				pRequest,
				pValue[0],
				pValue[1],
				(char*)buffer,
				sizeof(buffer),
				5000);
	if (r < 0) {
		return 1;
	}
//	Log::getInstance()->debug("Response '%s'\t(%d bytes)\n", buffer, r);

	return 0;
}

/**
 * sends data via usb. Data must be null terminated!
 */
uint32_t USB_SendLargeData(usb_dev_handle *pDevice, uint8_t pRequest, uint8_t *pBuffer) {
	int32_t r;

	r = usb_control_msg(
			pDevice,
				USB_TYPE_CLASS | USB_RECIP_INTERFACE | USB_ENDPOINT_OUT,
				pRequest,
				0,
				0,
				(char*)pBuffer,
				sizeof(pBuffer)+1,
				5000);
	if (r < 0) {
		return 1;
	}
	printf("Response '%s'\t(%d bytes)\n", pBuffer, r);

	return 0;
}
