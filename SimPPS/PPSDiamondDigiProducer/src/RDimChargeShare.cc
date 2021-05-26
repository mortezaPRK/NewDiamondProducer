#include "SimPPS/PPSDiamondDigiProducer/interface/RDimChargeShare.h"
#include <iostream>
#include <fstream>

RDimChargeShare::RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  // TODO: read from config file
}

// retruns amount of charge absorbed by each section of the detector
// Map<part index, effective absorbed charge>
std::map<unsigned short, double> RDimChargeShare::Share(const std::vector<RDimSignalPoint> &charge_map) {
  std::map<unsigned short, double> theDiamondChargeMap;

  // RDimSignalPoint: An element charge point, with position, sigma from diffusion and tof
  for (std::vector<RDimSignalPoint>::const_iterator i = charge_map.begin(); i != charge_map.end(); ++i) {
    double hit_pos_x, hit_pos_y;

    CTPPSDiamondTopology::PartInfo relevant_part = theRPDiamondDetTopology_.getPartInvolved(
        (*i).Position().x(), (*i).Position().y(), (*i).Sigma(), hit_pos_x, hit_pos_y);

    // effFactor => same as edge factor
    double effic = relevant_part.effFactor();

    // part index => from 1 - 8
    unsigned short part_index = relevant_part.partIndex();

    double charge_in_part = (*i).Charge() * effic;

    theDiamondChargeMap[part_index] += charge_in_part;
  }

  return theDiamondChargeMap;
}
