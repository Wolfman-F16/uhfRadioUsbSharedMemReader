/*
 * FalconSMR.h
 *
 *  Created on: Dez 10, 2015
 *      Author: Wolfgang Engelhard
 *
 * Copyright: (c) 2015 by Wolfgang Engelhard
 * License: GNU GPL v2 (see License.txt)
 */
#ifndef FALCON_SMR_H
#define FALCON_SMR_H

#include <windows.h>
#include <cstdio>
#include <string>
#include <ctime>
#include <inttypes.h>
#include "FlightData2.h"
#include "Log.h"
#include "ErrorCodes.h"

/**
pojo for shared memory data
*/
class FalconSMR
{
public:
  /// constructor , destructor
  FalconSMR();

  virtual ~FalconSMR();

  /// members
  int status;
  unsigned char *cData;     // contains the data to send via serial interface

  /// methods
  int   sync();

  int   dumpSharedMem(void);
  int   dumpData(unsigned int );

  bool  getMasterCautionOn();     // left eyebrow
  bool  getTerrainFollowFault();  // left eyebrow
  bool  getOxyLowOn();            // OBS aka Marker Beacon on center console
  bool  getEquipHot();            // HUD ??
  bool  getHudShootOn();
  bool  getWeightOnWheels();      // not displayed
  bool  getEngineFireOn();        // right eyebrow
  bool  getConfigurationFault();  // fault board
  bool  getHydraulicsFault();     // right eyebrow
  bool  getFlcsAbcdOn();          // right eyebrow
  bool  getDualFault();           // right eyebrow and fault board
  bool  getCanopyPressureFault();
  bool  getObs();
  bool  getTLConfigFault();       // takeoff landing
  bool  getAoaAboveOn();
  bool  getAoaOnGlideSlopeOn();
  bool  getAoaBelowOn();
  bool  getRefuelRdyOn();
  bool  getRefuelAirOn();         // air refueling
  bool  getRefuelDisconnectOn();
  bool  getFltCntrlSysFault();    // fault board
  bool  getLeFlapsFault();
  bool  getEngineFault();         // fault board
  bool  getOverheat();            // fault board
  bool  getHudFuelLow();          // HUD ??
  bool  getAvionicsFault();       // fault board
  bool  getRadarAltimeterFault(); // fault board
  bool  getIffFault();            // fault board
  bool  getEcmCautionLightOn();   // fault board (i know it contradicts xflight block 50 printout)
  bool  getHookFault();           // fault board
  bool  getNwsFail();             // fault board
  bool  getCabinPressureFault();  // fault board
  bool  getAutoPilotOn();         // not AF
  bool  getTfRadarStby();
  bool  getHandOffOn();           // TWP
  bool  getLaunchOn();
  bool  getPriorityModeOn();
  bool  getNavalOn();
  bool  getUnknownOn();
  bool  getTargetSeparationOn();
  bool  getGoOn();
  bool  getNoGoOn();
  bool  getDegradeOn();
  bool  getCmdsRdy();
  bool  getChaffLow();
  bool  getFlareLow();
  bool  getAuxSearchOn();        // TWA
  bool  getAuxActiveOn();
  bool  getAuxLowOn();
  bool  getAuxPower();
  bool  getEcmPower();
  bool  getEcmFault();          // fault board (check with above EcmCautionLight)
  bool  getFwdFuelLow();        // fault board
  bool  getAftFuelLow();        // fault board
  bool  getEpuOn();
  bool  getJfsOn();
  bool  getSecOn();          // secondary engine fault; fault board
  bool  getOxygenLow();        // fault board
  bool  getProbeHeatOn();      // fault board
  bool  getSeatArmingFault();    // fault board
  bool  getBuc();          // fault board
  bool  getFuelOilHot();      // fault board
  bool  getAntiSkidFault();      // fault board
  bool  getTfRadarEngaged();
  bool  getGearInTransition();
  bool  getEngineOn();
  bool  getFlcsPmgOn();        // ELEC
  bool  getMainGeneratorOn();
  bool  getStbyGeneratorOn();
  bool  getEpuGeneratorOn();
  bool  getEpuPmgOn();
  bool  getToFlcsOn();
  bool  getFlcsRelayOn();
  bool  getBatteryFailure();
  bool  getHydrazineOn();
  bool  getAirOn();
  bool  getElectricFailure();    // fault board
  bool  getLefFault();
  bool  getPowerOff();				// no AF ff.
  bool  getFlcsBitRunOn();
  bool  getHudLockLightOn();
  bool  getFlcsBitFailOn();
  bool  getDbuWarnOn();
  bool  getNoseGearDown();
  bool  getLeftGearDown();
  bool  getRightGearDown();
  bool  getParkingBrakeOn();
  bool  getCadcFault();
  bool  getSpeedBrakeOn();
  bool  getHsiTo();          // HSI
  bool  getHsiIlsWarningOn();
  bool  getHsiCourseWarningOn();
  bool  getHsiInitFlag();
  bool  getHsiTotalFlag();
  bool  getAdiOff();
  bool  getAdiAuxOn();
  bool  getAdiGsOn();
  bool  getAdiLocOn();
  bool  getHsiOff();
  bool  getBackupAdiOff();
  bool  getVviFlag();
  bool  getAoaFlag();
  bool  getAvtrOn();
  bool  getOuterMarker();
  bool  getMiddleMarker();
  bool  getFromTrue();
  bool  getIn3DWorldTrue();
  float getPositionX();
  float getPositionY();
  float getPositionZ();
  float getSpeedX();
  float getSpeedY();
  float getSpeedZ();
  float getAoa();
  float getBeta();
  float getGamma();
  float getPitch();
  float getRoll();
  float getYaw();
  float getMach();
  float getAirspeed();
  float getTrueAirspeed();
  float getGLoad();
  float getWind();
  float getNozzlePos();
  float getFtit();
  float getRpm();
  float getFuelFlow();
  float getInternalFuel();
  float getExternalFuel();
  float getAftFuel();
  float getFwdFuel();
  float getTotalFuel();
  float getEpuFuel();
  float getOilPressure();
  float getGearPosition();
  float getNoseGearPosition();
  float getLeftGearPosition();
  float getRightGearPosition();
  int   getFlare();
  int   getChaff();
  float getAdiIlsHorizontal();
  float getAdiIlsVertical();
  int   getHsiCourseState();
  int   getHsiHeadingState();
  int   getHsiTotalStates();
  float getCourseDeviation();
  float getDesiredCourse();
  float getDistanceToBeacon();
  float getBearingToBeacon();
  float getCurrentHeading();
  float getDesiredHeading();
  float getDeviationLimit();
  float getHalfDeviationLimit();
  float getLocalizerCourse();
  float getAirbaseX();
  float getAirbaseY();
  float getHsiTotalValues();
  float getTrimPitch();
  float getTrimRoll();
  float getTrimYaw();
  char *getDed(unsigned short);
  char *getDedInv(unsigned short);
  char *getPfl(unsigned short);
  char *getPflInv(unsigned short);
  int   getAuxTacan();
  int   getUfcTacan();
  float getSpeedBrake();
  int   getNumberOfRwrObjects();
  int   getFalconVersion();
  int   getMainPower();

