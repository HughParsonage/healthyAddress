#include "healthyAddress.h"

int next_numeral(int j, const char * x, int n) {
  while (!isdigit(x[j])) {
    ++j;
  }
  return j;
}


