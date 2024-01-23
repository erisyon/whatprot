/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

// Defining symbols from header:
#include "radiometry-precomputations.h"

// Local project headers:
#include "common/radiometry.h"
#include "hmm/step/peptide-emission.h"
#include "parameterization/model/sequencing-model.h"
#include "parameterization/settings/sequencing-settings.h"

namespace whatprot {

RadiometryPrecomputations::RadiometryPrecomputations(
        const Radiometry& radiometry,
        const SequencingModel& seq_model,
        const SequencingSettings& seq_settings,
        unsigned int max_num_dyes) {
    for (unsigned int t = 0; t < radiometry.num_timesteps; t++) {
        peptide_emissions.push_back(new PeptideEmission(
                radiometry, t, max_num_dyes, seq_model, seq_settings));
    }
}

RadiometryPrecomputations::~RadiometryPrecomputations() {
    for (PeptideEmission* step : peptide_emissions) {
        delete step;
    }
}

}  // namespace whatprot
