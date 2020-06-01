#ifndef SimPPS_PPSDiamondDigiProducer_RDim_Charge_Share_H
#define SimPPS_PPSDiamondDigiProducer_RDim_Charge_Share_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <vector>
// #include "Geometry/VeryForwardGeometry/interface/CTPPSPixelSimTopology.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimSignalPoint.h"

class RDimChargeShare {
public:
  RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id);
  std::map<unsigned short, double> Share(const std::vector<RDimSignalPoint> &charge_map);

private:
  uint32_t det_id_;
  std::vector<double> signalCoupling_;
  // CTPPSPixelSimTopology theRPixDetTopology_;
  // CTPPSPixelIndices pxlInd;
  // const int pxlRowSize_ = pxlInd.getDefaultRowDetSize();
  // const int pxlColSize_ = pxlInd.getDefaultColDetSize();
  // int no_of_pixels_;

  int verbosity_;

  // std::string ChargeMapFile2E_[4];
  // double chargeMap2E_[4][60][40];
  // const int xBinMax_[4] = {29, 59, 29, 59};  // X upper bins of the charge maps [0:3]
  // const int yBinMax_[4] = {19, 19, 39, 39};  // Y upper bins of the charge maps [0:3]
};

#endif
