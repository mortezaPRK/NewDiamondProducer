#ifndef SimPPS_RDDigiProducer_RP_LINEAR_CHARGE_DIVIDER_H
#define SimPPS_RDDigiProducer_RP_LINEAR_CHARGE_DIVIDER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

namespace CLHEP {
  class HepRandomEngine;
}

class RDLinearChargeDivider {
public:
  RDLinearChargeDivider(const edm::ParameterSet& params, CLHEP::HepRandomEngine& eng, RDDetId det_id);
  ~RDLinearChargeDivider();
  simromanpot::energy_path_distribution divide(const PSimHit& hit);

private:
  const edm::ParameterSet& params_;
  CLHEP::HepRandomEngine& rndEngine_;
  RDDetId det_id_;

  simromanpot::energy_path_distribution the_energy_path_distribution_;
  int verbosity_;
};

#endif  //SimPPS_RDDigiProducer_RP_LINEAR_CHARGE_DIVIDER_H
