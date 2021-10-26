#ifndef RDIM_DUMMY_ROC_SIMULATION_H
#define RDIM_DUMMY_ROC_SIMULATION_H

#include <set>

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

namespace CLHEP {
  class HepRandomEngine;
}

class RDimDummyROCSimulator {
public:
  CLHEP::HepRandomEngine* rndEngine_ = nullptr;

  RDimDummyROCSimulator(const edm::ParameterSet &params,CLHEP::HepRandomEngine &rng, uint32_t det_id);

  std::vector<CTPPSDiamondDigi> ConvertChargesToSignal(const std::vector<std::pair<double,double>> &signals);

  static void PopulateVTBins(std::vector<edm::ParameterSet> poly_coef, int num_of_bins, double min_bin_value, double max_bin_value);

private:
  uint32_t det_id_;
  int verbosity_;

  static std::vector<std::pair<double, double>> v_t_bins;
  double min_voltage_;
  double leading_edge_height_percentage_;
  double k_coef_;
  std::vector<edm::ParameterSet> w_coef_;
  
  double calculateMaximumVoltage(double charge);
  double getLeadingEdge(double vmax, double time_of_flight);
  double getTrailingEdge(double vmax, double time_of_flight);
};

#endif
