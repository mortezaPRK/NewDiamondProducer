#ifndef RDIM_DUMMY_ROC_SIMULATION_H
#define RDIM_DUMMY_ROC_SIMULATION_H

#include <set>

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"

class RDimDummyROCSimulator {
public:
  RDimDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id);

  void ConvertChargeToHits(const std::vector<std::pair<double,double>> &signals,
                           std::map<unsigned short, std::vector<std::pair<int, double> > > &theSignalProvenance,
                           std::vector<CTPPSDiamondDigi> &output_digi,
                           std::vector<std::vector<std::pair<int, double> > > &output_digi_links);

  static void PopulateVTBins(std::vector<double> poly_coef, int num_of_bins, double min_bin_value, double max_bin_value);

private:
  uint32_t det_id_;
  int verbosity_;

  static std::vector<std::pair<double, double>> v_t_bins;
  double min_voltage_;
  double leading_edge_height_percentage_;
  double k_coef_;
  double w_coef_a_;
  double w_coef_b_;
  double w_coef_c_;
  double w_coef_d_;
  
  double calculateMaximumVoltage(double charge);
  double getLeadingEdge(double vmax, double timeOfFlight);
  double getTrailingEdge(double vmax);
};

#endif
