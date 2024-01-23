/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

#ifndef WHATPROT_COMMON_DYE_TRACK_H
#define WHATPROT_COMMON_DYE_TRACK_H

// Standard C++ library headers:
#include <functional>
#include <vector>

// Local project headers:
#include "common/dye-seq.h"
#include "util/vector-hash.h"

namespace whatprot {

class DyeTrack {
public:
    DyeTrack(unsigned int num_timesteps,
             unsigned int num_channels,
             const DyeSeq& dye_seq);
    DyeTrack(unsigned int num_timesteps,
             unsigned int num_channels,
             short* counts);
    DyeTrack(unsigned int num_timesteps, unsigned int num_channels);
    DyeTrack(const DyeTrack& other);
    DyeTrack(DyeTrack&& other);
    DyeTrack& operator=(DyeTrack&& other);
    bool operator==(const DyeTrack& other) const;
    short& operator()(int t, int c);
    short operator()(int t, int c) const;
    short* operator[](int t);
    const short* operator[](int t) const;

    std::vector<short> counts;
    unsigned int num_timesteps;
    unsigned int num_channels;
};

}  // namespace whatprot

// An std namespace injection is the accepted way of creating a new hash
// function.
namespace std {

template <>
struct hash<whatprot::DyeTrack> {
public:
    size_t operator()(const whatprot::DyeTrack& dye_track) const;

    hash<vector<short>> vector_hash;
};

}  // namespace std

#endif  // WHATPROT_COMMON_DYE_TRACK_H
