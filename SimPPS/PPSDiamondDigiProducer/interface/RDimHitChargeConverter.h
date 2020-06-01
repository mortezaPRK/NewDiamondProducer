#ifndef SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H
#define SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimLinearChargeDivider.h"
// #include "SimPPS/PPSDiamondDigiProducer/interface/RPSimTypes.h"

#include <map>

class RDimHitChargeConverter {
public:
  RDimHitChargeConverter(const edm::ParameterSet &params_, CLHEP::HepRandomEngine &eng, uint32_t det_id);
  ~RDimHitChargeConverter();

  std::map<unsigned short, double> processHit(const PSimHit &hit);

private:
  const uint32_t det_id_;
  std::unique_ptr<RDimLinearChargeDivider> theRDimChargeDivider;
  int verbosity_;
};

#endif  //SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H
