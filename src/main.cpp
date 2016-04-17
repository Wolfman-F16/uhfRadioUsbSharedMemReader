/*
 * main.cpp
 *
 *  Created on: Nov 14, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */

#include <cstdlib>
#include <cstdio>
#include "ErrorCodes.h"
#include "Application.h"
#include "AppSerial.h"

// global variables
CApplication m_pAppFalcon;
CAppSerial m_pAppSerial;
uint32_t TIMEOUT_VALUE = 20; // init refresh rate [ms]

extern uint8_t readLogbookFrequencies(void);
extern uint8_t sendUhfPresetFrequencies(CAppSerial *pAppSerial);

/**
 writes data to serial data buffer (cData)
 */
uint32_t txData() {
  uint32_t errorCode = ERROR_NO_NEW_DATA;
  static uint32_t chan = 33;
  static uint32_t freq = 1;
  uint8_t dirtyFlag = 0;
  uint16_t value[2];

  if (chan != m_pAppFalcon.m_pFalconSMR->getBupUhfChan())
  {
    chan = m_pAppFalcon.m_pFalconSMR->getBupUhfChan();
    dirtyFlag = 1;
  }
  if (freq != m_pAppFalcon.m_pFalconSMR->getBupUhfFreq())
  {
    freq = m_pAppFalcon.m_pFalconSMR->getBupUhfFreq();
    dirtyFlag = 1;
  }
  if (dirtyFlag)
  {
	    if(convert(value, freq, chan)) {
	      Log::getInstance()->error("converting input data failed\n");
	    } else {
	      errorCode = m_pAppSerial.sendData(value);
	    }
    if (errorCode != ERROR_OK)
    {
      return errorCode;
    } else
    {
      return ERROR_OK;
    }
  }
  return errorCode;
}

/*
 * main
 */
int main(int argc, char **argv) {
  uint32_t retVal;

  printf(
      "Falcon 4.0 / BMS 4.33 Shared Memory Reader\n\rARC-164 UHF Radio - %s %s\n\r",
      __DATE__, __TIME__);
  if (m_pAppSerial.setup() != TRUE)
  {
    Log::getInstance()->error("setup failed. USB device not found.\n");
    return ERROR_CONFIG;
  }
  if(readLogbookFrequencies()) {
    Log::getInstance()->error("could not find Pilot Logbook\n");
    printf("no pilot logbook found\n");
  }
  sendUhfPresetFrequencies(&m_pAppSerial);
  if (m_pAppFalcon.InitInstance() != TRUE)
  {
    Log::getInstance()->debug("could not initialize application\n");
    return ERROR_DATA;
  }

  printf("transmitting @%dms ...\n", TIMEOUT_VALUE);

  while (1)
  {
    Sleep(TIMEOUT_VALUE); /* sleep 100 ms */

    retVal = txData();
    if (retVal)
    {
      if (retVal != ERROR_NO_NEW_DATA)
      {
        printf("\rError: %d\r", retVal);
        /* don't want to quit just bc. data is invalid */
      }
    }
  }
}
