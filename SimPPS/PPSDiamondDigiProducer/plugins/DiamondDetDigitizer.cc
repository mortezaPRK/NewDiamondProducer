#include <vector>
#include <iostream>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/DiamondDetDigitizer.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"

DiamondDetDigitizer::DiamondDetDigitizer(const edm::ParameterSet &params,
                                         CLHEP::HepRandomEngine &eng,
                                         uint32_t det_id,
                                         const edm::EventSetup &iSetup)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("DiamondVerbosity");
  theRDimHitChargeConverter = std::make_unique<RDimHitChargeConverter>(params, eng, det_id_);
}

DiamondDetDigitizer::~DiamondDetDigitizer() {}

void DiamondDetDigitizer::run(const std::vector<PSimHit> &input,
                              const std::vector<int> &input_links,
                              std::vector<CTPPSDiamondDigi> &output_digi,
                              std::vector<std::vector<std::pair<int, double> > > &output_digi_links) {
  int input_size = input.size();
  for (int i = 0; i < input_size; ++i) {
    std::map<unsigned short, double> the_pixel_charge_map;
    the_pixel_charge_map = theRDimHitChargeConverter->processHit(input[i]);
  }
}
