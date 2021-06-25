#include <vector>
#include <iostream>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/DiamondDetDigitizer.h"

DiamondDetDigitizer::DiamondDetDigitizer(const edm::ParameterSet &params,
                                         CLHEP::HepRandomEngine &eng,
                                         uint32_t det_id,
                                         const edm::EventSetup &iSetup)
    :conf_(params), det_id_(det_id) {
  verbosity_ = conf_.getParameter<int>("RDimVerbosity");
  theRDimDummyROCSimulator = std::make_unique<RDimDummyROCSimulator>(params, det_id_);
  GeV_per_electron_ = params.getParameter<double>("RDimGeVPerElectron");
  charge_cloud_sigmas_vect_ = params.getParameter<std::vector<double>>("RDimInterSmearing");

  std::cout << "here at: " << __FUNCTION__ << '\n';
}

DiamondDetDigitizer::~DiamondDetDigitizer() {}

void DiamondDetDigitizer::run(const std::vector<PSimHit> &input,
                              const std::vector<int> &input_links,
                              std::vector<CTPPSDiamondDigi> &output_digi,
                              std::vector<std::vector<std::pair<int, double> > > &output_digi_links) {
  std::map<unsigned short, double> theDiamondChargeMap;

  int input_size = input.size();
  
  for (int i = 0; i < input_size; ++i) {
    PSimHit hit = input[i];
    double hit_pos_x, hit_pos_y;

    double energy = hit.energyLoss();
    Local3DPoint position = hit.exitPoint();
    double sigma = getSigma_(position.z());
    double charge = energy / GeV_per_electron_;


    CTPPSDiamondTopology::PartInfo relevant_part = theRPDiamondDetTopology_.getPartInvolved(
        position.x(), position.y(), sigma, hit_pos_x, hit_pos_y);

    double effic = relevant_part.effFactor();
    // part index => from 1 - 8
    unsigned short part_index = relevant_part.partIndex();

    double charge_in_part = charge * effic;

    theDiamondChargeMap[part_index] += charge_in_part;
  }

  // const std::map<unsigned short, double> &theSignal = theRDimPileUpSignals->dumpSignal();
  std::map<unsigned short, std::vector<std::pair<int, double> > > theSignalProvenance;
      // theRDimPileUpSignals->dumpLinks();
  // std::map<unsigned short, double> afterNoise;
  // afterNoise = theSignal;
  theRDimDummyROCSimulator->ConvertChargeToHits(theDiamondChargeMap, theSignalProvenance, output_digi, output_digi_links);
}


double DiamondDetDigitizer::getSigma_(double z) { return charge_cloud_sigmas_vect_[0]; }