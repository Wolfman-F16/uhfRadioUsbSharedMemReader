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
  int prepareData(unsigned char*, unsigned int*, bool);

protected:
  int errorIndex;
  bool blinkStateOn[32];

private:
  // members
  const unsigned short FREQ_4HZ = 125;
  bool  bSingleShotFlag;
  // methods
  unsigned char reverseByte(unsigned char x);
  unsigned short reverse16(unsigned short x);
  unsigned int getPowerOffData(void);

// left console
  int prepareLeftConsole(FalconSMR *, unsigned int &, bool);
  int getLeftConsoleIndication(FalconSMR *, unsigned int &);
  int getCmds(FalconSMR *, unsigned int &, bool);
  int getUhf(FalconSMR *, unsigned int &);
  int getTacan(FalconSMR *, unsigned int &);
  
// center console
  int prepareCenterConsole(FalconSMR *, unsigned int &, bool);
  int getCenterConsoleIndication(FalconSMR *, unsigned int &);
  int getAirspeed(FalconSMR *, unsigned int &);
  int getAltimeter(FalconSMR *, unsigned int &);
  int getAoa(FalconSMR *, unsigned int &);
  int getAdi(FalconSMR *, unsigned int &);
  int getVvi(FalconSMR *, unsigned int &);
  int getHsi(FalconSMR *, unsigned int &);
  int getDed(FalconSMR *, unsigned int &, bool);
  int getFuelFlow(FalconSMR *, unsigned int &);
  int getOilPressure(FalconSMR *, unsigned int &);
  int getNozzlePos(FalconSMR *, unsigned int &);
  int getRpm(FalconSMR *, unsigned int &);
  int getFtit(FalconSMR *, unsigned int &);
  int getRwr(FalconSMR *, unsigned int &);

  // right console
  int prepareRightConsole(FalconSMR *, unsigned int &, bool, bool);
  int getFaultLights(FalconSMR *, unsigned int &);
  int getPfl(FalconSMR *, unsigned int &, bool);
  int getEpuFuel(FalconSMR *, unsigned int &);
  int getCompass(FalconSMR *, unsigned int &);
  int getFuel(FalconSMR *, unsigned int &);
  int getCabinPressure(FalconSMR *, unsigned int &);
  int getClock(FalconSMR *, unsigned int &, bool );
};

#endif // APPLICATION_H
