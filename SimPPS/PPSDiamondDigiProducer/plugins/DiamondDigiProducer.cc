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
#include "Geometry/VeryForwardGeometry/interface/CTPPSDiamondTopology.h"
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
  virtual void beginStream(edm::StreamID) override;
  virtual void endStream() override;

  typedef std::map<unsigned int, std::vector<PSimHit>> simhit_map;
  typedef simhit_map::iterator simhit_map_iterator;
  std::map<uint32_t, std::unique_ptr<DiamondDetDigitizer>> theAlgoMap;

  edm::ParameterSet conf_;

  CLHEP::HepRandomEngine* rndEngine_ = nullptr;
  edm::EDGetTokenT<std::vector<PSimHit>> tokenCrossingFramePPSDiamond;

  int verbosity_;
};

void DiamondDigiProducer::beginStream(edm::StreamID) {
  std::cout << "here at call bs";
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void DiamondDigiProducer::endStream() {
  std::cout << "here at end bs";
}

DiamondDigiProducer::DiamondDigiProducer(const edm::ParameterSet& conf) : conf_(conf) {
  produces<edm::DetSetVector<CTPPSDiamondDigi>>();

  // register data to consume
  // tokenCrossingFramePPSDiamond = consumes<std::vector<PSimHit>>(edm::InputTag("g4SimHitsCTPPSTimingHits"));
  
  // consumes<edm::DetSetVector<CTPPSDiamondDigi>>(edm::InputTag("g4SimHitsCTPPSTimingHits"));
  // consumes<std::vector<PSimHit>>(edm::InputTag("g4SimHitsCTPPSTimingHits"));
  // consumes<edm::PSimHitContainer>(edm::InputTag("g4SimHitsCTPPSTimingHits"));

  // consumes<edm::DetSetVector<CTPPSDiamondDigi>>(edm::InputTag("CTPPSTimingHits"));
  // consumes<std::vector<PSimHit>>(edm::InputTag("CTPPSTimingHits"));
  // consumes<edm::PSimHitContainer>(edm::InputTag("CTPPSTimingHits"));

  // consumes<edm::DetSetVector<CTPPSDiamondDigi>>(edm::InputTag("g4SimHits","CTPPSTimingHits"));
  // consumes<std::vector<PSimHit>>(edm::InputTag("g4SimHits","CTPPSTimingHits"));
  // consumes<edm::PSimHitContainer>(edm::InputTag("g4SimHits","CTPPSTimingHits"));

  // consumes<edm::DetSetVector<CTPPSDiamondDigi>>(edm::InputTag("g4SimHits","CTPPSHits"));
  // consumes<std::vector<PSimHit>>(edm::InputTag("g4SimHits","CTPPSHits"));
  // consumes<edm::PSimHitContainer>(edm::InputTag("g4SimHits","CTPPSHits"));
  
  verbosity_ = conf.getParameter<int>("RDimVerbosity");
  std::cout << "here at: " << __FUNCTION__ << '\n';
}

DiamondDigiProducer::~DiamondDigiProducer() {}

void DiamondDigiProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  std::cout << "here at: " << __FUNCTION__ << '\n';
  edm::ParameterSetDescription desc;
  desc.add<std::string>("InputCollection", "g4SimHitsCTPPSTimingHits");
  desc.add<int>("RDimVerbosity", 0);
  // desc.add<std::string>("mixLabel", "mix");
  descriptions.add("RDimDetDigitizer", desc);
}

void DiamondDigiProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
  std::cout << "here at: " << __FUNCTION__ << '\n';
  throw std::invalid_argument( "received negative value" );
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

  // get calibration DB
  // theGainCalibrationDB.getDB(iEvent, iSetup);

  // Step A: Get Inputs
  edm::Handle<PSimHit> cf;

  iEvent.getByToken(tokenCrossingFramePPSDiamond, cf);

  // MixCollection<PSimHit> allRDimHits{cf.product(), std::pair(0, 0)};

  //Loop on PSimHit
  simhit_map SimHitMap;
  SimHitMap.clear();

  MixCollection<PSimHit>::iterator isim;
  // for (isim = allRDimHits.begin(); isim != allRDimHits.end(); ++isim) {
  //   SimHitMap[(*isim).detUnitId()].push_back((*isim));
  // }

  // Step B: LOOP on hits in event
  std::vector<edm::DetSet<CTPPSDiamondDigi>> theDigiVector;
  theDigiVector.reserve(400);
  theDigiVector.clear();

  for (simhit_map_iterator it = SimHitMap.begin(); it != SimHitMap.end(); ++it) {
    edm::DetSet<CTPPSDiamondDigi> digi_collector(it->first);

    if (theAlgoMap.find(it->first) == theAlgoMap.end()) {
      theAlgoMap[it->first] = std::unique_ptr<DiamondDetDigitizer>(
          new DiamondDetDigitizer(conf_, *rndEngine_, it->first, iSetup));  //a digitizer for eny detector
    }

    std::vector<int> input_links;
    std::vector<std::vector<std::pair<int, double>>> output_digi_links;  // links to simhits

    (theAlgoMap.find(it->first)->second)->run(SimHitMap[it->first], input_links, digi_collector.data, output_digi_links);

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