  int   getLightBits();
  int   getLightBits2();
  int   getLightBits3();
  int   getHsiBits();

  float getAltitude();
  float getVvi();

  // BMS additional data
  bool  getAuxAABand();
  float getBaroAlt();
  int   getBupUhfFreq();
  int   getBupUhfChan();
  bool  isSetBlink(uint8_t);


  char  *getMasterCautionAsChar();    // left eyebrow
  char  *getTerrainFollowingAsChar();  // left eyebrow
  char  *getObsAsChar();            // OBS aka Marker Beacon on center console
  char  *getHudAltitudeWarningAsChar();      // ???
  char  *getWeightOnWheelsAsChar();      // not displayed
  char  *getEngineFireEyebrowAsChar();    // right eyebrow
  char  *getConfigurationAsChar();      // fault board
  char  *getHydraulicsEyebrowAsChar();    // right eyebrow
  char  *getOilPressureEyebrowAsChar();    // right eyebrow
  char  *getDualEyebrowAsChar();        // right eyebrow
  char  *getCanopyPressureEyebrowAsChar();
  char  *getTLConfigEyebrowAsChar();      // takeoff landing
  char  *getAoaAboveAsChar();
  char  *getAoaOnAsChar();
  char  *getAoaBelowAsChar();
  char  *getRefuelRdyAsChar();
  char  *getRefuelAirAsChar();          // air refueling
  char  *getRefuelDisconnectAsChar();
  char  *getFltCntrlSysAsChar();        // fault board
  char  *getLeFlapsAsChar();
  char  *getEngineFaultAsChar();        // fault board
  char  *getElecSysAsChar();          // fault board
  char  *getOverheatAsChar();          // fault board
  char  *getFuelLowAsChar();
  char  *getAvionicsAsChar();          // fault board
  char  *getRadarAltimeterAsChar();      // fault board
  char  *getIffAsChar();            // fault board
  char  *getEcmCautionLightAsChar();
  char  *getHookAsChar();            // fault board
  char  *getNwsFailAsChar();          // fault board
  char  *getCabinPressureAsChar();      // fault board
  char  *getAutoPilotOnAsChar();
  char  *getTfRadarStbyAsChar();
  char  *getHandOffAsChar();
  char  *getLaunchAsChar();
  char  *getPriorityModeAsChar();
  char  *getNavalAsChar();
  char  *getUnknownAsChar();
  char  *getTargetSeparationAsChar();
  char  *getAuxSearchAsChar();
  char  *getAuxActiveAsChar();
  char  *getAuxLowAsChar();
  char  *getAuxPowerAsChar();
  char  *getEcmPowerAsChar();
  char  *getEcmFailAsChar();
  char  *getForwardFuelLowAsChar();      // fault board
  char  *getAftFuelLowAsChar();        // fault board
  char  *getEpuOnAsChar();
  char  *getJfsOnAsChar();
  char  *getSecOnAsChar();          // secondary engine fault board
  char  *getOxygenLowAsChar();        // fault board
  char  *getProbeHeatAsChar();        // fault board
  char  *getSeatArmingAsChar();        // fault board
  char  *getBucAsChar();            // fault board
  char  *getFuelOilHotAsChar();        // fault board
  char  *getAntiSkidAsChar();          // fault board
  char  *getTfRadarEngagedAsChar();
  char  *getGearHandleAsChar();
  char  *getEngineAsChar();
  char  *getFlcsPmgAsChar();
  char  *getMainGeneratorAsChar();
  char  *getStbyGeneratorAsChar();
  char  *getEpuGeneratorAsChar();
  char  *getEpuPmgAsChar();
  char  *getToFlcsAsChar();
  char  *getFlcsRelayAsChar();
  char  *getBatteryFailureAsChar();
  char  *getHydrazineAsChar();
  char  *getAirAsChar();
  char  *getElectricFailureAsChar();      // fault board
  char  *getLefFaultAsChar();
  char  *getPowerOffAsChar();
  char  *getEngine2FireAsChar();
  char  *getHudLockLightAsChar();
  char  *getHudShootAsChar();
  char  *getNoseGearDownAsChar();
  char  *getLeftGearDownAsChar();
  char  *getRightGearDownAsChar();
  char  *getHsiToAsChar();
  char  *getHsiIlsWarningAsChar();
  char  *getHsiCourseWarningAsChar();
  char  *getHsiInitFlagAsChar();
  char  *getHsiTotalFlagAsChar();
  char  *getAdiOffAsChar();
  char  *getAdiAuxAsChar();
  char  *getAdiGsAsChar();
  char  *getAdiLocAsChar();
  char  *getHsiOffAsChar();
  char  *getBackupAdiOffAsChar();
  char  *getVviFlagAsChar();
  char  *getAoaFlagAsChar();
  char  *getAvtrAsChar();
  char  *getPositionXAsChar();
  char  *getPositionYAsChar();
  char  *getPositionZAsChar();
  char  *getSpeedXAsChar();
  char  *getSpeedYAsChar();
  char  *getSpeedZAsChar();
  char  *getAoaAsChar();
  char  *getBetaAsChar();
  char  *getGammaAsChar();
  char  *getPitchAsChar();
  char  *getRollAsChar();
  char  *getYawAsChar();
  char  *getMachAsChar();
  char  *getAirspeedAsChar();
  char  *getTrueAirspeedAsChar();
  char  *getGLoadAsChar();
  char  *getWindAsChar();
  char  *getNozzlePosAsChar();
  char  *getFtitAsChar();
  char  *getRpmAsChar();
  char  *getFuelFlowAsChar();
  char  *getInternalFuelAsChar();
  char  *getExternalFuelAsChar();
  char  *getAftFuelAsChar();
  char  *getFwdFuelAsChar();
  char  *getTotalFuelAsChar();
  char  *getEpuFuelAsChar();
  char  *getOilPressureAsChar();
  char  *getGearPositionAsChar();
  char  *getNoseGearPositionAsChar();
  char  *getLeftGearPositionAsChar();
  char  *getRightGearPositionAsChar();
  char  *getFlareAsChar();
  char  *getChaffAsChar();
  char  *getAdiIlsHorizontalAsChar();
  char  *getAdiIlsVerticalAsChar();
  char  *getHsiCourseStateAsChar();
  char  *getHsiHeadingStateAsChar();
  char  *getHsiTotalStatesAsChar();
  char  *getCourseDeviationAsChar();
  char  *getDesiredCourseAsChar();
  char  *getDistanceToBeaconAsChar();
  char  *getBearingToBeaconAsChar();
  char  *getCurrentHeadingAsChar();
  char  *getDesiredHeadingAsChar();
  char  *getDeviationLimitAsChar();
  char  *getHalfDeviationLimitAsChar();
  char  *getLocalizerCourseAsChar();
  char  *getAirbaseXAsChar();
  char  *getAirbaseYAsChar();
  char  *getHsiTotalValuesAsChar();
  char  *getTrimPitchAsChar();
  char  *getTrimRollAsChar();
  char  *getTrimYawAsChar();
  char  *getAuxTacanAsChar();
  char  *getUfcTacanAsChar();
  char  *getSpeedBrakeAsChar();
  char  *getNumberOfRwrObjectsAsChar();
  char  *getRwrObjectAsChar(int );
  char  *getMainPowerAsChar();

  char  *getClockAsChar(bool );

  char  *getAltitudeAsChar();
  char  *getBaroAltAsChar();

  char  *getVviAsChar();
  char  *getVerticalSpeedAsChar();
  
  char  *getVersionAsChar();

  char  *getGoAsChar();
  char  *getNoGoAsChar();

private:
  /// members
  HANDLE          hFlightData;    // handle to flight data
  void           *FlightDataMap;  // pointer for holding flight data mapping
  FlightData     *flightDataF4;     // the class containing data
  
  HANDLE          hFlightDataBms; // handle to BMS flight data
  void           *BmsFlightDataMap;  // pointer for holding BMS flight data mapping
  FlightDataBMS  *flightDataBms;  // the other class containing BMS specific data

  char           *cValue;         // holds return value from getters. used as temporary storage 

  /// methods
  HANDLE  createF4  (void);
  int     initF4    (void);
  int     destroyF4 (void);
  HANDLE  createBms (void);
  int     initBms   (void);
  int     destroyBms(void);
};

#endif // FALCON_SMR_H
