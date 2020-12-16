#include "SimPPS/PPSDiamondDigiProducer/interface/RDimChargeShare.h"
#include <iostream>
#include <fstream>

RDimChargeShare::RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  // TODO: read from config file
}

// converts vector<num_of_electrons, 2d-position, depth> to map<part index, number of inducted electrons>
//
// every pixel has an index. here, we find whats is the relevant pixel based on 2d-position
//      and caculate the inducted electrons in that pixel
//
//
std::map<unsigned short, double> RDimChargeShare::Share(const std::vector<RDimSignalPoint> &charge_map) {
  std::map<unsigned short, double> theDiamondChargeMap;

  for (std::vector<RPixSignalPoint>::const_iterator i = charge_map.begin(); i != charge_map.end(); ++i) {
    double hit_pos_x, hit_pos_y;

    CTPPSDiamondTopology::PartInfo relevant_part = theRPDiamondDetTopology_.getPartInvolved(
      (*i).Position().x(), 
      (*i).Position().y(), 
      (*i).Sigma(), 
      hit_pos_x, 
      hit_pos_y
    );

    double effic = relevant_part.effFactor();

    unsigned short part_index = relevant_part.partIndex();

    double charge_in_part = (*i).Charge() * effic;

    theDiamondChargeMap[part_index] += charge_in_part;
  }

  return theDiamondChargeMap;
}
