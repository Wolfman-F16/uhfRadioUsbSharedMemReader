/*
 * Application.h
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef APPLICATION_H
#define APPLICATION_H

#include <cmath>
#include "ErrorCodes.h"
#include "FalconSMR.h"

#define  STATIC

/// FalconSMR application, derived from windows application class
class CApplication
{
public:
  // constructor, destructor
  CApplication();
  virtual ~CApplication();
  // members
  FalconSMR  *m_pFalconSMR;

  // methods
  virtual BOOL InitInstance();

protected:
  uint32_t errorIndex;

private:
  // members
  bool  bSingleShotFlag;
};

#endif // APPLICATION_H
