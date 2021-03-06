/*
 * FalconSMRBupUhf.cpp
 *
 *  Created on: Dez 12, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include "FalconSMR.h"

/*
getter methods of FalconSMR class for use with GUI. placed here as separate file for
clarity's sake
*/


/// return Backup UHF Frequency
uint32_t FalconSMR::getBupUhfFreq()
{
	return flightDataBms->BupUhfFreq;
}

/// return Backup UHF Channel
uint32_t FalconSMR::getBupUhfChan()
{
	return flightDataBms->BupUhfPreset;
}

/// returns falcon version
uint32_t FalconSMR::getFalconVersion()
{
  if(flightDataF4) {
    return flightDataF4->iFalconVersion;
  }
  return 0;
}

