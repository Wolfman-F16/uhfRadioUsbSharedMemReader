/*
 * AppSerial.h
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef LOG_H
#define LOG_H

#include <iostream>                          //cout 
#include <ostream>                           //ostream (<<) 
#include <fstream>                           //ofstream
#include <sstream>                           //stringstream

#include <time.h>
#include <cstdio>

using namespace std;

enum LogLevel
{
  DISABLED,
  DEBUG_LEVEL,
  INFO_LEVEL,
  WARN_LEVEL,
  ERROR_LEVEL
};

/*
provides logging functions
*/
class Log
{
public:
  //no public constructor!
  // destructor
  virtual ~Log();

  // methods
  static Log*     getInstance(void);                    //the singleton getInstance
  void            setLogger(const string & sFileName);
  static void     setFilter(LogLevel eLevel);
  static LogLevel getFilter(void);
  void            debug(const string & sString);        //log to file
  void            info(const string & sString);         //log to file
  void            warn(const string & sString);         //log to file
  void            error(const string & sString);        //log to file
  void            clearLogFile(void);

//no public constructor:
protected:
  // constructor
  Log();

private:
  // members
  static LogLevel m_eMinLevel;  //minimum log level
  ofstream        m_logFile;
  string          m_sFileName;
  static Log    * m_instance;

  // methods
  void        log(const string & sMessage, const string & sLevel);
  string      getTimeStamp();

};

#endif /* LOG_H */

