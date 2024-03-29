#ifndef SimPPS_PPSDiamondDigiProducers_PPSDiamondDigiProducer_h
#define SimPPS_PPSDiamondDigiProducers_PPSDiamondDigiProducer_h

// -*- C++ -*-
//
// Package:    PPSDiamondDigiProducer
// Class:      DiamondDigiProducer
//
/**\class DiamondDigiProducer PPSDiamondDigiProducer.cc SimPPS/PPSDiamondDigiProducer/plugins/PPSDiamondDigiProducer.cc

 Description: Base Producer for Diamond Det

 Implementation:
     Not Implemented yet
*/
//
// Authors:  M.Pourkazemi M.Etesami
//

// system include files
#include <memory>
#include <vector>
#include <map>
#include <string>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/ParameterSetDescription.h"
#include "FWCore/ParameterSet/interface/ConfigurationDescriptions.h"

//  ****  CTPPS
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include "SimPPS/PPSDiamondDigiProducer/interface/DiamondDetDigitizer.h"

#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"

// user include files
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/CrossingFrame/interface/CrossingFrame.h"
#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"
#include <cstdlib>

//needed for the geometry:
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/Common/interface/DetSetVector.h"

//Random Number
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "CLHEP/Random/RandomEngine.h"

namespace CLHEP {
  class HepRandomEngine;
}

class DiamondDigiProducer : public edm::stream::EDProducer<> {
public:
  explicit DiamondDigiProducer(const edm::ParameterSet&);
  ~DiamondDigiProducer() override;
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void produce(edm::Event&, const edm::EventSetup&) override;

  typedef std::map<unsigned int, std::vector<PSimHit>> simhit_map;
  typedef simhit_map::iterator simhit_map_iterator;
  std::map<uint32_t, std::unique_ptr<DiamondDetDigitizer>> theAlgoMap;

  edm::ParameterSet conf_;

  CLHEP::HepRandomEngine* rndEngine_ = nullptr;
  edm::EDGetTokenT<edm::PSimHitContainer> containerToken;

  std::map<unsigned int, double> effMap;
  int verbosity_;
};

DiamondDigiProducer::DiamondDigiProducer(const edm::ParameterSet& conf) : conf_(conf) {
  produces<edm::DetSetVector<CTPPSDiamondDigi>>();
  containerToken = consumes<edm::PSimHitContainer>(edm::InputTag("g4SimHits", "CTPPSTimingHits"));

  verbosity_ = conf.getParameter<int>("RDimVerbosity");
  std::vector<edm::ParameterSet> voltage_time_coef_ =
      conf_.getParameter<std::vector<edm::ParameterSet>>("RDimVoltageTimeCoef");
  RDimDummyROCSimulator::PopulateVTBins(voltage_time_coef_, 1000, 1.0, 5.0);

  std::vector<edm::ParameterSet> detectorsEffFactors_ =
      conf_.getParameter<std::vector<edm::ParameterSet>>("RDimEffFactors");
  for (auto const& it : detectorsEffFactors_) {
    unsigned int det_id = it.getParameter<unsigned int>("DetID");
    double value = it.getParameter<double>("EffFactor");
    effMap[det_id] = value;
  }
}

DiamondDigiProducer::~DiamondDigiProducer() {}

void DiamondDigiProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  edm::ParameterSetDescription desc;
  desc.add<std::string>("InputCollection", "g4SimHitsCTPPSTimingHits");
  desc.add<int>("RDimVerbosity", 0);
  desc.add<double>("RDimGeVPerElectron", 1.0);
  desc.add<double>("RDimMinVoltage", 0.2);
  desc.add<double>("RDimLeadingEdgeHeightPercentage", 0.3);
  desc.add<double>("RDimKCoeff", .0);

  edm::ParameterSetDescription diamond_eff_factors_desc;
  diamond_eff_factors_desc.add<unsigned int>("DetID", 0);
  diamond_eff_factors_desc.add<double>("EffFactor", 0);
  desc.addVPSet("RDimEffFactors", diamond_eff_factors_desc);

  edm::ParameterSetDescription voltage_time_coeff_desc;
  voltage_time_coeff_desc.add<unsigned int>("Power", 0);
  voltage_time_coeff_desc.add<double>("Coeff", 0);
  desc.addVPSet("RDimVoltageTimeCoef", voltage_time_coeff_desc);

  edm::ParameterSetDescription ledge_desc;
  ledge_desc.add<double>("RangeStart", 0);
  ledge_desc.add<double>("RangeEnd", 0);
  edm::ParameterSetDescription ledge_fit_desc;
  ledge_fit_desc.add<double>("Constant", 0);
  ledge_fit_desc.add<double>("Mean", 0);
  ledge_fit_desc.add<double>("Sigma", 0);
  ledge_desc.add<edm::ParameterSetDescription>("Fit", ledge_fit_desc);
  desc.addVPSet("RDimWCoeff", ledge_desc);

  descriptions.add("RDimDetDigitizer", desc);
}

void DiamondDigiProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  using namespace edm;
  if (!rndEngine_) {
    Service<RandomNumberGenerator> rng;
    if (!rng.isAvailable()) {
      throw cms::Exception("Configuration")
          << "This class requires the RandomNumberGeneratorService\n"
             "which is not present in the configuration file.  You must add the service\n"
             "in the configuration file or remove the modules that require it.";
    }
    rndEngine_ = &(rng->getEngine(iEvent.streamID()));
  }

  // Step A: Get Inputs
  edm::Handle<edm::PSimHitContainer> cf;

  iEvent.getByToken(containerToken, cf);

  simhit_map SimHitMap;
  SimHitMap.clear();

  for (PSimHitContainer::const_iterator simhit = cf->begin(); simhit != cf->end(); ++simhit) {
    SimHitMap[simhit->detUnitId()].push_back(*simhit);
  }

  // Step B: LOOP on hits in event
  std::vector<edm::DetSet<CTPPSDiamondDigi>> theDigiVector;
  theDigiVector.reserve(400);
  theDigiVector.clear();

  for (auto const& it : SimHitMap) {
    edm::DetSet<CTPPSDiamondDigi> digi_collector(it.first);
    if (theAlgoMap.find(it.first) == theAlgoMap.end()) {
      theAlgoMap[it.first] =
          std::unique_ptr<DiamondDetDigitizer>(new DiamondDetDigitizer(conf_, *rndEngine_, it.first, iSetup));
    }

    (theAlgoMap.find(it.first)->second)->run(it.second, effMap[it.first], digi_collector.data);
    if (!digi_collector.data.empty()) {
      theDigiVector.push_back(digi_collector);
    }
  }

  std::unique_ptr<edm::DetSetVector<CTPPSDiamondDigi>> digi_output(
      new edm::DetSetVector<CTPPSDiamondDigi>(theDigiVector));
  iEvent.put(std::move(digi_output));
}

DEFINE_FWK_MODULE(DiamondDigiProducer);

#endif
