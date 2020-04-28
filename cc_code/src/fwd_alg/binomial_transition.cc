// Author: Matthew Beauregard Smith
#include "binomial_transition.h"

#include "tensor/tensor.h"
#include "tensor/vector.h"

namespace fluoroseq {

BinomialTransition::BinomialTransition(int max_n, double q) {
    double p = 1 - q;
    length = max_n + 1;
    size = length * (length + 1) / 2;
    values = new double[size];
    values[0] = 1.0;
    for (int i = 1; i < length; i++) {
        prob(i, 0) = prob(i - 1, 0) * q;
        for (int j = 1; j < i; j++) {
            prob(i, j) = prob(i - 1, j) * q + prob(i - 1, j - 1) * p;
        }
        prob(i, i) = prob(i - 1, i - 1) * p;
    }
}

BinomialTransition::~BinomialTransition() {
    delete[] values;
}

double& BinomialTransition::prob(int from, int to) {
    return values[from * (from + 1) / 2 + to];
}

double BinomialTransition::prob(int from, int to) const {
    return values[from * (from + 1) / 2 + to];
}

void BinomialTransition::operator()(Tensor* tensor,
                                    int channel,
                                    int edmans) const {
    int vector_stride = tensor->strides[1 + channel];
    int vector_length = tensor->shape[1 + channel];
    int outer_stride = vector_stride * vector_length;
    int outer_max = tensor->strides[0] * (edmans + 1);
    for (int outer = 0; outer < outer_max; outer += outer_stride) {
        for (int inner = 0; inner < vector_stride; inner++) {
            Vector v(vector_length,
                     vector_stride,
                     &tensor->values[outer + inner]);
            (*this)(&v);
        }
    }
}

void BinomialTransition::operator()(Vector* v) const {
    for (int to = 0; to < v->length; to++) {
        double v_to = 0.0;
        for (int from = to; from < v->length; from++) {
            v_to += prob(from, to) * (*v)[from];
        }
        (*v)[to] = v_to;
    }
}

}  // namespace fluoroseq
