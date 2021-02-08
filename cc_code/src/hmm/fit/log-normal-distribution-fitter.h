/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

#ifndef WHATPROT_HMM_FIT_LOG_NORMAL_DISTRIBUTION_FITTER_H
#define WHATPROT_HMM_FIT_LOG_NORMAL_DISTRIBUTION_FITTER_H

// Local project headers:
#include "common/error-model.h"
#include "hmm/fit/distribution-fitter.h"

namespace whatprot {

class LogNormalDistributionFitter : public DistributionFitter {
public:
    LogNormalDistributionFitter();
    virtual void add_sample(double x, int n, double weight) override;
    virtual DistributionType get_type() const override;
    virtual double get_mu() const override;
    virtual double get_sigma() const override;
    double w_sum_log_x_over_n;
    double w_sum_log_x_over_n_sq;
    double total_weight;
};

}  // namespace whatprot

#endif  // WHATPROT_HMM_FIT_LOG_NORMAL_DISTRIBUTION_FITTER_H
