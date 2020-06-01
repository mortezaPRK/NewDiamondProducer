#include "SimPPS/PPSDiamondDigiProducer/interface/RDimChargeShare.h"
#include <iostream>
#include <fstream>

RDimChargeShare::RDimChargeShare(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  // TODO: read from config file
}

std::map<unsigned short, double> RDimChargeShare::Share(const std::vector<RDimSignalPoint> &charge_map) {
  std::map<unsigned short, double> theDiamondChargeMap;
  return theDiamondChargeMap;
}
