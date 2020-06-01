#ifndef SimPPS_PPSDiamondDigiProducer_Diamond_DET_DIGITIZER_H
#define SimPPS_PPSDiamondDigiProducer_Diamond_DET_DIGITIZER_H

#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include <vector>
#include <string>

#include "SimTracker/Common/interface/SiG4UniversalFluctuation.h"
#include "SimGeneral/NoiseGenerators/interface/GaussianTailNoiseGenerator.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/EventSetup.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

namespace CLHEP
{
  class HepRandomEngine;
}

class DiamondDetDigitizer
{
public:
  DiamondDetDigitizer(const edm::ParameterSet &params,
                      CLHEP::HepRandomEngine &eng,
                      uint32_t det_id,
                      const edm::EventSetup &iSetup);

  void run(const std::vector<PSimHit> &input,
           const std::vector<int> &input_links,
           std::vector<CTPPSDiamondDigi> &output_digi,
           std::vector<std::vector<std::pair<int, double>>> &output_digi_links);

  ~DiamondDetDigitizer();

private:
  uint32_t det_id_;
  std::unique_ptr<RDimHitChargeConverter> theRDimHitChargeConverter;
  int verbosity_;
};
#endif
