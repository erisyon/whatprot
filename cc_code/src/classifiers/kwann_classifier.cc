// Author: Matthew Beauregard Smith (UT Austin)
#include "kwann_classifier.h"

#include <functional>
#include <queue>
#include <unordered_map>
#include <vector>

#include "common/radiometry.h"
#include "common/scored_classification.h"
#include "common/sourced_data.h"
#include "flann/flann.hpp"

namespace {
using flann::FLANN_CHECKS_UNLIMITED;
using flann::Index;
using flann::KDTreeIndexParams;
using flann::L2;
using flann::Matrix;
using flann::SearchParams;
using std::function;
using std::greater;  // defined in <functional>
using std::priority_queue;
using std::unordered_map;
using std::vector;
}  // namespace

namespace fluoroseq {

KWANNClassifier::KWANNClassifier(
        int num_timesteps,
        int num_channels,
        function<double (double, int)> pdf,
        int k,
        int num_train,
        SourcedData<DyeTrack*, SourceCountHitsList<int>*>** dye_tracks)
        : num_timesteps(num_timesteps),
          num_channels(num_channels),
          pdf(pdf),
          k(k),
          num_train(num_train),
          dye_tracks(dye_tracks) {
    int stride = num_timesteps * num_channels;
    double* raw_dataset = new double[num_train * stride];
    for (int i = 0; i < num_train; i++) {
        for (int j = 0; j < stride; j++) {
            double count = (double) dye_tracks[i]->value->counts[j];
            raw_dataset[i * stride + j] = count;
        }
    }
    dataset = new Matrix<double>(raw_dataset, num_train, stride);
    index = new Index<L2<double>>(*dataset,
                                  KDTreeIndexParams(1));  // number of kdtrees.
    index->buildIndex();
}

KWANNClassifier::~KWANNClassifier() {
    delete[] dataset->ptr();
    delete dataset;
    delete index;
}

double KWANNClassifier::classify_helper(
        const Radiometry& radiometry,
        unordered_map<int, double>* id_score_map) {
    Matrix<double> query(radiometry.intensities,
                         1,  // num rows (num queries)
                         num_timesteps * num_channels);  // num columns
    Matrix<int> indices(new int[k],
                        1,  // num rows (num queries)
                        k);  // num results per query
    Matrix<double> dists_sq(new double[k],
                            1,  // num rows (num queries)
                            k);  // num results per query
    index->knnSearch(query,
                     indices,
                     dists_sq,
                     k,
                     SearchParams(FLANN_CHECKS_UNLIMITED));
    delete[] dists_sq.ptr();
    double total_score = 0.0;
    unordered_map<int, int> id_hits_map;
    for (int i = 0; i < k; i++) {
        int index = indices[0][i];
        SourcedData<DyeTrack*,
                    SourceCountHitsList<int>*>* dye_track = dye_tracks[index];
        double weight = 1.0;
        for (int j = 0; j < num_timesteps * num_channels; j++) {
            weight *= pdf(radiometry.intensities[j],
                          dye_track->value->counts[j]);
        }
        for (int j = 0; j < dye_track->source->num_sources; j++) {
            int id = dye_track->source->sources[j]->source;
            double count = (double) dye_track->source->sources[j]->count;
            double hits = (double) dye_track->source->sources[j]->hits;
            total_score += weight * hits;
            (*id_score_map)[id] += weight * hits / count;
        }
    }
    delete[] indices.ptr();
    return total_score;
}

ScoredClassification KWANNClassifier::classify(const Radiometry& radiometry) {
    unordered_map<int, double> id_score_map;
    double total_score = classify_helper(radiometry, &id_score_map);
    int best_id = -1;
    double best_score = -1.0;
    for (const auto& id_and_score : id_score_map) {
        double id = id_and_score.first;
        double score = id_and_score.second;
        if (score > best_score) {
            best_id = id;
            best_score = score;
        }
    }
    ScoredClassification result(best_id, best_score, total_score);
    // This next thing is a bit of a hack. Sometimes the candidates have a total
    // score of 0.0, which causes the adjusted score to be nan. This can mess
    // things up for us later. The best way to deal with it is to just set the
    // score to 0.0 when this happens. It might be better though to find a way
    // to avoid this situation.
    if (isnan(result.adjusted_score())) {
        result.score = 0.0;
        result.total = 1.0;
    }
    return result;
}

vector<ScoredClassification> KWANNClassifier::classify(
        const Radiometry& radiometry,
        int h) {
    unordered_map<int, double> id_score_map;
    double total_score = classify_helper(radiometry, &id_score_map);
    priority_queue<ScoredClassification,
                   vector<ScoredClassification>,
                   greater<ScoredClassification>> pq;
    for (const auto& id_and_score : id_score_map) {
        double id = id_and_score.first;
        double score = id_and_score.second;
        if (pq.size() < h) {
            pq.push(ScoredClassification(id, score, total_score));
        } else if (score > pq.top().score) {
            pq.push(ScoredClassification(id, score, total_score));
            pq.pop();
        }
    }
    vector<ScoredClassification> results;
    results.reserve(pq.size());
    while (!pq.empty()) {
        results.push_back(pq.top());
        pq.pop();
    }
    return results;
}

ScoredClassification* KWANNClassifier::classify(int num_radiometries, 
                                                Radiometry** radiometries) {
    ScoredClassification* results = new ScoredClassification[num_radiometries];
    for (int i = 0; i < num_radiometries; i++) {
        results[i] = classify(*radiometries[i]);
    }
    return results;
}

}  // namespace fluoroseq