/*
 * Application.cpp
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef _FLIGHT_DATA2_H
#define _FLIGHT_DATA2_H

#define MAP_NAME "FalconSharedMemoryArea"
#define BMS_MAP_NAME "FalconSharedMemoryArea2"

#define FALCON_BMS_432_VERSION 110
#define FALCON_BMS_433_VERSION 117
#define FALCON_BMS_435_VERSION 118
#define FALCON_AF_VERSION      111

/*
 makes shared memory data accessible
 */
class FlightData {

public:
	uint32_t reserved[59];
	uint8_t reserved2[20][26];
	uint32_t reserved3[6 + (7*40)];
	uint32_t iFalconVersion;         // Falcon Version
};

class FlightDataBMS {
public:
	uint32_t reserved[11];
	uint16_t reserved2;

	uint32_t BupUhfPreset;	// BUP UHF channel preset
	uint32_t BupUhfFreq;		// BUP UHF channel frequency
	uint32_t reserved4[5];
	uint32_t VersionNum;		// Version of FlightData2 mem area
};

#endif  //_FLIGHT_DATA2_H
