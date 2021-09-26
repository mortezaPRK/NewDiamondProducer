#include "SimPPS/PPSDiamondDigiProducer/interface/RDimDummyROCSimulator.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include <vector>
#include "TRandom.h"
#include <iostream>
#include <cmath>

RDimDummyROCSimulator::RDimDummyROCSimulator(const edm::ParameterSet &params, uint32_t det_id) : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");

  min_voltage_ = params.getParameter<double>("RDimMinVoltage");
  leading_edge_height_percentage_ = params.getParameter<double>("RDimLeadingEdgeHeightPercentage");
  k_coef_ = params.getParameter<double>("RDimKCoeff");
  w_coef_a_ = params.getParameter<double>("RDimWCoeffA");
  w_coef_b_ = params.getParameter<double>("RDimWCoeffB");
  w_coef_c_ = params.getParameter<double>("RDimWCoeffC");
  w_coef_d_ = params.getParameter<double>("RDimWCoeffD");
}

void RDimDummyROCSimulator::PopulateVTBins(std::vector<double> poly_coef,
                                           int num_of_bins,
                                           double min_bin_value,
                                           double max_bin_value) {
  // since the relation between voltage and time is complex, and finding the reverse function is impossible
  //  we have to create `num_of_bins` bins and calculate the value of voltage for a given time
  //  we then find the time for a given voltage by iterating over `v_t_bins`
  //  this is possible, since the relation between voltage and time is ascending for v < vmax
  //
  //  also, since we only need vmax to calculate trailing edge, we don't need to the values for v > vmx
  double bin_step = (max_bin_value - min_bin_value) / (2 * num_of_bins);
  double max_v = 0;
  int current_bin = 0;
  int poly_size = poly_coef.size();
  while (true) {
    double t_value = min_bin_value + bin_step * current_bin++;
    double v_value = 0;
    for (int j = 0; j < poly_size; j++) {
      v_value += std::pow(t_value, j) * poly_coef[j];
    }
    if (v_value < max_v) {
      break;
    }
    max_v = v_value;
    RDimDummyROCSimulator::v_t_bins.push_back(std::pair(v_value, t_value));
  }
}

void RDimDummyROCSimulator::ConvertChargeToSignal(
    const std::vector<std::pair<double, double>> &signals,
    std::map<unsigned short, std::vector<std::pair<int, double>>> &theSignalProvenance,
    std::vector<CTPPSDiamondDigi> &output_digi,
    std::vector<std::vector<std::pair<int, double>>> &output_digi_links) {
  int input_size = signals.size();
  bool is_multi_hit = input_size > 1;
  for (int i = 0; i < input_size; ++i) {
    std::pair<double, double> signal = signals[i];
    double vmax = calculateMaximumVoltage(signal.first);
    if (signal.first < min_voltage_)
      continue;

    double ledge = getLeadingEdge(vmax, signal.second);
    double tedge = getTrailingEdge(vmax);
    output_digi.push_back(CTPPSDiamondDigi(ledge, tedge, min_voltage_, is_multi_hit, 0));
  }
}

double RDimDummyROCSimulator::calculateMaximumVoltage(double charge) {
  // to determine the value of max voltage, we have to find the maximum value in bins
  double max_v = 0;
  for (auto const &x : RDimDummyROCSimulator::v_t_bins) {
    if (max_v < x.first) {
      max_v = x.first;
    }
  }
  return max_v;
}

double RDimDummyROCSimulator::getLeadingEdge(double vmax, double timeOfFlight) {
  // to determine the value of leading edge, we have to find the nearest bin
  //  the exact value is: vmax * leading_edge_height_percentage_
  // so we iterate over all bins until we pass the vmax * leading_edge_height_percentage_
  // this is possible, because the relation between voltage and time is always ascending
  double ledge_volate = leading_edge_height_percentage_ * vmax;
  for (auto const &x : RDimDummyROCSimulator::v_t_bins) {
    if (x.first > ledge_volate) {
      return x.second;
    }
  }
  return -1;
}

double RDimDummyROCSimulator::getTrailingEdge(double vmax) {
  // assuming vmax -> w relation: v = a * exp(b * w + c) + d
  // the reverse relation is: w[v] = (ln((v - d) / a) - c) / b
  // trailing edge then become: tedge = k + w[v]
  return k_coef_ + (std::log((vmax - w_coef_d_) / w_coef_a_) - w_coef_c_) / w_coef_b_;
}

std::vector<std::pair<double, double>> RDimDummyROCSimulator::v_t_bins;
