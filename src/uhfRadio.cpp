/*
 * uhfRadio.cpp
 *
 *  Created on: 29.09.2012
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2011 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include <inttypes.h>
#include <cstdlib>
#include <cstring>

#include <cstdio>

#include "uhfRadio.h"

/**
 * converts frequency string and channel string to UHF-Radio data format
 */
int convert(uint16_t pBuffer[2], char *pFreq, char *pChan) {

  if (strlen(pFreq) != 6)
  {
    return -1;
  }
  if (strlen(pChan) != 2)
  {
    return -1;
  }
  pBuffer[0] = (pFreq[0] << 4) & 0x0030;
  pBuffer[0] |= pFreq[1] & 0x0F;
  pBuffer[0] |= (pFreq[2] << 11) & 0x7800;
  pBuffer[0] |= (pFreq[3] << 7) & 0x0700;
  pBuffer[0] |= (pFreq[3] << 6) & 0x0040;
  pBuffer[1] = 0;
  if (pFreq[4] > '2')
  {
    pBuffer[1] = 0x0040;
  }
  if (pFreq[5] == '5')
  {
    pBuffer[1] |= 0x0020;
  }
  pBuffer[1] |= atoi(pChan) & 0x001F;

  return 0;
}

/**
 * converts frequency string and channel string to UHF-Radio data format
 */
int convert(uint16_t pBuffer[2], uint32_t pFreq, uint32_t pChan) {
  uint8_t dig1;
  uint8_t dig2;
  uint8_t dig3;
  uint8_t dig4;
  uint8_t dig5;

  if (pFreq == 0)
  {
    dig1 = 8;
    dig2 = 8;
    dig3 = 8;
    dig4 = 8;
    dig5 = 8;
  } else if (pChan == 0)
  {
    return -1;
  } else
  {
    dig1 = (pFreq / 100000);
    dig2 = (pFreq / 10000) % 10;
    dig3 = (pFreq / 1000) % 10;
    dig4 = (pFreq / 100) % 10;
    dig5 = (pFreq) % 100;
  }
  pBuffer[0] = (dig1 << 4) & 0x0030;
  pBuffer[0] |= dig2 & 0x0F;
  pBuffer[0] |= (dig3 << 11) & 0x7800;
  pBuffer[0] |= (dig4 << 7) & 0x0700;
  pBuffer[0] |= (dig4 << 6) & 0x0040;

  pBuffer[1] = 0;
  if (dig5 > 25)
  {
    pBuffer[1] = 0x0040;
  }
  if ((dig5 % 10) == 5)
  {
    pBuffer[1] |= 0x0020;
  }
  pBuffer[1] |= pChan & 0x001F;

  printf("\nConverting %d to %d %d %d %d %d = %04x %04x\r", pFreq, dig1, dig2,
      dig3, dig4, dig5, pBuffer[0], pBuffer[1]);

  return 0;
}
