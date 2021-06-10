/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

// These tests may benefit from using a mocking framework. If a mocking
// framework is added to this code base in the future many of these tests should
// be revisited with that in mind.

// Boost unit test framework (recommended to be the first include):
#include <boost/test/unit_test.hpp>

// File under test:
#include "peptide-emission.h"

// Standard C++ library headers:
#include <functional>

// External headers:
#include "fakeit.hpp"

// Local project headers:
#include "common/radiometry.h"
#include "parameterization/fit/log-normal-distribution-fitter.h"
#include "parameterization/fit/sequencing-model-fitter.h"
#include "parameterization/model/sequencing-model.h"
#include "tensor/tensor.h"
#include "test-util/fakeit.h"

namespace whatprot {

namespace {
using boost::unit_test::tolerance;
using fakeit::Fake;
using fakeit::Mock;
using fakeit::Verify;
using fakeit::VerifyNoOtherInvocations;
using fakeit::When;
using std::function;
using whatprot::test_util::Close;
const double TOL = 0.000000001;
}  // namespace

BOOST_AUTO_TEST_SUITE(hmm_suite)
BOOST_AUTO_TEST_SUITE(step_suite)
BOOST_AUTO_TEST_SUITE(peptide_emission_suite)

BOOST_AUTO_TEST_CASE(constructor_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf)).AlwaysReturn(0.5);
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    BOOST_TEST(e.num_channels == num_channels);
    BOOST_TEST(e.max_num_dyes == max_num_dyes);
    BOOST_TEST(e.values[0] == 0.5);
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_timesteps_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 3;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(1, 0) = 1.0;
    rad(2, 0) = 2.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    BOOST_TEST(e.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(e.prob(1, 0, 0) == cm_mock.get().pdf(1.0, 0));
    BOOST_TEST(e.prob(2, 0, 0) == cm_mock.get().pdf(2.0, 0));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_timesteps_const_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 3;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(1, 0) = 1.0;
    rad(2, 0) = 2.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    const PeptideEmission& ce = e;
    BOOST_TEST(ce.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(ce.prob(1, 0, 0) == cm_mock.get().pdf(1.0, 0));
    BOOST_TEST(ce.prob(2, 0, 0) == cm_mock.get().pdf(2.0, 0));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_channels_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 3;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(0, 2) = 0.2;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    BOOST_TEST(e.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(e.prob(0, 1, 0) == cm_mock.get().pdf(0.1, 0));
    BOOST_TEST(e.prob(0, 2, 0) == cm_mock.get().pdf(0.2, 0));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_channels_const_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 3;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(0, 2) = 0.2;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    const PeptideEmission& ce = e;
    BOOST_TEST(ce.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(ce.prob(0, 1, 0) == cm_mock.get().pdf(0.1, 0));
    BOOST_TEST(ce.prob(0, 2, 0) == cm_mock.get().pdf(0.2, 0));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_channels_different_pdfs_test,
                     *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 3;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(0, 2) = 0.2;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock_0;
    When(Method(cm_mock_0, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock_0.get());
    Mock<ChannelModel> cm_mock_1;
    When(Method(cm_mock_1, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed * 1.9 + 0.098;
            });
    seq_model.channel_models.push_back(&cm_mock_1.get());
    Mock<ChannelModel> cm_mock_2;
    When(Method(cm_mock_2, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed * 2.7 + 0.187;
            });
    seq_model.channel_models.push_back(&cm_mock_2.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    BOOST_TEST(e.prob(0, 0, 0) == cm_mock_0.get().pdf(0.0, 0));
    BOOST_TEST(e.prob(0, 1, 0) == cm_mock_1.get().pdf(0.1, 0));
    BOOST_TEST(e.prob(0, 2, 0) == cm_mock_2.get().pdf(0.2, 0));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_dye_counts_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    int max_num_dyes = 2;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return 1.0 / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.max_num_dyes == max_num_dyes);
    BOOST_TEST(e.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(e.prob(0, 0, 1) == cm_mock.get().pdf(0.0, 1));
    BOOST_TEST(e.prob(0, 0, 2) == cm_mock.get().pdf(0.0, 2));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_dye_counts_const_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    int max_num_dyes = 2;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return 1.0 / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.max_num_dyes == max_num_dyes);
    const PeptideEmission& ce = e;
    BOOST_TEST(ce.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(ce.prob(0, 0, 1) == cm_mock.get().pdf(0.0, 1));
    BOOST_TEST(ce.prob(0, 0, 2) == cm_mock.get().pdf(0.0, 2));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_everything_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 2;
    unsigned int num_channels = 2;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(1, 0) = 1.0;
    rad(1, 1) = 1.1;
    int max_num_dyes = 1;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return (observed + 0.042) / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    BOOST_TEST(e.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(e.prob(0, 0, 1) == cm_mock.get().pdf(0.0, 1));
    BOOST_TEST(e.prob(0, 1, 0) == cm_mock.get().pdf(0.1, 0));
    BOOST_TEST(e.prob(0, 1, 1) == cm_mock.get().pdf(0.1, 1));
    BOOST_TEST(e.prob(1, 0, 0) == cm_mock.get().pdf(1.0, 0));
    BOOST_TEST(e.prob(1, 0, 1) == cm_mock.get().pdf(1.0, 1));
    BOOST_TEST(e.prob(1, 1, 0) == cm_mock.get().pdf(1.1, 0));
    BOOST_TEST(e.prob(1, 1, 1) == cm_mock.get().pdf(1.1, 1));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(prob_multiple_everything_const_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 2;
    unsigned int num_channels = 2;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(1, 0) = 1.0;
    rad(1, 1) = 1.1;
    int max_num_dyes = 1;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return (observed + 0.042) / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int expected_size = num_timesteps * num_channels * (max_num_dyes + 1);
    BOOST_TEST(e.values.size() == expected_size);
    BOOST_TEST(e.num_timesteps == num_timesteps);
    const PeptideEmission& ce = e;
    BOOST_TEST(ce.prob(0, 0, 0) == cm_mock.get().pdf(0.0, 0));
    BOOST_TEST(ce.prob(0, 0, 1) == cm_mock.get().pdf(0.0, 1));
    BOOST_TEST(ce.prob(0, 1, 0) == cm_mock.get().pdf(0.1, 0));
    BOOST_TEST(ce.prob(0, 1, 1) == cm_mock.get().pdf(0.1, 1));
    BOOST_TEST(ce.prob(1, 0, 0) == cm_mock.get().pdf(1.0, 0));
    BOOST_TEST(ce.prob(1, 0, 1) == cm_mock.get().pdf(1.0, 1));
    BOOST_TEST(ce.prob(1, 1, 0) == cm_mock.get().pdf(1.1, 0));
    BOOST_TEST(ce.prob(1, 1, 1) == cm_mock.get().pdf(1.1, 1));
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_trivial_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return 0.5;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    psv.tensor[loc] = 3.14;  // loc is {0, 0}
    unsigned int edmans = 0;
    e.forward(&edmans, &psv);
    BOOST_TEST(psv.tensor[loc]
               == 3.14 * cm_mock.get().pdf(1.0, 0));  // loc is {0, 0}
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_tsr_reuse_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return 0.5;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    psv.tensor[loc] = 3.14;  // loc is {0, 0}
    unsigned int edmans = 0;
    e.forward(&edmans, &psv);
    e.forward(&edmans, &psv);
    BOOST_TEST(psv.tensor[loc]
               == 3.14 * cm_mock.get().pdf(1.0, 0)
                          * cm_mock.get().pdf(1.0, 0));  // loc is {0, 0}
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_multiple_timesteps_test,
                     *tolerance(TOL)) {
    unsigned int num_timesteps = 3;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(1, 0) = 1.0;
    rad(2, 0) = 2.0;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    psv.tensor[loc] = 13.0;  // loc is {0, 0}
    loc[0] = 1;
    psv.tensor[loc] = 13.1;  // loc is {1, 0}
    loc[0] = 2;
    psv.tensor[loc] = 13.2;  // loc is {2, 0}
    unsigned int edmans = 2;
    e.forward(&edmans, &psv);
    loc[0] = 0;
    BOOST_TEST(psv.tensor[loc]
               == 13.0 * cm_mock.get().pdf(2.0, 0));  // loc is {0, 0}
    loc[0] = 1;
    BOOST_TEST(psv.tensor[loc]
               == 13.1 * cm_mock.get().pdf(2.0, 0));  // loc is {1, 0}
    loc[0] = 2;
    BOOST_TEST(psv.tensor[loc]
               == 13.2 * cm_mock.get().pdf(2.0, 0));  // loc is {2, 0}
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_multiple_channels_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 3;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(0, 2) = 0.2;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 1;
    shape[2] = 1;
    shape[3] = 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    loc[2] = 0;
    loc[3] = 0;
    psv.tensor[loc] = 13.0;  // loc is {0, 0, 0, 0}
    unsigned int edmans = 0;
    e.forward(&edmans, &psv);
    // loc is {0, 0, 0, 0}
    BOOST_TEST(psv.tensor[loc]
               == 13.0 * cm_mock.get().pdf(0.0, 0) * cm_mock.get().pdf(0.1, 0)
                          * cm_mock.get().pdf(0.2, 0));
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_multiple_channels_different_pdfs_test,
                     *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 3;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(0, 2) = 0.2;
    int max_num_dyes = 0;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock_0;
    When(Method(cm_mock_0, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed + 0.042;
            });
    seq_model.channel_models.push_back(&cm_mock_0.get());
    Mock<ChannelModel> cm_mock_1;
    When(Method(cm_mock_1, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed * 1.9 + 0.098;
            });
    seq_model.channel_models.push_back(&cm_mock_1.get());
    Mock<ChannelModel> cm_mock_2;
    When(Method(cm_mock_2, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return observed * 2.7 + 0.187;
            });
    seq_model.channel_models.push_back(&cm_mock_2.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 1;
    shape[2] = 1;
    shape[3] = 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    loc[2] = 0;
    loc[3] = 0;
    psv.tensor[loc] = 13.0;  // loc is {0, 0, 0, 0}
    unsigned int edmans = 0;
    e.forward(&edmans, &psv);
    // loc is {0, 0, 0, 0}
    BOOST_TEST(psv.tensor[loc]
               == 13.0 * cm_mock_0.get().pdf(0.0, 0)
                          * cm_mock_1.get().pdf(0.1, 0)
                          * cm_mock_2.get().pdf(0.2, 0));
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_multiple_dye_counts_test,
                     *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    int max_num_dyes = 2;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return 1.0 / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = max_num_dyes + 1;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    psv.tensor[loc] = 13.0;  // loc is {0, 0}
    loc[1] = 1;
    psv.tensor[loc] = 13.1;  // loc is {0, 1}
    loc[1] = 2;
    psv.tensor[loc] = 13.2;  // loc is {0, 2}
    unsigned int edmans = 0;
    e.forward(&edmans, &psv);
    loc[0] = 0;
    loc[1] = 0;
    BOOST_TEST(psv.tensor[loc]
               == 13.0 * cm_mock.get().pdf(0.0, 0));  // loc is {0, 0}
    loc[1] = 1;
    BOOST_TEST(psv.tensor[loc]
               == 13.1 * cm_mock.get().pdf(0.0, 1));  // loc is {0, 1}
    loc[1] = 2;
    BOOST_TEST(psv.tensor[loc]
               == 13.2 * cm_mock.get().pdf(0.0, 2));  // loc is {0, 2}
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(forward_in_place_multiple_everything_test,
                     *tolerance(TOL)) {
    unsigned int num_timesteps = 2;
    unsigned int num_channels = 2;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 0.0;
    rad(0, 1) = 0.1;
    rad(1, 0) = 1.0;
    rad(1, 1) = 1.1;
    int max_num_dyes = 1;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf))
            .AlwaysDo([](double observed, int state) -> double {
                return (observed + 0.042) / (double)(state + 7);
            });
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = 2;
    shape[2] = 2;
    PeptideStateVector psv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    loc[2] = 0;
    psv.tensor[loc] = 7.000;  // loc is {0, 0, 0}
    loc[2] = 1;
    psv.tensor[loc] = 7.001;  // loc is {0, 0, 1}
    loc[1] = 1;
    loc[2] = 0;
    psv.tensor[loc] = 7.010;  // loc is {0, 1, 0}
    loc[2] = 1;
    psv.tensor[loc] = 7.011;  // loc is {0, 1, 1}
    loc[0] = 1;
    loc[1] = 0;
    loc[2] = 0;
    psv.tensor[loc] = 7.100;  // loc is {1, 0, 0}
    loc[2] = 1;
    psv.tensor[loc] = 7.101;  // loc is {1, 0, 1}
    loc[1] = 1;
    loc[2] = 0;
    psv.tensor[loc] = 7.110;  // loc is {1, 1, 0}
    loc[2] = 1;
    psv.tensor[loc] = 7.111;  // loc is {1, 1, 1}
    unsigned int edmans = 1;
    e.forward(&edmans, &psv);
    loc[0] = 0;
    loc[1] = 0;
    loc[2] = 0;
    // loc is {0, 0, 0}
    BOOST_TEST(psv.tensor[loc]
               == 7.000 * cm_mock.get().pdf(1.0, 0)
                          * cm_mock.get().pdf(1.1, 0));
    loc[2] = 1;
    // loc is {0, 0, 1}
    BOOST_TEST(psv.tensor[loc]
               == 7.001 * cm_mock.get().pdf(1.0, 0)
                          * cm_mock.get().pdf(1.1, 1));
    loc[1] = 1;
    loc[2] = 0;
    // loc is {0, 1, 0}
    BOOST_TEST(psv.tensor[loc]
               == 7.010 * cm_mock.get().pdf(1.0, 1)
                          * cm_mock.get().pdf(1.1, 0));
    loc[2] = 1;
    // loc is {0, 1, 1}
    BOOST_TEST(psv.tensor[loc]
               == 7.011 * cm_mock.get().pdf(1.0, 1)
                          * cm_mock.get().pdf(1.1, 1));
    loc[0] = 1;
    loc[1] = 0;
    loc[2] = 0;
    // loc is {1, 0, 0}
    BOOST_TEST(psv.tensor[loc]
               == 7.100 * cm_mock.get().pdf(1.0, 0)
                          * cm_mock.get().pdf(1.1, 0));
    loc[2] = 1;
    // loc is {1, 0, 1}
    BOOST_TEST(psv.tensor[loc]
               == 7.101 * cm_mock.get().pdf(1.0, 0)
                          * cm_mock.get().pdf(1.1, 1));
    loc[1] = 1;
    loc[2] = 0;
    // loc is {1, 1, 0}
    BOOST_TEST(psv.tensor[loc]
               == 7.110 * cm_mock.get().pdf(1.0, 1)
                          * cm_mock.get().pdf(1.1, 0));
    loc[2] = 1;
    // loc is {1, 1, 1}
    BOOST_TEST(psv.tensor[loc]
               == 7.111 * cm_mock.get().pdf(1.0, 1)
                          * cm_mock.get().pdf(1.1, 1));
    delete[] loc;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(improve_fit_simple_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.009;
    int max_num_dyes = 2;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf)).AlwaysReturn(0.5);
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = max_num_dyes + 1;
    PeptideStateVector fpsv(order, shape);
    PeptideStateVector bpsv(order, shape);
    PeptideStateVector nbpsv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    fpsv.tensor[loc] = 1.72;  // loc is {0, 0}
    bpsv.tensor[loc] = 2.72;
    nbpsv.tensor[loc] = 3.72;
    loc[1] = 1;
    fpsv.tensor[loc] = 1.36;  // loc is {0, 1}
    bpsv.tensor[loc] = 2.36;
    nbpsv.tensor[loc] = 3.36;
    loc[1] = 2;
    fpsv.tensor[loc] = 1.18;  // loc is {0, 2}
    bpsv.tensor[loc] = 2.18;
    nbpsv.tensor[loc] = 3.18;
    delete[] loc;
    unsigned int edmans = 0;
    double probability = 3.14159;
    SequencingModelFitter smf;
    smf.channel_fits.push_back(new ChannelModelFitter());
    LogNormalDistributionFitter* original_dist_fit =
            smf.channel_fits[0]->distribution_fit;
    Mock<LogNormalDistributionFitter> df_mock;
    Fake(Method(df_mock, add_sample));
    smf.channel_fits[0]->distribution_fit = &df_mock.get();
    e.improve_fit(fpsv, bpsv, nbpsv, edmans, probability, &smf);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.009, TOL),
                          0,
                          Close(1.72 * 2.72 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.009, TOL),
                          1,
                          Close(1.36 * 2.36 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.009, TOL),
                          2,
                          Close(1.18 * 2.18 / 3.14159, TOL)))
            .Exactly(1);
    VerifyNoOtherInvocations(df_mock);
    smf.channel_fits[0]->distribution_fit =
            original_dist_fit;  // This avoids breaking cleanup.
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(improve_fit_multiple_dye_colors_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 1;
    unsigned int num_channels = 2;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.009;
    rad(0, 1) = 1.019;
    int max_num_dyes = 1;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf)).AlwaysReturn(0.5);
    seq_model.channel_models.push_back(&cm_mock.get());
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = max_num_dyes + 1;
    shape[2] = max_num_dyes + 1;
    PeptideStateVector fpsv(order, shape);
    PeptideStateVector bpsv(order, shape);
    PeptideStateVector nbpsv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    loc[2] = 0;
    fpsv.tensor[loc] = 1.72;  // loc is {0, 0, 0}
    bpsv.tensor[loc] = 2.72;
    nbpsv.tensor[loc] = 3.72;
    loc[2] = 1;
    fpsv.tensor[loc] = 1.64;  // loc is {0, 0, 1}
    bpsv.tensor[loc] = 2.64;
    nbpsv.tensor[loc] = 3.64;
    loc[1] = 1;
    loc[2] = 0;
    fpsv.tensor[loc] = 1.36;  // loc is {0, 1, 0}
    bpsv.tensor[loc] = 2.36;
    nbpsv.tensor[loc] = 3.36;
    loc[2] = 1;
    fpsv.tensor[loc] = 1.25;  // loc is {0, 1, 1}
    bpsv.tensor[loc] = 2.25;
    nbpsv.tensor[loc] = 3.25;
    delete[] loc;
    unsigned int edmans = 0;
    double probability = 3.14159;
    SequencingModelFitter smf;
    smf.channel_fits.push_back(new ChannelModelFitter());
    smf.channel_fits.push_back(new ChannelModelFitter());
    LogNormalDistributionFitter* original_dist_fit_0 =
            smf.channel_fits[0]->distribution_fit;
    Mock<LogNormalDistributionFitter> df_mock_0;
    Fake(Method(df_mock_0, add_sample));
    smf.channel_fits[0]->distribution_fit = &df_mock_0.get();
    LogNormalDistributionFitter* original_dist_fit_1 =
            smf.channel_fits[1]->distribution_fit;
    Mock<LogNormalDistributionFitter> df_mock_1;
    Fake(Method(df_mock_1, add_sample));
    smf.channel_fits[1]->distribution_fit = &df_mock_1.get();
    e.improve_fit(fpsv, bpsv, nbpsv, edmans, probability, &smf);
    Verify(Method(df_mock_0, add_sample)
                   .Using(Close(1.009, TOL),
                          0,
                          Close(1.72 * 2.72 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_1, add_sample)
                   .Using(Close(1.019, TOL),
                          0,
                          Close(1.72 * 2.72 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_0, add_sample)
                   .Using(Close(1.009, TOL),
                          0,
                          Close(1.64 * 2.64 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_1, add_sample)
                   .Using(Close(1.019, TOL),
                          1,
                          Close(1.64 * 2.64 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_0, add_sample)
                   .Using(Close(1.009, TOL),
                          1,
                          Close(1.36 * 2.36 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_1, add_sample)
                   .Using(Close(1.019, TOL),
                          0,
                          Close(1.36 * 2.36 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_0, add_sample)
                   .Using(Close(1.009, TOL),
                          1,
                          Close(1.25 * 2.25 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock_1, add_sample)
                   .Using(Close(1.019, TOL),
                          1,
                          Close(1.25 * 2.25 / 3.14159, TOL)))
            .Exactly(1);
    VerifyNoOtherInvocations(df_mock_0);
    VerifyNoOtherInvocations(df_mock_1);
    // This avoids breaking cleanup:
    smf.channel_fits[0]->distribution_fit = original_dist_fit_0;
    smf.channel_fits[1]->distribution_fit = original_dist_fit_1;
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_CASE(improve_fit_multiple_edmans_test, *tolerance(TOL)) {
    unsigned int num_timesteps = 2;
    unsigned int num_channels = 1;
    Radiometry rad(num_timesteps, num_channels);
    rad(0, 0) = 1.009;
    rad(1, 0) = 1.109;
    int max_num_dyes = 1;
    SequencingModel seq_model;
    Mock<ChannelModel> cm_mock;
    When(Method(cm_mock, pdf)).AlwaysReturn(0.5);
    seq_model.channel_models.push_back(&cm_mock.get());
    PeptideEmission e(rad, max_num_dyes, seq_model);
    unsigned int order = 1 + num_channels;
    unsigned int* shape = new unsigned int[order];
    shape[0] = num_timesteps;
    shape[1] = max_num_dyes + 1;
    PeptideStateVector fpsv(order, shape);
    PeptideStateVector bpsv(order, shape);
    PeptideStateVector nbpsv(order, shape);
    delete[] shape;
    unsigned int* loc = new unsigned int[order];
    loc[0] = 0;
    loc[1] = 0;
    fpsv.tensor[loc] = 1.72;  // loc is {0, 0}
    bpsv.tensor[loc] = 2.72;
    nbpsv.tensor[loc] = 3.72;
    loc[1] = 1;
    fpsv.tensor[loc] = 1.36;  // loc is {0, 1}
    bpsv.tensor[loc] = 2.36;
    nbpsv.tensor[loc] = 3.36;
    loc[0] = 1;
    loc[1] = 0;
    fpsv.tensor[loc] = 1.64;  // loc is {1, 0}
    bpsv.tensor[loc] = 2.64;
    nbpsv.tensor[loc] = 3.64;
    loc[1] = 1;
    fpsv.tensor[loc] = 1.25;  // loc is {1, 1}
    bpsv.tensor[loc] = 2.25;
    nbpsv.tensor[loc] = 3.25;
    delete[] loc;
    unsigned int edmans = 1;
    double probability = 3.14159;
    SequencingModelFitter smf;
    smf.channel_fits.push_back(new ChannelModelFitter());
    LogNormalDistributionFitter* original_dist_fit =
            smf.channel_fits[0]->distribution_fit;
    Mock<LogNormalDistributionFitter> df_mock;
    Fake(Method(df_mock, add_sample));
    smf.channel_fits[0]->distribution_fit = &df_mock.get();
    e.improve_fit(fpsv, bpsv, nbpsv, edmans, probability, &smf);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.109, TOL),
                          0,
                          Close(1.72 * 2.72 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.109, TOL),
                          1,
                          Close(1.36 * 2.36 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.109, TOL),
                          0,
                          Close(1.64 * 2.64 / 3.14159, TOL)))
            .Exactly(1);
    Verify(Method(df_mock, add_sample)
                   .Using(Close(1.109, TOL),
                          1,
                          Close(1.25 * 2.25 / 3.14159, TOL)))
            .Exactly(1);
    VerifyNoOtherInvocations(df_mock);
    smf.channel_fits[0]->distribution_fit =
            original_dist_fit;  // This avoids breaking cleanup.
    // Avoid double clean-up:
    seq_model.channel_models.resize(0);
}

BOOST_AUTO_TEST_SUITE_END()  // peptide_emission_suite
BOOST_AUTO_TEST_SUITE_END()  // step_suite
BOOST_AUTO_TEST_SUITE_END()  // hmm_suite

}  // namespace whatprot
