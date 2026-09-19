#include "utils.h"

int floorDiv(int a, int b){
  int q = a / b;
  int r = a % b;
  if (r != 0 && a < 0) {
    q--;
  }
  return q;
}

int floorMod(int a, int b){
  int r = a % b;
  if (r < 0) {
    r += b;
  }
  return r;
}