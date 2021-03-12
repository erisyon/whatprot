/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

#ifndef WHATPROT_HMM_STEP_DETACH_TRANSITION_H
#define WHATPROT_HMM_STEP_DETACH_TRANSITION_H

// Local project headers:
#include "hmm/fit/error-model-fitter.h"
#include "hmm/step/step.h"
#include "tensor/tensor.h"

namespace whatprot {

class DetachTransition : public Step {
public:
    DetachTransition(double p_detach);
    virtual void forward(int* edmans, Tensor* tsr) const override;
    virtual void backward(const Tensor& input,
                          int* edmans,
                          Tensor* output) const override;
    virtual void improve_fit(const Tensor& forward_tensor,
                             const Tensor& backward_tensor,
                             const Tensor& next_backward_tensor,
                             int edmans,
                             double probability,
                             ErrorModelFitter* fitter) const override;

    double p_detach;
};

}  // namespace whatprot

#endif  // WHATPROT_HMM_STEP_DETACH_TRANSITION_H