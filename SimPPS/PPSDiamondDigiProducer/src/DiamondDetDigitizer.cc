#include <vector>
#include <iostream>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/DiamondDetDigitizer.h"

DiamondDetDigitizer::DiamondDetDigitizer(const edm::ParameterSet &params,
                                         CLHEP::HepRandomEngine &eng,
                                         uint32_t det_id,
                                         const edm::EventSetup &iSetup)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  theRDimDummyROCSimulator = std::make_unique<RDimDummyROCSimulator>(params, det_id_);
  theHitToChargeConvertor = RDimHitToCharge(params);
}

DiamondDetDigitizer::~DiamondDetDigitizer() {}

void DiamondDetDigitizer::run(const std::vector<PSimHit> &input,
                              const double effFactor,
                              const std::vector<int> &input_links,
                              std::vector<CTPPSDiamondDigi> &output_digi,
                              std::vector<std::vector<std::pair<int, double>>> &output_digi_links) {
  std::vector<std::pair<double, double>> theDiamondCharge;

  int input_size = input.size();
  for (int i = 0; i < input_size; ++i) {
    RDimHitToCharge::ChargeInfo charge_info = theHitToChargeConvertor.ChargeFromHit(input[i]);
    theDiamondCharge.push_back(std::pair(charge_info.charge() * effFactor, charge_info.timeOfFlight()));
  }

  std::map<unsigned short, std::vector<std::pair<int, double>>> theSignalProvenance;
  theRDimDummyROCSimulator->ConvertChargeToSignal(theDiamondCharge, theSignalProvenance, output_digi, output_digi_links);
}
