#ifndef SimPPS_PPSDiamondDigiProducer_PPSDiamondDigiProducer_h
#define SimPPS_PPSDiamondDigiProducer_PPSDiamondDigiProducer_h

// -*- C++ -*-
//
// Package:    PPSDiamondDigiProducer
// Class:      CTPPSDiamondDigiProducer
//
/**\class CTPPSDiamondDigiProducer PPSDiamondDigiProducer.cc SimPPS/PPSDiamondDigiProducer/plugins/PPSDiamondDigiProducer.cc

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

class CTPPSDiamondDigiProducer : public edm::stream::EDProducer<> {
public:
  explicit CTPPSDiamondDigiProducer(const edm::ParameterSet&);
  ~CTPPSDiamondDigiProducer() override;
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

private:
  void produce(edm::Event&, const edm::EventSetup&) override;

  typedef std::map<unsigned int, std::vector<PSimHit>> simhit_map;
  typedef simhit_map::iterator simhit_map_iterator;

  edm::ParameterSet conf_;

  CLHEP::HepRandomEngine* rndEngine_ = nullptr;
  int verbosity_;
};

CTPPSDiamondDigiProducer::CTPPSDiamondDigiProducer(const edm::ParameterSet& conf) : conf_(conf) {}

CTPPSDiamondDigiProducer::~CTPPSDiamondDigiProducer() {}

void CTPPSDiamondDigiProducer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {}

void CTPPSDiamondDigiProducer::produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {}

DEFINE_FWK_MODULE(CTPPSDiamondDigiProducer);

#endif
