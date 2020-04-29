#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "SimPPS/RPDigiProducer/plugins/RDLinearChargeDivider.h"
#include "SimPPS/RPDigiProducer/plugins/RDHitChargeConverter.h"

RDHitChargeConverter::RDHitChargeConverter(const edm::ParameterSet &params, CLHEP::HepRandomEngine &eng, RPDetId det_id)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RPVerbosity");
  theRDChargeDivider = std::make_unique<RDLinearChargeDivider>(params, eng, det_id);
}

RDHitChargeConverter::~RDHitChargeConverter() {}

simromanpot::strip_charge_map RDHitChargeConverter::processHit(const PSimHit &hit) {
  simromanpot::energy_path_distribution ions_along_path = theRDChargeDivider->divide(hit);
  // return theRPixChargeShare->Share(theRPixChargeCollectionDrifter->Drift(ions_along_path));
}
