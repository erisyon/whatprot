/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin *
* Department: Oden Institute and Institute for Cellular and Molecular Biology
*
* PI: Edward Marcotte *
* Project: Protein Fluorosequencing *
\******************************************************************************/

// Boost unit test framework (recommended to be the first include):
#include <boost/test/unit_test.hpp>

// File under test:
#include "sequencing-model.h"

// Standard C++ library headers:
#include <cmath>
#include <functional>

namespace whatprot {

namespace {
using boost::unit_test::tolerance;
using std::exp;
using std::function;
using std::log;
const double TOL = 0.000000001;
}  // namespace

BOOST_AUTO_TEST_SUITE(parameterization_suite)
BOOST_AUTO_TEST_SUITE(model_suite)
BOOST_AUTO_TEST_SUITE(sequencing_model_suite)

BOOST_AUTO_TEST_CASE(distance_p_edman_failure_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.66;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_p_detach_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.66;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_p_initial_detach_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.66;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_p_initial_detach_decay_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.66;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_p_initial_block_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.66;
    sm2.p_cyclic_block = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_p_cyclic_block_test, *tolerance(TOL)) {
    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.66;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_with_channel_model_test, *tolerance(TOL)) {
    unsigned int num_channels = 1;
    unsigned int channel = 0;

    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;
    sm1.channel_models.push_back(new ChannelModel(channel, num_channels));
    sm1.channel_models[0]->p_bleach = 0.5;
    sm1.channel_models[0]->p_dud = 0.5;
    sm1.channel_models[0]->mu = 0.5;
    sm1.channel_models[0]->sig = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;
    sm2.channel_models.push_back(new ChannelModel(channel, num_channels));
    sm2.channel_models[0]->p_bleach = 0.5;
    sm2.channel_models[0]->p_dud = 0.66;
    sm2.channel_models[0]->mu = 0.5;
    sm2.channel_models[0]->sig = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_with_two_channel_models_test, *tolerance(TOL)) {
    unsigned int num_channels = 2;

    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;
    sm1.channel_models.push_back(new ChannelModel(0, num_channels));
    sm1.channel_models[0]->p_bleach = 0.5;
    sm1.channel_models[0]->p_dud = 0.5;
    sm1.channel_models[0]->mu = 0.5;
    sm1.channel_models[0]->sig = 0.5;
    sm1.channel_models.push_back(new ChannelModel(1, num_channels));
    sm1.channel_models[1]->p_bleach = 0.5;
    sm1.channel_models[1]->p_dud = 0.5;
    sm1.channel_models[1]->mu = 0.5;
    sm1.channel_models[1]->sig = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.5;
    sm2.p_detach.base = 0.5;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;
    sm2.channel_models.push_back(new ChannelModel(0, num_channels));
    sm2.channel_models[0]->p_bleach = 0.5;
    sm2.channel_models[0]->p_dud = 0.5;
    sm2.channel_models[0]->mu = 0.5;
    sm2.channel_models[0]->sig = 0.5;
    sm2.channel_models.push_back(new ChannelModel(1, num_channels));
    sm2.channel_models[1]->p_bleach = 0.5;
    sm2.channel_models[1]->p_dud = 0.66;
    sm2.channel_models[1]->mu = 0.5;
    sm2.channel_models[1]->sig = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_CASE(distance_max_no_sum_test, *tolerance(TOL)) {
    unsigned int num_channels = 2;

    SequencingModel sm1;
    sm1.p_edman_failure = 0.5;
    sm1.p_detach.base = 0.5;
    sm1.p_detach.initial = 0.5;
    sm1.p_detach.initial_decay = 0.5;
    sm1.p_initial_block = 0.5;
    sm1.p_cyclic_block = 0.5;
    sm1.channel_models.push_back(new ChannelModel(0, num_channels));
    sm1.channel_models[0]->p_bleach = 0.5;
    sm1.channel_models[0]->p_dud = 0.5;
    sm1.channel_models[0]->mu = 0.5;
    sm1.channel_models[0]->sig = 0.5;
    sm1.channel_models.push_back(new ChannelModel(1, num_channels));
    sm1.channel_models[1]->p_bleach = 0.5;
    sm1.channel_models[1]->p_dud = 0.5;
    sm1.channel_models[1]->mu = 0.5;
    sm1.channel_models[1]->sig = 0.5;

    SequencingModel sm2;
    sm2.p_edman_failure = 0.66;
    sm2.p_detach.base = 0.66;
    sm2.p_detach.initial = 0.5;
    sm2.p_detach.initial_decay = 0.5;
    sm2.p_initial_block = 0.5;
    sm2.p_cyclic_block = 0.5;
    sm2.channel_models.push_back(new ChannelModel(0, num_channels));
    sm2.channel_models[0]->p_bleach = 0.5;
    sm2.channel_models[0]->p_dud = 0.5;
    sm2.channel_models[0]->mu = 0.5;
    sm2.channel_models[0]->sig = 0.5;
    sm2.channel_models.push_back(new ChannelModel(1, num_channels));
    sm2.channel_models[1]->p_bleach = 0.5;
    sm2.channel_models[1]->p_dud = 0.66;
    sm2.channel_models[1]->mu = 0.5;
    sm2.channel_models[1]->sig = 0.5;

    BOOST_TEST(sm1.distance(sm2) == (0.66 - 0.5));
    BOOST_TEST(sm2.distance(sm1) == (0.66 - 0.5));
}

BOOST_AUTO_TEST_SUITE_END()  // sequencing_model_suite
BOOST_AUTO_TEST_SUITE_END()  // model_suite
BOOST_AUTO_TEST_SUITE_END()  // parameterization_suite

}  // namespace whatprot
