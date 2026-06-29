/*
 * MStripHit.h
 *
 * Copyright (C) by Andreas Zoglauer.
 * All rights reserved.
 *
 * Please see the source-file for the copyright-notice.
 *
 */


#ifndef __MStripHit__
#define __MStripHit__


////////////////////////////////////////////////////////////////////////////////


// Standard libs:

// ROOT libs:

// MEGAlib libs:
#include "MGlobal.h"

// Nuclearizer libs
#include "MReadOutElement.h"
#include "MReadOutElementDoubleStrip.h"

// Forward declarations:


////////////////////////////////////////////////////////////////////////////////


//! This class represents a hit in a strip
class MStripHit
{
  // public interface:
 public:
  //! Default constructor
  MStripHit();
  //! Default destructor
  virtual ~MStripHit();
  //! Copy constructor is disabled because this class owns m_ReadOutElement
  MStripHit(const MStripHit&) = delete;
  //! Assignment is disabled because this class owns m_ReadOutElement
  MStripHit& operator=(const MStripHit&) = delete;

  //! Reset all data
  void Clear();

  //! Return the read-out element
  //! Ownership stays with this object
  MReadOutElement* GetReadOutElement() const { return m_ReadOutElement; }

  //! Set the detector ID
  void SetDetectorID(unsigned int DetectorID) { m_ReadOutElement->SetDetectorID(DetectorID); }
  //! Return the detector ID
  unsigned int GetDetectorID() const { return m_ReadOutElement->GetDetectorID(); }

  //! Set the strip ID
  void SetStripID(unsigned int StripID) { m_ReadOutElement->SetStripID(StripID); }
  //! Return the strip ID
  unsigned int GetStripID() const { return m_ReadOutElement->GetStripID(); }

  //! DEPRECATED: Set whether the strip is on the low voltage side using IsLowVoltageStrip instead
  void IsXStrip(bool LowVoltageSide) { m_ReadOutElement->IsLowVoltageStrip(LowVoltageSide); }
  //! DEPRECATED: Return whether the strip is on the low voltage side using IsLowVoltageStrip instead
  bool IsXStrip() const { return m_ReadOutElement->IsLowVoltageStrip(); }

  //! Set whether the strip is on the low voltage side
  void IsLowVoltageStrip(bool LowVoltageSide) { m_ReadOutElement->IsLowVoltageStrip(LowVoltageSide); }
  //! Return whether the strip is on the low voltage side
  bool IsLowVoltageStrip() const { return m_ReadOutElement->IsLowVoltageStrip(); }

  //! Set whether the strip has triggered
  void HasTriggered(bool HasTriggered) { m_HasTriggered = HasTriggered; }
  //! Return whether the strip has triggered
  bool HasTriggered() const { return m_HasTriggered; }

  //! Set the uncorrected ADC units of the strip (before common-mode correction)
  void SetUncorrectedADCUnits(double UncorrectedADCUnits) { m_UncorrectedADCUnits = UncorrectedADCUnits; }
  //! Return the uncorrected ADC units of the strip (before common-mode correction)
  double GetUncorrectedADCUnits() const { return m_UncorrectedADCUnits; }

  //! Set the ADC units of the strip
  void SetADCUnits(double ADCUnits) { m_ADCUnits = ADCUnits; }
  //! Return the ADC units of the strip
  double GetADCUnits() const { return m_ADCUnits; }

  //! Set the calibrated energy
  void SetEnergy(double Energy) { m_Energy = Energy; }
  //! Return the calibrated energy
  double GetEnergy() const { return m_Energy; }

  //! Set the energy resolution (sigma)
  void SetEnergyResolution(double EnergyResolution) { m_EnergyResolution = EnergyResolution; }
  //! Return the energy resolution
  double GetEnergyResolution() const { return m_EnergyResolution; }

  //! Set the TAC
  void SetTAC(double TAC) { m_TAC = TAC; }
  //! Return the TAC
  double GetTAC() const { return m_TAC; }

  //! Set the TAC resolution
  void SetTACResolution(double TACResolution) { m_TACResolution = TACResolution; }
  //! Return the TAC resolution
  double GetTACResolution() const { return m_TACResolution; }

