#include "SimPPS/PPSDiamondDigiProducer/interface/RDimDummyROCSimulator.h"

#include "DataFormats/CTPPSDigi/interface/CTPPSDiamondDigi.h"
#include <vector>
#include "TRandom.h"
#include <iostream>
#include <cmath>
#include <CLHEP/Random/RandGauss.h>

RDimDummyROCSimulator::RDimDummyROCSimulator(const edm::ParameterSet &params,
                                             CLHEP::HepRandomEngine &rng,
                                             uint32_t det_id)
    : det_id_(det_id) {
  verbosity_ = params.getParameter<int>("RDimVerbosity");
  rndEngine_ = &rng;
  min_voltage_ = params.getParameter<double>("RDimMinVoltage");
  leading_edge_height_percentage_ = params.getParameter<double>("RDimLeadingEdgeHeightPercentage");
  k_coef_ = params.getParameter<double>("RDimKCoeff");
  w_coef_ = params.getParameter<std::vector<edm::ParameterSet>>("RDimWCoeff");
}

void RDimDummyROCSimulator::PopulateVTBins(std::vector<edm::ParameterSet> poly_coef,
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
  while (true) {
    double t_value = min_bin_value + bin_step * current_bin++;
    double v_value = 0;
    for (auto const &it : poly_coef) {
      unsigned int pow = it.getParameter<unsigned int>("Power");
      double coeff = it.getParameter<double>("Coeff");
      v_value += std::pow(t_value, pow) * coeff;
    }
    if (v_value < max_v) {
      break;
    }
    max_v = v_value;
    RDimDummyROCSimulator::v_t_bins.push_back(std::pair(v_value, t_value));
  }
}

std::vector<CTPPSDiamondDigi> RDimDummyROCSimulator::ConvertChargesToSignal(
    const std::vector<std::pair<double, double>> &signals) {
  int input_size = signals.size();
  std::vector<CTPPSDiamondDigi> out;
  out.reserve(input_size);

  bool is_multi_hit = input_size > 1;
  for (int i = 0; i < input_size; ++i) {
    std::pair<double, double> signal = signals[i];
    double vmax = calculateMaximumVoltage(signal.first);
    if (signal.first < min_voltage_)
      continue;

    double ledge = getLeadingEdge(vmax, signal.second);
    double tedge = getTrailingEdge(vmax, signal.second);
    out.push_back(CTPPSDiamondDigi(ledge * 1000, tedge * 1000, min_voltage_, is_multi_hit, 0));
  }
  return out;
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

double RDimDummyROCSimulator::getLeadingEdge(double vmax, double time_of_flight) {
  // to determine the value of leading edge, we have to find the nearest bin
  //  the exact value is: vmax * leading_edge_height_percentage_
  // so we iterate over all bins until we pass the vmax * leading_edge_height_percentage_
  // this is possible, because the relation between voltage and time is always ascending
  double ledge_volate = leading_edge_height_percentage_ * vmax;
  for (auto const &x : RDimDummyROCSimulator::v_t_bins) {
    if (x.first > ledge_volate) {
      return x.second + time_of_flight;
    }
  }
  return -1;
}

double RDimDummyROCSimulator::getTrailingEdge(double vmax, double time_of_flight) {
  for (auto const &x : w_coef_) {
    double start = x.getParameter<double>("RangeStart");
    double end = x.getParameter<double>("RangeEnd");
    if (vmax < start || vmax > end) {
      continue;
    }
    edm::ParameterSet fit = x.getParameter<edm::ParameterSet>("Fit");
    double constant = fit.getParameter<double>("Constant");
    double mean = fit.getParameter<double>("Mean");
    double sigma = fit.getParameter<double>("Sigma");
    return time_of_flight + k_coef_ + randomGaus(constant, mean, sigma);
  }
  return -1;
}

double RDimDummyROCSimulator::randomGaus(double constant, double mean, double sigma) {
  double result = CLHEP::RandGauss::shoot(rndEngine_, mean, sigma);
  return result * 1000000000;
}

std::vector<std::pair<double, double>> RDimDummyROCSimulator::v_t_bins;
