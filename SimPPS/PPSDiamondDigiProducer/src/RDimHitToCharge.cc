#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitToCharge.h"
#include <iostream>
#include <fstream>

RDimHitToCharge::RDimHitToCharge(const edm::ParameterSet &params) {
  GeV_per_electron_ = params.getParameter<double>("RDimGeVPerElectron");
  charge_cloud_sigmas_vect_ = params.getParameter<std::vector<double>>("RDimInterSmearing");
  verbosity_ = params.getParameter<int>("RDimVerbosity");
}

RDimHitToCharge::ChargeInfo RDimHitToCharge::ChargeFromHit(const PSimHit &hit) {
    double energy = hit.energyLoss();
    Local3DPoint position = hit.exitPoint();
    double sigma = getSigma_(position.z());
    double charge = energy / GeV_per_electron_;

    return RDimHitToCharge::ChargeInfo(energy, position, sigma, charge);
}


double RDimHitToCharge::getSigma_(double z) { return charge_cloud_sigmas_vect_[0]; }

std::ostream& operator<<(std::ostream& os, const RDimHitToCharge::ChargeInfo& ci) {
  os << "(energy:" << ci.energy() <<  ", positionX:" << ci.positionX() <<  ", positionY:" << ci.positionY() <<  ", sigma:" << ci.sigma() <<  ", charge:" << ci.charge() << ")";
  return os;
}