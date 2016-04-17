/*
 * pilotLogbook.c
 *
 *  Created on: Apr 16, 2016
 *      Author: wolfgang
 */
#include <inttypes.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>

#include "ErrorCodes.h"
#include "AppSerial.h"

#define UHF_CHANNELS    20u
#define BUFFER_SZ       128u

const std::string m_sFileName = "Viper.ini";
const std::string m_sKey = "[Radio]";

uint32_t uhfPresetFrequencies[UHF_CHANNELS];


uint8_t readLogbookFrequencies() {
  std::fstream pFile;
  char *pLineBuffer = new char[BUFFER_SZ];
  uint8_t uhfChannel = 0;

  /* get filepath */
  // ask command line argument
  printf("Reading %s\n",m_sFileName.c_str());
  /* open file */
  pFile.open(m_sFileName.c_str(), std::fstream::in);
  if(pFile.is_open()) {
    std::string sString;
    while(pFile.good()) {
      pFile.getline(pLineBuffer, BUFFER_SZ-1);
      sString = pLineBuffer;
      if(sString.find(m_sKey) == 0) {
        /* read uhf frequencies */
    	  printf("found frequency section\n");
        while((uhfChannel < 20) && pFile.good()) {
          pFile.getline(pLineBuffer, BUFFER_SZ-1);
          sString = pLineBuffer;
          sString = sString.substr(sString.find_first_of("=")+1, sString.size());
          uhfPresetFrequencies[uhfChannel] = atoi(sString.c_str());
          uhfChannel++;
          printf("found at UHF PRESET %d Frequency %d\r\n", uhfChannel, uhfPresetFrequencies[uhfChannel-1]);
        }
      }
#if DEBUG > 0
      else { printf("miss: %s\n",pLineBuffer);}
#endif
    }
  } else {
    delete pLineBuffer;
    return ERROR_FILE_NOT_FOUND;
  }
  delete pLineBuffer;
  pFile.close();

  return ERROR_OK;
}

uint32_t sendUhfPresetFrequencies(CAppSerial *pAppSerial) {
  uint32_t uhfChannel;
  uint32_t iRetVal = ERROR_OK;
  uint16_t value[2];

  if(pAppSerial == 0) {
    return ERROR_INVALID_PARAMETER;
  }

  for(uhfChannel = 1; uhfChannel <= UHF_CHANNELS; uhfChannel++) {

	    if(convert(value, uhfPresetFrequencies[uhfChannel-1], uhfChannel)) {
	      Log::getInstance()->error("converting input data failed\n");
	    } else {
	      value[1] |= 0xEE00;
	      iRetVal = pAppSerial->sendData(value);
	    }

  }

  return iRetVal;
}
