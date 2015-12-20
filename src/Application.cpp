/*
 * Application.cpp
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

/*
 InitInstance
 reverseByte
 reverse16
 transmitData
 */
#include "Application.h"

/**
 constructor
 */
CApplication::CApplication() {
  m_pFalconSMR = NULL;
  bSingleShotFlag = true;
}

/**
 destructor, deleting pointer pSerialComm and pFalconSMR
 */
CApplication::~CApplication() {
  delete m_pFalconSMR;
}

/**
 init instance. gets serial port config data, shared memory data and initialises gui
 \retVal true if successful
 */
BOOL CApplication::InitInstance() {
  uint32_t error = ERROR_DATA;
  // init memory access
  m_pFalconSMR = new FalconSMR;

  if (m_pFalconSMR->sync() != ERROR_OK) {

    while (error != ERROR_OK) {
      Log::getInstance()->debug("trying again...\n");

      Sleep(5000); // wait 5 seconds before next try
      error = m_pFalconSMR->sync();

      if (m_pFalconSMR->getFalconVersion() == 0) {
        Log::getInstance()->debug("failed\n");
        error = ERROR_DATA;
      }
    }
  }

  return TRUE;
}

