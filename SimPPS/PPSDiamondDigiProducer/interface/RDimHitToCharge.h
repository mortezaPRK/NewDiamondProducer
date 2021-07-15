#ifndef SimPPS_PPSDiamondDigiProducer_RDim_Hit_To_Charge_H
#define SimPPS_PPSDiamondDigiProducer_RDim_Hit_To_Charge_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <vector>
#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"

class RDimHitToCharge {
public:
  RDimHitToCharge(const edm::ParameterSet& params);
  RDimHitToCharge() = default;

  class ChargeInfo {
  public:
    ChargeInfo(double energy, Local3DPoint position, double sigma, double charge, double tof)
        : energy_(energy), position_(position), sigma_(sigma), charge_(charge), tof_(tof) {}

    inline double energy() const { return energy_; }
    inline double positionX() const { return position_.x(); }
    inline double positionY() const { return position_.y(); }
    inline double sigma() const { return sigma_; }
    inline double charge() const { return charge_; }
    inline double timeOfFlight() const { return tof_; }

  private:
    double energy_;
    Local3DPoint position_;
    double sigma_;
    double charge_;
    double tof_;

  public:
    friend std::ostream& operator<<(std::ostream& output, const ChargeInfo& c);
  };

  ChargeInfo ChargeFromHit(const PSimHit& hit);

private:
  double GeV_per_electron_;
  std::vector<double> charge_cloud_sigmas_vect_;
  int verbosity_;

  double getSigma_(double z);
};

#endif