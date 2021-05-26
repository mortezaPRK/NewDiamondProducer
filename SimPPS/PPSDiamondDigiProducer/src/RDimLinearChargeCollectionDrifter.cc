#include "SimPPS/PPSDiamondDigiProducer/interface/RDimLinearChargeCollectionDrifter.h"
// #include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"
#include <iostream>
#include <vector>

RDimLinearChargeCollectionDrifter::RDimLinearChargeCollectionDrifter(const edm::ParameterSet &params, uint32_t det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");

  GeV_per_electron_ = params.getParameter<double>("RDimGeVPerElectron");
  charge_cloud_sigmas_vect_ = params.getParameter<std::vector<double>>("RDimInterSmearing");
  // det_thickness_ = CTPPSDiamondTopology().detThickness();
  det_id_ = det_id;
}


// Converts Energy to number of electron
// Converts a vector<energy, position> to vector<num_of_electons, 2d position, depth>
//
// getSigma is not implemented yet
std::vector<RDimSignalPoint> RDimLinearChargeCollectionDrifter::Drift(
    const std::vector<RDimEnergyDepositUnit> &energy_deposition) {
  // convert an energy deposit in a point and in a charge of electrons n=E/3.61 (eV)
  temp_.resize(energy_deposition.size());
  for (unsigned int i = 0; i < energy_deposition.size(); i++) {
    temp_[i].setPosition(LocalPoint(energy_deposition[i].Position().x(), energy_deposition[i].Position().y()));
    temp_[i].setSigma(getSigma_(energy_deposition[i].Position().z()));
    temp_[i].setCharge(energy_deposition[i].Energy() / GeV_per_electron_);
    if (verbosity_ > 1) {
      edm::LogInfo("RDimLinearChargeCollectionDrifter")
          << det_id_ << " :" << temp_[i].Position() << " " << temp_[i].Sigma() << " " << temp_[i].Charge();
    }
  }
  return temp_;
}

// TODO: implement
double RDimLinearChargeCollectionDrifter::getSigma_(double z) { return charge_cloud_sigmas_vect_[0]; }
