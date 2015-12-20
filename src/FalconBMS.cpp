/*
 * FalconBMS.cpp
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
/*
  FalconBMS.cpp : This is one of three files comprising class FalconSMR
  the others are FalconSMRGetter.cpp and FalconSMRGetterGUI.cpp
  create
  init
  destroy
*/
#include "FalconSMR.h"


/**
creates a file mapping
\return handle to file mapping (aka shared memory)
*/
HANDLE FalconSMR::createBms(void)
{
  SetLastError(0); /* clear last error */
  hFlightDataBms = CreateFileMapping(INVALID_HANDLE_VALUE,
                                  NULL,
                                  PAGE_READWRITE,
                                  0,
                                  sizeof(FlightDataBMS),
                                  BMS_MAP_NAME);

  if (GetLastError() != ERROR_SUCCESS) {
    Log::getInstance()->debug("New BMS shared memory mapping not created...\n");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
      Log::getInstance()->debug("Falcon 4 BMS is running\n");
      return hFlightDataBms;
    } else {
	  CloseHandle(hFlightData);
      hFlightData = NULL;
      cData = new unsigned char[200];
      sprintf((char*)cData, "Error code: %d\n", GetLastError() );
      Log::getInstance()->error((char*)cData);
      delete cData;
      cData = NULL;
    }
    return NULL;
  }
  
  return hFlightDataBms;
}

/**
inits a file mapping. opens it and maps it to view.
\return error code
*/
uint32_t FalconSMR::initBms (void)
{
  uint32_t errVal = ERROR_OK;
  
  BmsFlightDataMap = OpenFileMapping(FILE_MAP_READ, true, BMS_MAP_NAME);

  if (BmsFlightDataMap != NULL)  // check if we have a valid mapping
  {
    Log::getInstance()->debug("BMS Shared memory mapping opened successful\n");

    flightDataBms = (FlightDataBMS*) MapViewOfFile(BmsFlightDataMap, FILE_MAP_READ, 0, 0, 0);

    if (flightDataBms != NULL) // check to see if we have a valid view
    {
      
      Log::getInstance()->debug("BMS Shared memory data is ready\n");
    } else {
      // do exception handling here
      Log::getInstance()->debug("BMS Shared memory mapping failed. Could not read shared memory\n");
      errVal = 2;
    }
  } else {
    Log::getInstance()->debug("Could not open BMS shared memory\n");
    errVal = ERROR_DATA;
  }

  return errVal;
}

/**
destroys file mapping
\return error code
*/
uint32_t FalconSMR::destroyBms (void)
{
  if (hFlightDataBms) {
	  CloseHandle(hFlightDataBms);
  }
  if (flightDataBms)
  {
    UnmapViewOfFile(flightDataBms);
    flightDataBms = NULL;
  }
  CloseHandle(BmsFlightDataMap);

  return 0;
}
