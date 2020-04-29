#ifndef SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H
#define SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimPPS/RPDigiProducer/plugins/RDLinearChargeDivider.h"
#include "SimPPS/RPDigiProducer/interface/RPSimTypes.h"

#include <map>

class RDHitChargeConverter {
public:
  RDHitChargeConverter(const edm::ParameterSet &params_, CLHEP::HepRandomEngine &eng, RDDetId det_id);
  ~RDHitChargeConverter();

  simromanpot::strip_charge_map processHit(const PSimHit &hit);

private:
  const RDDetId det_id_;

  std::unique_ptr<RDLinearChargeDivider> theRDChargeDivider;
  int verbosity_;
};

#endif  //SimPPS_RDDigiProducer_RP_HIT_CHARGE_CONVERTER_H
