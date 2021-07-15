#ifndef RDIM_DUMMY_ROC_SIMULATION_H
#define RDIM_DUMMY_ROC_SIMULATION_H

#include <set>

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
// #include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigiCollection.h"
// #include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelGainCalibrations.h"
// #include "CondFormats/CTPPSReadoutObjects/interface/CTPPSPixelAnalysisMask.h"
// #include "RecoCTPPS/PixelLocal/interface/CTPPSPixelGainCalibrationDBService.h"

class RDimDummyROCSimulator {
public:
  RDimDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id);

  void ConvertChargeToHits(const std::map<unsigned short, double> &signals,
                           std::map<unsigned short, std::vector<std::pair<int, double> > > &theSignalProvenance,
                           std::vector<CTPPSDiamondDigi> &output_digi,
                           std::vector<std::vector<std::pair<int, double> > > &output_digi_links);

private:
  typedef std::set<unsigned short> dead_pixel_set;
  static constexpr double highRangeCal_ = 1800.;
  static constexpr double lowRangeCal_ = 260.;
  static constexpr int maxADC_ = 255;

  uint32_t det_id_;
  int verbosity_;
  double threshold_;
  double electron_per_adc_;
  int VcaltoElectronGain_;
  int VcaltoElectronOffset_;
  bool doSingleCalibration_;

  double capacitor_; 
  double transmit_time_;
  double resistor_;
  
  double calculateMaximumVoltage(double charge);
  void calculateEdges(double vmax, double &ledge, double &tedge);
};

#endif
