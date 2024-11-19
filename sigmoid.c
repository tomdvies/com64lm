#include "matrix.h"
#include <stdint.h>

int16_t relu(int16_t x) {
  // If negative, return 0
  if (x < 0)
    return 0;

  // Otherwise return x in Q8.8 format
  return x;
}

// ReLU activation to entire matrix
void matrix_relu(Matrix *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->cols; j++) {
      m->data[i][j] = relu(m->data[i][j]);
    }
  }
}

// w1: weights for first layer
// w2: weights for second layer
Matrix *predict_2layer(Matrix *input, Matrix *w1, Matrix *w2) {
  // First layer
  Matrix *layer1 = createMatrix(w1->rows, input->cols);
  multiplyMatrix(layer1, w1, input);
  matrix_relu(layer1);

  // Second layer
  Matrix *output = createMatrix(w2->rows, layer1->cols);
  multiplyMatrix(output, w2, layer1);
  matrix_relu(output);

  // Clean up intermediate results
  freeMatrix(layer1);

  return output;
}
