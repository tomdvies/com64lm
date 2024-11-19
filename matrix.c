#include "matrix.h"
#include <stdint.h>
#include <stdlib.h>

Matrix *createMatrix(int rows, int cols) {
  Matrix *m = (Matrix *)malloc(sizeof(Matrix));
  if (!m)
    return NULL;

  m->rows = rows;
  m->cols = cols;

  // allocate rows
  m->data = (int **)malloc(rows * sizeof(int *));

  // initialise to 0
  for (int i = 0; i < rows; i++) {
    // alocate cols
    m->data[i] = (int *)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      m->data[i][j] = 0;
    }
  }
  return m;
}

void freeMatrix(Matrix *m) {
  if (!m)
    return;
  if (m->data) {
    for (int i = 0; i < m->rows; i++) {
      free(m->data[i]);
    }
    free(m->data);
  }
  free(m);
}

void multiplyMatrix(Matrix *result, Matrix *a, Matrix *b) {
  if (a->cols != b->rows)
    return; // wrong dims - maybe throw error

  // initialise result to 0 - maybe don't do this?
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->cols; j++) {
      result->data[i][j] = 0;
    }
  }

  for (int i = 0; i < a->rows; i++) {
    for (int j = 0; j < b->cols; j++) {
      result->data[i][j] = 0;
      for (int k = 0; k < a->cols; k++) {
        result->data[i][j] += a->data[i][k] * b->data[k][j];
      }
    }
  }
}


void printMatrix(Matrix *m) {
  void (*chroutr)(uint8_t) = (void (*)(uint8_t))0xFFD2;

  for (int i = 0; i < m->rows; i++) {
    chroutr('[');
    for (int j = 0; j < m->cols; j++) {
      int num = m->data[i][j];

      // print formatting for negatives - should wrap in printint or smth
      if (num < 0) {
        chroutr('-');
        num = -num;
      }

      // num 2 digits
      if (num == 0) {
        chroutr('0');
      } else {
        // number of digits
        int temp = num;
        int digits = 0;
        while (temp > 0) {
          digits++;
          temp /= 10;
        }

        // print digits from l to r
        temp = num;
        int divisor = 1;
        for (int k = 1; k < digits; k++) {
          divisor *= 10;
        }

        while (divisor > 0) {
          chroutr('0' + (temp / divisor));
          temp %= divisor;
          divisor /= 10;
        }
      }

      if (j < m->cols - 1)
        chroutr(' ');
    }
    chroutr(']');
    chroutr('\r');
    chroutr('\n');
  }
}
