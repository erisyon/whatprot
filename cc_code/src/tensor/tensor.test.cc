/******************************************************************************\
* Author: Matthew Beauregard Smith                                             *
* Affiliation: The University of Texas at Austin                               *
* Department: Oden Institute and Institute for Cellular and Molecular Biology  *
* PI: Edward Marcotte                                                          *
* Project: Protein Fluorosequencing                                            *
\******************************************************************************/

// Boost unit test framework (recommended to be the first include):
#include <boost/test/unit_test.hpp>

// File under test:
#include "tensor.h"

// Standard C++ library headers:
#include <utility>

// Local project headers:
#include "tensor/const-tensor-iterator.h"
#include "tensor/tensor-iterator.h"
#include "util/kd-range.h"

namespace whatprot {

namespace {
using boost::unit_test::tolerance;
using std::move;
const double TOL = 0.000000001;
}  // namespace

BOOST_AUTO_TEST_SUITE(tensor_suite)
BOOST_AUTO_TEST_SUITE(tensor_suite)

BOOST_AUTO_TEST_CASE(constructor_order_one_test, *tolerance(TOL)) {
    unsigned int order = 1;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 1;
    Tensor t(order, shape);
    delete[] shape;
    BOOST_TEST(t.order == order);
    BOOST_TEST(t.shape[0] == 1u);
    BOOST_TEST(t.strides[0] == 1);
    BOOST_ASSERT(t.size == 1u);
    BOOST_TEST(t.values[0] == 0.0);
}

BOOST_AUTO_TEST_CASE(constructor_order_one_bigger_test, *tolerance(TOL)) {
    unsigned int order = 1;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 10;
    Tensor t(order, shape);
    delete[] shape;
    BOOST_TEST(t.order == order);
    BOOST_TEST(t.shape[0] == 10u);
    BOOST_TEST(t.strides[0] == 1);
    BOOST_TEST(t.size == 10u);
    BOOST_TEST(t.values[0] == 0.0);
    BOOST_TEST(t.values[1] == 0.0);
    BOOST_TEST(t.values[2] == 0.0);
    BOOST_TEST(t.values[3] == 0.0);
    BOOST_TEST(t.values[4] == 0.0);
    BOOST_TEST(t.values[5] == 0.0);
    BOOST_TEST(t.values[6] == 0.0);
    BOOST_TEST(t.values[7] == 0.0);
    BOOST_TEST(t.values[8] == 0.0);
    BOOST_TEST(t.values[9] == 0.0);
}

BOOST_AUTO_TEST_CASE(constructor_order_two_test, *tolerance(TOL)) {
    unsigned int order = 2;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 3;
    shape[1] = 5;
    Tensor t(order, shape);
    delete[] shape;
    BOOST_TEST(t.order == order);
    BOOST_TEST(t.shape[0] == 3u);
    BOOST_TEST(t.shape[1] == 5u);
    BOOST_TEST(t.strides[0] == 5);
    BOOST_TEST(t.strides[1] == 1);
    BOOST_ASSERT(t.size == 3u * 5u);
    BOOST_TEST(t.values[0] == 0.0);
    BOOST_TEST(t.values[1] == 0.0);
    BOOST_TEST(t.values[2] == 0.0);
    BOOST_TEST(t.values[3] == 0.0);
    BOOST_TEST(t.values[4] == 0.0);
    BOOST_TEST(t.values[5] == 0.0);
    BOOST_TEST(t.values[6] == 0.0);
    BOOST_TEST(t.values[7] == 0.0);
    BOOST_TEST(t.values[8] == 0.0);
    BOOST_TEST(t.values[9] == 0.0);
    BOOST_TEST(t.values[10] == 0.0);
    BOOST_TEST(t.values[11] == 0.0);
    BOOST_TEST(t.values[12] == 0.0);
    BOOST_TEST(t.values[13] == 0.0);
    BOOST_TEST(t.values[14] == 0.0);
}

BOOST_AUTO_TEST_CASE(constructor_order_three_test, *tolerance(TOL)) {
    unsigned int order = 3;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 3;
    shape[2] = 4;
    Tensor t(order, shape);
    delete[] shape;
    BOOST_TEST(t.order == order);
    BOOST_TEST(t.shape[0] == 2u);
    BOOST_TEST(t.shape[1] == 3u);
    BOOST_TEST(t.shape[2] == 4u);
    BOOST_TEST(t.strides[0] == 3 * 4);
    BOOST_TEST(t.strides[1] == 4);
    BOOST_TEST(t.strides[2] == 1);
    BOOST_ASSERT(t.size == 2u * 3u * 4u);  // size is 24
    BOOST_TEST(t.values[0] == 0.0);
    BOOST_TEST(t.values[1] == 0.0);
    BOOST_TEST(t.values[2] == 0.0);
    BOOST_TEST(t.values[3] == 0.0);
    BOOST_TEST(t.values[4] == 0.0);
    BOOST_TEST(t.values[5] == 0.0);
    BOOST_TEST(t.values[6] == 0.0);
    BOOST_TEST(t.values[7] == 0.0);
    BOOST_TEST(t.values[8] == 0.0);
    BOOST_TEST(t.values[9] == 0.0);
    BOOST_TEST(t.values[10] == 0.0);
    BOOST_TEST(t.values[11] == 0.0);
    BOOST_TEST(t.values[12] == 0.0);
    BOOST_TEST(t.values[13] == 0.0);
    BOOST_TEST(t.values[14] == 0.0);
    BOOST_TEST(t.values[15] == 0.0);
    BOOST_TEST(t.values[16] == 0.0);
    BOOST_TEST(t.values[17] == 0.0);
    BOOST_TEST(t.values[18] == 0.0);
    BOOST_TEST(t.values[19] == 0.0);
    BOOST_TEST(t.values[20] == 0.0);
    BOOST_TEST(t.values[21] == 0.0);
    BOOST_TEST(t.values[22] == 0.0);
    BOOST_TEST(t.values[23] == 0.0);
}

BOOST_AUTO_TEST_CASE(move_constructor_test, *tolerance(TOL)) {
    unsigned int order = 3;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 3;
    shape[2] = 4;
    Tensor t1(order, shape);
    delete[] shape;
    Tensor t2(move(t1));
    BOOST_TEST(t1.values == (void*)NULL);
    BOOST_TEST(t1.shape == (void*)NULL);
    BOOST_TEST(t1.strides == (void*)NULL);
    BOOST_TEST(t2.order == order);
    BOOST_TEST(t2.shape[0] == 2u);
    BOOST_TEST(t2.shape[1] == 3u);
    BOOST_TEST(t2.shape[2] == 4u);
    BOOST_TEST(t2.strides[0] == 3 * 4);
    BOOST_TEST(t2.strides[1] == 4);
    BOOST_TEST(t2.strides[2] == 1);
    BOOST_ASSERT(t2.size == 2u * 3u * 4u);  // size is 24
    BOOST_TEST(t2.values[0] == 0.0);
    BOOST_TEST(t2.values[1] == 0.0);
    BOOST_TEST(t2.values[2] == 0.0);
    BOOST_TEST(t2.values[3] == 0.0);
    BOOST_TEST(t2.values[4] == 0.0);
    BOOST_TEST(t2.values[5] == 0.0);
    BOOST_TEST(t2.values[6] == 0.0);
    BOOST_TEST(t2.values[7] == 0.0);
    BOOST_TEST(t2.values[8] == 0.0);
    BOOST_TEST(t2.values[9] == 0.0);
    BOOST_TEST(t2.values[10] == 0.0);
    BOOST_TEST(t2.values[11] == 0.0);
    BOOST_TEST(t2.values[12] == 0.0);
    BOOST_TEST(t2.values[13] == 0.0);
    BOOST_TEST(t2.values[14] == 0.0);
    BOOST_TEST(t2.values[15] == 0.0);
    BOOST_TEST(t2.values[16] == 0.0);
    BOOST_TEST(t2.values[17] == 0.0);
    BOOST_TEST(t2.values[18] == 0.0);
    BOOST_TEST(t2.values[19] == 0.0);
    BOOST_TEST(t2.values[20] == 0.0);
    BOOST_TEST(t2.values[21] == 0.0);
    BOOST_TEST(t2.values[22] == 0.0);
    BOOST_TEST(t2.values[23] == 0.0);
}

BOOST_AUTO_TEST_CASE(bracket_op_test, *tolerance(TOL)) {
    unsigned int order = 2;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 3;
    Tensor t(order, shape);
    delete[] shape;
    t[{0, 0}] = 600;
    t[{0, 1}] = 601;
    t[{0, 2}] = 602;
    t[{1, 0}] = 610;
    t[{1, 1}] = 611;
    t[{1, 2}] = 612;
    BOOST_TEST((t[{0, 0}]) == 600);
    BOOST_TEST((t[{0, 1}]) == 601);
    BOOST_TEST((t[{0, 2}]) == 602);
    BOOST_TEST((t[{1, 0}]) == 610);
    BOOST_TEST((t[{1, 1}]) == 611);
    BOOST_TEST((t[{1, 2}]) == 612);
}

BOOST_AUTO_TEST_CASE(iterator_test, *tolerance(TOL)) {
    unsigned int order = 2;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 3;
    KDRange range;
    range.min.resize(order);
    range.min[0] = 0;
    range.min[1] = 0;
    range.max.resize(order);
    range.max[0] = 2;
    range.max[1] = 3;
    Tensor t(order, shape);
    t[{0, 0}] = 500;
    t[{0, 1}] = 501;
    t[{0, 2}] = 502;
    t[{1, 0}] = 510;
    t[{1, 1}] = 511;
    t[{1, 2}] = 512;
    TensorIterator* itr = t.iterator(range);
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 500);
    *itr->get() = 600;
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 501);
    *itr->get() = 601;
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 502);
    *itr->get() = 602;
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 510);
    *itr->get() = 610;
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 511);
    *itr->get() = 611;
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 512);
    *itr->get() = 612;
    itr->advance();
    BOOST_TEST(itr->done() == true);
    BOOST_TEST((t[{0, 0}]) == 600);
    BOOST_TEST((t[{0, 1}]) == 601);
    BOOST_TEST((t[{0, 2}]) == 602);
    BOOST_TEST((t[{1, 0}]) == 610);
    BOOST_TEST((t[{1, 1}]) == 611);
    BOOST_TEST((t[{1, 2}]) == 612);
    delete itr;
    delete[] shape;
}

