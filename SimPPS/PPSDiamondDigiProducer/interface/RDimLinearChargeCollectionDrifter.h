#ifndef SimPPS_PPSDiamondDigiProducer_RDim_LINEAR_CHARGE_COLLECTION_DRIFTER_H
#define SimPPS_PPSDiamondDigiProducer_RDim_LINEAR_CHARGE_COLLECTION_DRIFTER_H

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimPPS/PPSDiamondDigiProducer/interface/RDimSignalPoint.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimEnergyDepositUnit.h"

class RDimLinearChargeCollectionDrifter {
public:
  RDimLinearChargeCollectionDrifter(const edm::ParameterSet &params, uint32_t det_id);
  std::vector<RDimSignalPoint> Drift(const std::vector<RDimEnergyDepositUnit> &energy_deposition);

private:
  std::vector<RDimSignalPoint> temp_;

  std::vector<double> charge_cloud_sigmas_vect_;
  double GeV_per_electron_;
  int verbosity_;
  double det_thickness_;
  uint32_t det_id_;

  double getSigma_(double z);
};

#endif
