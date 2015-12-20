/*
 * FalconSMR.cpp
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
/*
 FalconSMR.cpp : This is one of three files comprising class FalconSMR
 the others are FalconSMRGetter.cpp and FalconSMRGetterGUI.cpp
 create
 init
 destroy
 */
#include "FalconSMR.h"

/**
 constructor. initializes reader
 */
FalconSMR::FalconSMR() {
  status = -1;
  flightDataF4 = NULL;
  hFlightData = NULL;
  FlightDataMap = NULL;
  flightDataBms = NULL;
  hFlightDataBms = NULL;
  BmsFlightDataMap = NULL;
  cValue = NULL;
  cData = NULL;
}

/**
 destructor. calls destroy
 */
FalconSMR::~FalconSMR() {
  destroyF4();
  destroyBms();
}

/**
 creates a file mapping
 \return handle to file mapping (aka shared memory)
 */
HANDLE FalconSMR::createF4(void) {
  SetLastError(0);
  hFlightData = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READONLY, 0,
      sizeof(FlightData), MAP_NAME);

  if (GetLastError() != ERROR_SUCCESS) {
    Log::getInstance()->debug("New shared memory mapping not created...\n");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
      Log::getInstance()->debug("Shared memory area already exists (F4)\n");
      return hFlightData;
    } else {
      CloseHandle(hFlightData);
      hFlightData = NULL;
      cData = new unsigned char[200];
      sprintf((char*) cData, "Error code: %d\n", GetLastError());
      Log::getInstance()->error((char*) cData);
      delete cData;
      cData = NULL;
    }
    return NULL;
  }

  return hFlightData;
}

/**
 inits a file mapping. opens it and maps it to view.
 \return error code
 */
uint32_t FalconSMR::initF4(void) {
  uint32_t errVal = ERROR_OK;

  FlightDataMap = OpenFileMapping(FILE_MAP_READ, true, MAP_NAME);

  if (FlightDataMap != NULL) // check if we have a valid mapping
  {
    Log::getInstance()->debug("Shared memory mapping opened successful\n");

    flightDataF4 = (FlightData*) MapViewOfFile(FlightDataMap, FILE_MAP_READ, 0,
        0, 0);

    if (flightDataF4 != NULL) // check to see if we have a valid view
    {
      printf("Shared memory data ready. ");
      switch (flightDataF4->iFalconVersion) {
      case FALCON_AF_VERSION:
        printf("Detected Allied Force\n");
        break;
      case FALCON_BMS_432_VERSION:
        printf("Detected BMS 4.32\n");
        break;
      case FALCON_BMS_433_VERSION:
        printf("Detected BMS 4.33\n");
        break;
      default:
        printf("Falcon 4.0 not running\n");
        errVal = -1;
        break;
      }
      if (errVal == ERROR_OK) {
        Log::getInstance()->debug("Shared memory data is ready\n");
      }
    } else {
      // do exception handling here
      Log::getInstance()->debug(
          "Shared memory mapping failed. Could not read shared memory\n");
      errVal = 2;
    }
  } else {
    Log::getInstance()->debug("Could not open shared memory\n");
    errVal = ERROR_DATA;
  }

  return errVal;
}

/**
 destroys file mapping
 \return error code
 */
uint32_t FalconSMR::destroyF4(void) {
  if (hFlightData) {
    try {
      CloseHandle(hFlightData);
    } catch (...) {
      Log::getInstance()->error("close handle crashed on hFlightData\n");
    }
  }
  if (flightDataF4) {
    UnmapViewOfFile(flightDataF4);
    flightDataF4 = NULL;
  }
  CloseHandle(FlightDataMap);

  return 0;
}

/**
 * synchronize with shared memory.
 *
 * Wait for Falcon 4.0 to start if necessary.
 */
int32_t FalconSMR::sync() {
  // create mapping
  Log::getInstance()->debug("create shared memory mapping...\n");
  if (createF4() == NULL) {
    destroyF4();
    Log::getInstance()->debug("error creating shared memory mapping\n");
    cData = new unsigned char[300];
    sprintf((char*) cData, "returning with error code %d\n", status);
    Log::getInstance()->error((char*) cData);
    delete cData;
    cData = NULL;
    return ERROR_DATA;
  }

  // open link
  status = initF4();
  if (status != ERROR_OK) {
    destroyF4();
    Log::getInstance()->debug("shared memory not ready\n");
    return status;
  }

  if (flightDataF4->iFalconVersion == FALCON_BMS_432_VERSION) {
    if (createBms() == NULL) {
      destroyBms();
      Log::getInstance()->debug(
          "error creating BMS 4.32 shared memory mapping\n");
      return ERROR_DATA;
    } else {
      status = initBms();
    }
  }

  if (flightDataF4->iFalconVersion == FALCON_BMS_433_VERSION) {
    if (createBms() == NULL) {
      destroyBms();
      Log::getInstance()->debug(
          "error creating BMS 4.33 shared memory mapping\n");
      return ERROR_DATA;
    } else {
      status = initBms();
    }
  }
  return status;
}
