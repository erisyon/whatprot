// Author: Matthew Beauregard Smith (UT Austin)
#include "error_model.h"

#include <cmath>
#include <functional>

namespace fluoroseq {

namespace {
using std::exp;
using std::function;
using std::log;
using std::sqrt;

double PI = 3.141592653589793238;
}  // namespace

ErrorModel::ErrorModel(double p_edman_failure,
                       double p_detach,
                       double p_bleach,
                       double p_dud,
                       DistributionType distribution_type,
                       double mu,
                       double sigma) : p_edman_failure(p_edman_failure),
                                       p_detach(p_detach),
                                       p_bleach(p_bleach),
                                       p_dud(p_dud),
                                       distribution_type(distribution_type),
                                       mu(mu),
                                       sigma(sigma) {}

function<double (double, int)> ErrorModel::pdf() const {
    switch(distribution_type) {
    case LOGNORMAL:
        double scale = mu;
        double sigma = sigma;
        double multiplier = 1.0 / (sigma * sqrt(2.0 * PI));
        return [scale,
                sigma,
                multiplier](double observed, int state) -> double {
            if (state > 0) {
                if (observed == 0.0) {
                    return 0.0;
                } else {
                    double unit_obs = observed / scale;
                    double offset = log(unit_obs) - log((double) state);
                    return (multiplier / unit_obs)
                           * exp(-(offset * offset) / (2.0 * sigma * sigma));
                }
            } else {
                if (observed == 0.0) {
                    return 1.0;
                } else {
                    return 0.0;
                }
            }
        };
    }
}

}  // namespace fluoroseq
