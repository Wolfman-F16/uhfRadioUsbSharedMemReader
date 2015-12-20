/*
 * FalconSMR.h
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef FALCON_SMR_H
#define FALCON_SMR_H

#include <windows.h>
#include <cstdio>
#include <string>
#include <ctime>
#include <inttypes.h>
#include "FlightData2.h"
#include "Log.h"
#include "ErrorCodes.h"

/**
pojo for shared memory data
*/
class FalconSMR
{
public:
  /// constructor , destructor
  FalconSMR();

  virtual ~FalconSMR();

  /// members
  int32_t status;
  uint8_t *cData;     // contains the data to send via serial interface

  /// methods
  int32_t	sync();

  uint32_t	getFalconVersion();

  // BMS additional data
  uint32_t  getBupUhfFreq();
  uint32_t	getBupUhfChan();

private:
  /// members
  HANDLE          hFlightData;    // handle to flight data
  void           *FlightDataMap;  // pointer for holding flight data mapping
  FlightData     *flightDataF4;     // the class containing data
  
  HANDLE          hFlightDataBms; // handle to BMS flight data
  void           *BmsFlightDataMap;  // pointer for holding BMS flight data mapping
  FlightDataBMS  *flightDataBms;  // the other class containing BMS specific data

  uint8_t        *cValue;         // holds return value from getters. used as temporary storage

  /// methods
  HANDLE  	createF4  (void);
  uint32_t  initF4    (void);
  uint32_t	destroyF4 (void);
  HANDLE  	createBms (void);
  uint32_t	initBms   (void);
  uint32_t	destroyBms(void);
};

#endif // FALCON_SMR_H
