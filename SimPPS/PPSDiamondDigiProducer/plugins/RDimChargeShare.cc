#include "SimPPS/PPSDiamondDigiProducer/interface/RDimChargeShare.h"
#include <iostream>
#include <fstream>

RDimChargeShare::RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  // TODO: read from config file
}

// converts vector<num_of_electrons, 2d-position, depth> to map<pixel index, number of inducted electrons>
//
// every pixel has an index. here, we find whats is the relevant pixel based on 2d-position
//      and caculate the inducted electrons in that pixel
//
//
std::map<unsigned short, double> RDimChargeShare::Share(const std::vector<RDimSignalPoint> &charge_map) {
  std::map<unsigned short, double> theDiamondChargeMap;
  return theDiamondChargeMap;
}
