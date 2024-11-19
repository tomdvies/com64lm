#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

typedef struct {
    int rows;
    int cols;
    int **data;
} Matrix;

Matrix* createMatrix(int rows, int cols);
void freeMatrix(Matrix* m);
void multiplyMatrix(Matrix* result, Matrix* a, Matrix* b);
void printMatrix(Matrix* m);

#endif

