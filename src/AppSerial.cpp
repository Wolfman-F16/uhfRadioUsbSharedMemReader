/*
 * AppCenter.cpp
 *
 *  Created on: Nov 28, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include <AppSerial.h>

CAppSerial::CAppSerial() {
  devUhfRadio = NULL;
}

CAppSerial::~CAppSerial() {
  if(devUhfRadio) {
    usb_close(devUhfRadio);
  }
}

int CAppSerial::setup() {
  int bResult = -1;
  char charBuffer[50];
  // init logging
  Log::getInstance()->setFilter(DEBUG_LEVEL);
  Log::getInstance()->setLogger("f4.uhf-radio.log.txt");

  devUhfRadio = USB_OpenDevice(VENDOR_ID, PRODUCT_ID, PRODUCT_NAME);

  if (!devUhfRadio) {
    Log::getInstance()->error("Failed to open USB device\n");
    Log::getInstance()->info("Note: UHF Radio uses VendorId 0x16C0 and ProductId 0x27DB\ninstall-filter install --device=USB\Vid_16c0.Pid_27db.Rev_0100\n");
    return FALSE;
  } else {
    printf("Established connection to UHF-Radio\n");
  }

  return TRUE;
}

int CAppSerial::sendData(const uint32_t freq, uint32_t chan) {
  int iRetVal = -1;
  uint16_t value[2];

  if(devUhfRadio) {
    if(convert(value, freq, chan)) {
      Log::getInstance()->error("converting input data failed\n");
    } else {
      iRetVal = USB_SendData(devUhfRadio,USB_DATA_TX, value);
    }
  }
  return iRetVal;
}
