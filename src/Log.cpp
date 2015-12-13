/*
 * Log.cpp
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#include "log.h"

// static stuff
LogLevel Log::m_eMinLevel = INFO_LEVEL;
Log *Log::m_instance = 0;

/**
constructor, clearing member m_sFileName.
*/
Log::Log()
{
  //protected
  m_sFileName.erase();
}

/**
brief empty destructor
*/
Log::~Log()
{
  // file is closed on every write, so no file handle is open at his point in program
}

/**
creates new instance, if m_instance is 0
\return Pointer to Log instance
*/
Log* Log::getInstance()
{
  if ( m_instance == 0 )
  {
    m_instance = new Log();

  }
  return m_instance;
}

/**
sets logger by specifying log file.
\param[in] sFileName file name of log file including path.
*/
void Log::setLogger(const string & sFileName)
{
  m_sFileName = sFileName;
}

/**
writes argument as debug output to log file.
\param[in] sMessage debug text
*/
void Log::debug(const string & sMessage)
{
  if (m_eMinLevel < 2)
  {
    log(sMessage,"[DEBUG]");  // second parameter should be defined in the header
  }
}

/**
writes argument as info output to log file.
\param[in] sMessage info text
*/
void Log::info(const string & sMessage)
{
  if (m_eMinLevel < 3)
  {
    log(sMessage,"[INFO] ");  // second parameter should be defined in the header
  }
}

/**
writes argument as warn output to log file.
\param[in] sMessage warn text
*/
void Log::warn(const string & sMessage)
{
  if (m_eMinLevel < 4)
  {
    log(sMessage,"[WARN] ");  // second parameter should be defined in the header
  }
}

/**
writes argument as error output to log file.
\param[in] sMessage error text
*/
void Log::error(const string & sMessage)
{
  log(sMessage,"[ERROR]");    // second parameter should be defined in the header
}

/**
writes argument to log file.
\param[in] sMessage log text
\param[in] sLevel log level
*/
void Log::log(const string & sMessage, const string & sLevel)
{
  if ((m_sFileName.size() > 0) && (m_eMinLevel != 0))
  {
    m_logFile.open (m_sFileName.c_str(), ios::out | ios::app);
    m_logFile << sLevel << " " << getTimeStamp() << " > " << sMessage.c_str();
    m_logFile.close();
  }
}

/**
sets minimum log level. if invalid argument is passed, logging is disabled
param[in] sLevel log level. ERROR, WARN, INFO, DEBUG
*/
void Log::setFilter(LogLevel eNewLevel)
{
  m_eMinLevel = eNewLevel;
}

/**
returns current minimum log level.
\return error, warn, info, debug, disabled
*/
LogLevel Log::getFilter()
{
  return m_eMinLevel;
}

/**
clears log file
*/
void Log::clearLogFile()
{
  if (m_sFileName.size()>0)
  {
    m_logFile.open (m_sFileName.c_str(), ios::out);
    m_logFile.close();
  }
}

/**
gets time stamp.
\return string of format is DD.MM.YY HH:MM:SS
*/
string Log::getTimeStamp()
{
  string sTime;
  char cBuffer[80];
  struct tm * timeData;
  time_t strTime;

  time(&strTime);                       // get time
  timeData = localtime(&strTime);
  strftime(cBuffer, 80, "%d.%m.%Y %H:%M:%S", timeData);   // format time

  sTime = cBuffer;

  //getTime(&currentTime);
  return sTime;
}
