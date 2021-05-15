#include "SimPPS/PPSDiamondDigiProducer/interface/RDimPileUpSignals.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

RDimPileUpSignals::RDimPileUpSignals(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RPixVerbosity");
}

void RDimPileUpSignals::reset() {
  the_diamond_charge_piled_up_map_.clear();
  the_diamond_charge_piled_up_map_links_.clear();
}

void RDimPileUpSignals::add(const std::map<unsigned short, double> &charge_induced, int PSimHitIndex) {
  for (std::map<unsigned short, double>::const_iterator i = charge_induced.begin(); i != charge_induced.end(); ++i) {
    the_diamond_charge_piled_up_map_[i->first] += i->second;
  }
}
