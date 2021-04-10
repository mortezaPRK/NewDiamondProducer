#include <vector>
#include <iostream>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/DiamondDetDigitizer.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimHitChargeConverter.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/RDimPileUpSignals.h"

DiamondDetDigitizer::DiamondDetDigitizer(const edm::ParameterSet &params,
                                         CLHEP::HepRandomEngine &eng,
                                         uint32_t det_id,
                                         const edm::EventSetup &iSetup)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  theRDimHitChargeConverter = std::make_unique<RDimHitChargeConverter>(params, eng, det_id_);
  theRDimPileUpSignals = std::make_unique<RDimPileUpSignals>(params, det_id_);
  theRDimDummyROCSimulator = std::make_unique<RDimDummyROCSimulator>(params, det_id_);

  std::cout << "here at: " << __FUNCTION__ << '\n';
}

DiamondDetDigitizer::~DiamondDetDigitizer() {}

void DiamondDetDigitizer::run(const std::vector<PSimHit> &input,
                              const std::vector<int> &input_links,
                              std::vector<CTPPSDiamondDigi> &output_digi,
                              std::vector<std::vector<std::pair<int, double> > > &output_digi_links) {
  std::cout << "here at: " << __FUNCTION__ << '\n';
  std::cout << "h1\n";
  int input_size = input.size();
  std::cout << "h2\n";
  std::cout << input_size;
  std::cout << "h3\n";
  for (int i = 0; i < input_size; ++i) {
    std::map<unsigned short, double> the_diamond_charge_map;
    the_diamond_charge_map = theRDimHitChargeConverter->processHit(input[i]);
    theRDimPileUpSignals->add(the_diamond_charge_map, 0);
    std::cout << "h4\n";
  }
  std::cout << "h5\n";

  const std::map<unsigned short, double> &theSignal = theRDimPileUpSignals->dumpSignal();
  std::map<unsigned short, std::vector<std::pair<int, double> > > &theSignalProvenance =
      theRDimPileUpSignals->dumpLinks();
  std::map<unsigned short, double> afterNoise;
  afterNoise = theSignal;
  theRDimDummyROCSimulator->ConvertChargeToHits(afterNoise, theSignalProvenance, output_digi, output_digi_links);
}