BOOST_AUTO_TEST_CASE(const_iterator_test, *tolerance(TOL)) {
    unsigned int order = 2;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 3;
    KDRange range;
    range.min.resize(order);
    range.min[0] = 0;
    range.min[1] = 0;
    range.max.resize(order);
    range.max[0] = 2;
    range.max[1] = 3;
    Tensor t(order, shape);
    t[{0, 0}] = 500;
    t[{0, 1}] = 501;
    t[{0, 2}] = 502;
    t[{1, 0}] = 510;
    t[{1, 1}] = 511;
    t[{1, 2}] = 512;
    ConstTensorIterator* itr = t.const_iterator(range);
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 500);
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 501);
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 502);
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 510);
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 511);
    itr->advance();
    BOOST_TEST(itr->done() == false);
    BOOST_TEST(*itr->get() == 512);
    itr->advance();
    BOOST_TEST(itr->done() == true);
    BOOST_TEST((t[{0, 0}]) == 500);
    BOOST_TEST((t[{0, 1}]) == 501);
    BOOST_TEST((t[{0, 2}]) == 502);
    BOOST_TEST((t[{1, 0}]) == 510);
    BOOST_TEST((t[{1, 1}]) == 511);
    BOOST_TEST((t[{1, 2}]) == 512);
    delete itr;
    delete[] shape;
}

