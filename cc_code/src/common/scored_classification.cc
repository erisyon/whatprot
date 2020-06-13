// Author: Matthew Beauregard Smith (UT Austin)
#include "scored_classification.h"

#include <climits>

#include "common/dye_seq.h"

namespace fluoroseq {

ScoredClassification::ScoredClassification(int id,
                                           double score,
                                           double total) : id(id),
                                                           score(score),
                                                           total(total) {}

ScoredClassification::ScoredClassification() : id(-1),
                                               score(INT_MIN),
                                               total(0.0) {}

double ScoredClassification::adjusted_score() const {
    return score / total;
}

bool operator>(const ScoredClassification& x, const ScoredClassification& y) {
    return (x.score > y.score);
}

}  // namespace fluoroseq
