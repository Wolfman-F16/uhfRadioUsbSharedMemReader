/*
 * pilotLogbook.c
 *
 *  Created on: Apr 16, 2016
 *      Author: wolfgang
 */
#include <inttypes>
#include <stdio>
#include <string>
#include <fstream>

#include "ErrorCodes.h"

#define UHF_CHANNELS    20u
#define BUFFER_SZ       64u

const std::string m_sFileName = "Viper.ini";

uint32_t uhfPresetFrequencies[UHF_CHANNELS];


uint8_t readLogbookFrequencies() {
  std::fstream pFile;
  char *pLineBuffer = new char[BUFFER_SZ];
  uint8_t uhfChannel = 0;

  /* get filepath */
  // ask command line argument
  /* open file */
  pFile.open(m_sFileName.c_str(), fstream:in);
  if(pFile.is_open()) {
    std::string sString;
    while(pFile.good()) {
      pFile.getline(pLineBuffer, BUFFER_SZ-1);
      sString = pLineBuffer;
      if(sString.find("[RADIO]") == 0) {
        /* read uhf frequencies */
        while((uhfChannel < 20) && pFile.good()) {
          pFile.getline(pLineBuffer, BUFFER_SZ-1);
          sString = pLineBuffer;
          sString = sString.substr(sString.find_first_of("=")+1, sString.size());
          uhfPresetFrequencies[uhfChannel] = atoi(sString.c_str());
          uhfChannel++;
          printf("found UHF PRESET %d Frequency %d\r\n", uhfChannel, uhfPresetFrequencies[uhfChannel-1]);
        }
      }
    }
  } else {
    delete pLineBuffer;
    return ERROR_FILE_NOT_FOUND;
  }
  delete pLineBuffer;
  pFile.close();

  return ERROR_OK;
}

uint8_t sendUhfPresetFrequencies(CAppSerial *pAppSerial) {
  uint32_t uhfChannel;
  uint8_t errorCode;

  if(pAppSerial == 0) {
    return ERROR_INVALID_PARAMETER;
  }

  for(uhfChannel = 1; uhfChannel <= UHF_CHANNELS; uhfChannel++) {

    errorCode = pAppSerial->sendData(uhfPresetFrequencies[uhfChannel-1], uhfChannel);
    if (errorCode != ERROR_OK)
    {
      return errorCode;
    } else
    {
      return ERROR_OK;
    }
  }

  return ERROR_OK;
}
