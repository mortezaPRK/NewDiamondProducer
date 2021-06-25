#ifndef SimPPS_PPSDiamondDigiProducer_Diamond_DET_DIGITIZER_H
#define SimPPS_PPSDiamondDigiProducer_Diamond_DET_DIGITIZER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <vector>
#include <string>

#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimGeneral/NoiseGenerators/interface/GaussianTailNoiseGenerator.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimDummyROCSimulator.h"
#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

namespace CLHEP {
  class HepRandomEngine;
}

class DiamondDetDigitizer {
public:
  DiamondDetDigitizer(const edm::ParameterSet &params,
                      CLHEP::HepRandomEngine &eng,
                      uint32_t det_id,
                      const edm::EventSetup &iSetup);

  void run(const std::vector<PSimHit> &input,
           const std::vector<int> &input_links,
           std::vector<CTPPSDiamondDigi> &output_digi,
           std::vector<std::vector<std::pair<int, double>>> &output_digi_links);

  double getSigma_(double z);
  
  ~DiamondDetDigitizer();

private:
  edm::ParameterSet conf_;
  uint32_t det_id_;
  std::unique_ptr<RDimDummyROCSimulator> theRDimDummyROCSimulator;
  double GeV_per_electron_;
  std::vector<double> charge_cloud_sigmas_vect_;
  CTPPSDiamondTopology theRPDiamondDetTopology_;
  int verbosity_;
};
#endif
