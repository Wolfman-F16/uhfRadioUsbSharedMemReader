/*
 * ErrorCodes.h
 *
 * definition of error codes used as return value
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef ERROR_OK
#define ERROR_OK                  0
#endif
#ifndef ERROR_DATA
#define ERROR_DATA                1
#endif
#ifndef ERROR_NO_NEW_DATA
#define ERROR_NO_NEW_DATA         6
#endif
#ifndef ERROR_CONFIG
#define ERROR_CONFIG              4
#endif
#ifndef ERROR_FILE_NOT_FOUND
#define ERROR_FILE_NOT_FOUND      2 // redundant with winerror.h
#endif
#ifndef ERROR_POWER_OFF
#define ERROR_POWER_OFF           111
#endif
