#include "SimPPS/RPDigiProducer/plugins/RDLinearChargeDivider.h"
#include "DataFormats/GeometryVector/interface/LocalPoint.h"
#include "DataFormats/GeometryVector/interface/LocalVector.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

RDLinearChargeDivider::RDLinearChargeDivider(const edm::ParameterSet& params,
                                             CLHEP::HepRandomEngine& eng,
                                             RDDetId det_id)
    : params_(params), rndEngine_(eng), det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDVerbosity");
}

RDLinearChargeDivider::~RDLinearChargeDivider() {}

simromanpot::energy_path_distribution RDLinearChargeDivider::divide(const PSimHit& hit) {
  LocalVector direction = hit.exitPoint() - hit.entryPoint();
  // NOTE: What's our constraints for proccessing Hit
  // if (direction.z() > 10 || direction.x() > 200 || direction.y() > 200) {
  //   the_energy_path_distribution_.clear();
  //   return the_energy_path_distribution_;
  // }

  // TODO: change segment calculations
  int NumberOfSegmentation_y = (int)(1 + chargedivisionsPerStrip_ * fabs(direction.y()) / pitch_);
  int NumberOfSegmentation_z = (int)(1 + chargedivisionsPerThickness_ * fabs(direction.z()) / thickness_);
  int NumberOfSegmentation = (double)std::max(NumberOfSegmentation_y, NumberOfSegmentation_z);

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