BOOST_AUTO_TEST_CASE(sum_trivial_test, *tolerance(TOL)) {
    unsigned int order = 1;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 1;
    Tensor tsr(order, shape);
    delete[] shape;
    tsr[{0}] = 3.14;
    BOOST_TEST(tsr.sum() == 3.14);
}

BOOST_AUTO_TEST_CASE(sum_bigger_size_test, *tolerance(TOL)) {
    unsigned int order = 1;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 3;
    Tensor tsr(order, shape);
    delete[] shape;
    tsr[{0}] = 7.0;
    tsr[{1}] = 7.1;
    tsr[{2}] = 7.2;
    BOOST_TEST(tsr.sum() == 7.0 + 7.1 + 7.2);
}

BOOST_AUTO_TEST_CASE(sum_more_dimensions_test, *tolerance(TOL)) {
    unsigned int order = 3;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 1;
    shape[1] = 1;
    shape[2] = 1;
    Tensor tsr(order, shape);
    delete[] shape;
    tsr[{0, 0, 0}] = 3.14;
    BOOST_TEST(tsr.sum() == 3.14);
}

BOOST_AUTO_TEST_CASE(sum_more_dimensions_big_test, *tolerance(TOL)) {
    unsigned int order = 2;
    unsigned int* shape = new unsigned int[order];
    shape[0] = 2;
    shape[1] = 2;
    Tensor tsr(order, shape);
    delete[] shape;
    tsr[{0, 0}] = 7.00;
    tsr[{0, 1}] = 7.01;
    tsr[{1, 0}] = 7.10;
    tsr[{1, 1}] = 7.11;
    BOOST_TEST(tsr.sum() == 7.00 + 7.01 + 7.10 + 7.11);
}

BOOST_AUTO_TEST_SUITE_END()  // tensor_suite
BOOST_AUTO_TEST_SUITE_END()  // tensor_suite

}  // namespace whatprot
