#ifndef SimPPS_PPSDiamondDigiProducer_RDim_PILE_UP_SIGNALS_H
#define SimPPS_PPSDiamondDigiProducer_RDim_PILE_UP_SIGNALS_H

#include <map>
#include "FWCore/ParameterSet/interface/ParameterSet.h"

class RDimPileUpSignals {
public:
  RDimPileUpSignals(const edm::ParameterSet &params, uint32_t det_id);

  void reset();

  void add(const std::map<unsigned short, double> &charge_induced, int PSimHitIndex);

  inline const std::map<unsigned short, double> &dumpSignal() { return the_diamond_charge_piled_up_map_; }

  inline std::map<unsigned short, std::vector<std::pair<int, double> > > &dumpLinks() {
    return the_diamond_charge_piled_up_map_links_;
  }

private:
  std::map<unsigned short, double> the_diamond_charge_piled_up_map_;
  std::map<unsigned short, std::vector<std::pair<int, double> > > the_diamond_charge_piled_up_map_links_;
  uint32_t det_id_;
  bool verbosity_;
};

#endif
