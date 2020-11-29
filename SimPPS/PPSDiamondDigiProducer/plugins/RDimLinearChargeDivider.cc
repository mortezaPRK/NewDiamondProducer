#include "SimPPS/PPSDiamondDigiProducer/interface/RDimLinearChargeDivider.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

RDimLinearChargeDivider::RDimLinearChargeDivider(const edm::ParameterSet& params,
                                                 CLHEP::HepRandomEngine& eng,
                                                 RDDetId det_id)
    : params_(params), rndEngine_(eng), det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDVerbosity");
  chargedivisions_ = params.getParameter<int>("RPDiamondChargeDivisions");
}

RDimLinearChargeDivider::~RDimLinearChargeDivider() {}

// 
// This is used for distribting a hint energy to each segment of detector
// 
// we are assuming enegry is distrubted evenly in every segment
//
//
// returns a vector of <energy,postion> combinition
//
// TODO: use vector<energy, position> instead for return value 
//      same as SimPPS.PPSPixelDigiProducer.RPixEnergyDepositUnit
simromanpot::energy_path_distribution RDimLinearChargeDivider::divide(const PSimHit& hit) {
  LocalVector direction = hit.exitPoint() - hit.entryPoint();\
  // TODO: use pixel's divider
  // NOTE: What's our constraints for proccessing Hit
  // if (direction.z() > 10 || direction.x() > 200 || direction.y() > 200) {
  //   the_energy_path_distribution_.clear();
  //   return the_energy_path_distribution_;
  // }

  // TODO: change segment calculations
  // int NumberOfSegmentation_y = (int)(1 + chargedivisionsPerStrip_ * fabs(direction.y()) / pitch_);
  // int NumberOfSegmentation_z = (int)(1 + chargedivisionsPerThickness_ * fabs(direction.z()) / thickness_);
  // int NumberOfSegmentation = (double)std::max(NumberOfSegmentation_y, NumberOfSegmentation_z);
  int NumberOfSegmentation = chargedivisions_ // this is = 20 for pixel

  double eLoss = hit.energyLoss();  // Eloss in GeV

  the_energy_path_distribution_.resize(NumberOfSegmentation);

  for (int i = 0; i < NumberOfSegmentation; i++) {
    the_energy_path_distribution_[i].setPosition(
      hit.entryPoint() + double((i + 0.5) / NumberOfSegmentation) * direction
    );
    the_energy_path_distribution_[i].setEnergy(eLoss / NumberOfSegmentation);
  }
  return the_energy_path_distribution_;
}
