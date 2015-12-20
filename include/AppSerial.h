/*
 * AppSerial.h
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#ifndef APPSERIAL_H_
#define APPSERIAL_H_

#include <inttypes.h>
#include "Application.h"
#include "uhfRadio.h"
#include "usb.h"

class CAppSerial {
public:
  CAppSerial();
  virtual ~CAppSerial();

  bool setup();
  int32_t sendData(uint32_t , uint32_t );

private:
  usb_dev_handle *devUhfRadio = 0;

};


#endif /* APPSERIAL_H_ */
