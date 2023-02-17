/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

// Defining symbols from header:
#include "cyclic-block-transition.h"

// Local project headers:
#include "hmm/state-vector/peptide-state-vector.h"
#include "hmm/step/block-transition.h"
#include "parameterization/fit/sequencing-model-fitter.h"

namespace whatprot {

CyclicBrokenNTransition::CyclicBrokenNTransition(double p_cyclic_block)
        : BrokenNTransition(p_cyclic_block) {}

void CyclicBrokenNTransition::improve_fit(
        const PeptideStateVector& forward_psv,
        const PeptideStateVector& backward_psv,
        const PeptideStateVector& next_backward_psv,
        unsigned int num_edmans,
        double probability,
        SequencingModelFitter* fitter) const {
    BrokenNTransition::improve_fit(forward_psv,
                                   backward_psv,
                                   next_backward_psv,
                                   num_edmans,
                                   probability,
                                   &fitter->p_cyclic_block_fit);
}

}  // namespace whatprot
