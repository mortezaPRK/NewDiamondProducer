#ifndef SimPPS_PPSDiamondDigiProducer_RDim_Charge_Share_H
#define SimPPS_PPSDiamondDigiProducer_RDim_Charge_Share_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <vector>
#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimSignalPoint.h"

class RDimChargeShare {
public:
  RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id);
  std::map<unsigned short, double> Share(const std::vector<RDimSignalPoint> &charge_map);

private:
  uint32_t det_id_;
  std::vector<double> signalCoupling_;
  CTPPSDiamondTopology theRPDiamondDetTopology_;

  int verbosity_;
};

#endif
