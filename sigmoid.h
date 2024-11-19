#ifndef SIGMOID_H
#define SIGMOID_H

#include <stdint.h>
#include "matrix.h"

// Fixed-point ReLU implementation
// Input and output in Q8.8 format
int16_t relu(int16_t x);

// Apply ReLU activation to entire matrix
void matrix_relu(Matrix* m);

// Perform 2-layer neural network inference
// input: input vector (matrix with one column)
// w1: weights for first layer
// w2: weights for second layer
// Returns: output vector (matrix with one column)
Matrix* predict_2layer(Matrix* input, Matrix* w1, Matrix* w2);

#endif