  //! Set the timing in nanoseconds
  void SetTiming(double Timing) { m_Timing = Timing; }
  //! Return the timing in nanoseconds
  double GetTiming() const { return m_Timing; }

  //! Set the timing resolution
  void SetTimingResolution(double TimingResolution) { m_TimingResolution = TimingResolution; }
  //! Return the timing resolution
  double GetTimingResolution() const { return m_TimingResolution; }

  //! Set the temperature of the relevant preamp (in degrees C)
  void SetPreampTemp(double PreampTemp) { m_PreampTemp = PreampTemp; }
  //! Return the temperature of the relevant preamp (in degrees C)
  double GetPreampTemp() const { return m_PreampTemp; }

  //! Add origins from the simulation and remove duplicates
  void AddOrigins(const vector<int>& Origins);
  //! Return the origins from the simulation
  vector<int> GetOrigins() const { return m_Origins; }

  //! Set the guard ring flag
  void IsGuardRing(bool GuardRing) { m_IsGuardRing = GuardRing; }
  //! Return whether the strip is a guard ring
  bool IsGuardRing() const { return m_IsGuardRing; }
  //! Set the nearest-neighbor flag
  void IsNearestNeighbor(bool NearestNeighbor) { m_IsNearestNeighbor = NearestNeighbor; }
  //! Return whether the strip is a nearest neighbor
  bool IsNearestNeighbor() const { return m_IsNearestNeighbor; }

  //! Set the fast-timing flag
  void HasFastTiming(bool FastTiming) { m_HasFastTiming = FastTiming; }
  //! Return whether the strip timing is fast
  bool HasFastTiming() const { return m_HasFastTiming; }

  //! Set the calibrated-timing flag
  void HasCalibratedTiming(bool CalibratedTiming) { m_HasCalibratedTiming = CalibratedTiming; }
  //! Return whether the strip timing has been calibrated
  bool HasCalibratedTiming() const { return m_HasCalibratedTiming; }

  //! Return the bitwise strip-hit flags
  unsigned int MakeFlags();
  //! Update the strip-hit flags from a bit mask
  void ParseFlags(unsigned int Flags);

  //! Parse a strip hit from a line
  bool Parse(const MString& Line, int Version = 1);
  //! Write the strip hit to a file stream
  bool StreamDat(ostream& S, int Version = 1);
  //! Stream the strip hit in MEGAlib's ROA format
  void StreamRoa(ostream& S, bool WithADC = true, bool WithTAC = true, bool WithEnergy = false, bool WithTiming = false, bool WithTemperature = false, bool WithFlags = false, bool WithOrigins = false);


  // protected methods:
 protected:

   // private methods:
 private:



  // protected members:
 protected:


  // private members:
 private:
  //! Read-out element
  MReadOutElementDoubleStrip* m_ReadOutElement;
  //! True if the strip has triggered
  bool m_HasTriggered;
  //! ADC units before all corrections
  double m_UncorrectedADCUnits;
  //! ADC units after any correction
  double m_ADCUnits;
  //! Calibrated energy
  double m_Energy;
  //! Energy resolution
  double m_EnergyResolution;
  //! TAC timing
  double m_TAC;
  //! TAC timing resolution
  double m_TACResolution;
  //! Timing in nanoseconds
  double m_Timing;
  //! Timing resolution in nanoseconds
  double m_TimingResolution;
  //! Temperature of the preamp
  double m_PreampTemp;

  //! True if the hit is a guard ring
  bool m_IsGuardRing;
  //! True if the hit is a nearest neighbor
  bool m_IsNearestNeighbor;

  //! True if the hit has fast timing
  bool m_HasFastTiming;
  //! True if the hit has calibrated timing
  bool m_HasCalibratedTiming;

  //! Origin interaction IDs from the simulation
  vector<int> m_Origins;

#ifdef ___CLING___
 public:
  ClassDef(MStripHit, 0) // A strip hit
#endif

};

#endif


////////////////////////////////////////////////////////////////////////////////
