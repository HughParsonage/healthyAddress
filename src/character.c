#include "healthyAddress.h"

int next_numeral(int j, const char * x, int n) {
  while (!isdigit(x[j])) {
    ++j;
  }
  return j;
}

bool digit_or_space_digit(int j, const char * x) {
  return isdigit(x[j]) || (isspace(x[j]) && isdigit(x[j + 1]));
}

// positiion of digit after level
int LEVEL_j(const char * x, int n) {
  const char * LEVEL = "LEVEL";
  if (x[0] == 'L') {
    if (isdigit(x[1])) {
      return 1;
    }
    if (isspace(x[1]) && isdigit(x[2])) {
      return 2;
    }
    bool has_LEVEL = true;
    for (int j = 1; j < 5; ++j) {
      if (x[j] != LEVEL[j]) {
        has_LEVEL = false;
        break;
      }
    }
    if (has_LEVEL) {
      if (isdigit(x[5])) {
        return 5;
      }
      if (isspace(x[5]) && isdigit(x[6])) {
        return 6;
      }
    }
  }
  for (int j = 1; j < n - 4; ++j) {
    if (x[j - 1] != ' ' || x[j] != 'L') {
      continue;
    }
    if (isdigit(x[j + 1])) {
      return j + 1;
    }
    if (isspace(x[j + 1]) && isdigit(x[j + 2])) {
      return j + 2;
    }
    bool has_LEVEL = true;
    for (int jj = 1; jj < 5; ++jj) {
      if (x[jj] != LEVEL[jj]) {
        has_LEVEL = false;
        break;
      }
    }
    if (has_LEVEL) {
      if (isdigit(x[j + 5])) {
        return j + 5;
      }
      if (isspace(x[j + 5]) && isdigit(x[j + 6])) {
        return j + 6;
      }
    }
  }
  return 0;
}

int j_post_LEVEL(const char * x, int n) {
  int j = LEVEL_j(x, n);
  if (j) {
    while (isdigit(x[j])) {
      ++j;
    }
    return j;
  }
  return 0;
}


