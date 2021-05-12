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

#include "SimDataFormats/CrossingFrame/interface/MixCollection.h"

#include "DataFormats/Common/interface/DetSet.h"
#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

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
  // std::map<uint32_t, std::unique_ptr<DiamondDetDigitizer>> theAlgoMap;

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
  // produces<edm::DetSetVector<CTPPSDiamondDigi>>();

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
  consumes<edm::PSimHitContainer>(edm::InputTag("g4SimHits","CTPPSTimingHits"));

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
}

DEFINE_FWK_MODULE(DiamondDigiProducer);

#endif
