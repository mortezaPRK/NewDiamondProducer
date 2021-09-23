#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitToCharge.h"
#include <iostream>
#include <fstream>

RDimHitToCharge::RDimHitToCharge(const edm::ParameterSet& params) {
  GeV_per_electron_ = params.getParameter<double>("RDimGeVPerElectron");
  verbosity_ = params.getParameter<int>("RDimVerbosity");
}

RDimHitToCharge::ChargeInfo RDimHitToCharge::ChargeFromHit(const PSimHit& hit) {
  double energy = hit.energyLoss();
  Local3DPoint position = hit.exitPoint();
  double charge = energy / GeV_per_electron_;
  double tof = hit.timeOfFlight();

  return RDimHitToCharge::ChargeInfo(energy, position, charge, tof);
}

std::ostream& operator<<(std::ostream& os, const RDimHitToCharge::ChargeInfo& ci) {
  os << "(energy:" << ci.energy() << ", positionX:" << ci.positionX() << ", positionY:" << ci.positionY()
     << ", charge:" << ci.charge() << ")";
  return os;
}