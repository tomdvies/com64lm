#include "matrix.h"
#include "sigmoid.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// compile with com-llvm 
// mos-c64-clang -Os -o ./build/main.prg main.c matrix.c sigmoid.c
// run with vice:
// x64 --autostart ./build/main.prg

// C64 screen memory starts at 0x0400
#define SCREEN_MEMORY 0x0400

void (*chroutr)(uint8_t) = (void (*)(uint8_t))0xFFD2;

// Function to print a string to the screen 
void print_string(const char *str) {
  uint16_t position = 10;
  while (*str) {
    chroutr(*str++);
  }
  const char *newline = "\n\r";
  while (*newline)
    chroutr(*newline++);
}

int main() {

  // 2x1
  Matrix *input = createMatrix(2, 1);
  input->data[0][0] = 20; 
  input->data[1][0] = 10; 

  // 3x2
  Matrix *w1 = createMatrix(3, 2);
  w1->data[0][0] = 1; 
  w1->data[0][1] = 2; 
  w1->data[1][0] = 3; 
  w1->data[1][1] = 4; 
  w1->data[2][0] = 5; 
  w1->data[2][1] = 6; 

  // 1x3
  Matrix *w2 = createMatrix(1, 3);
  w2->data[0][0] = 1; 
  w2->data[0][1] = 3; 
  w2->data[0][2] = 0; 

  print_string("Input:\n");
  printMatrix(input);

  Matrix *output = predict_2layer(input, w1, w2);

  print_string("Output:\n");
  printMatrix(output);

  freeMatrix(input);
  freeMatrix(w1);
  freeMatrix(w2);
  freeMatrix(output);
}
