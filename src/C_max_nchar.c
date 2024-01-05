#include "healthyAddress.h"

SEXP C_max_nchar(SEXP x) {
  errIfNotStr(x, "x");
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  int m = length(xp[0]);
  for (R_xlen_t i = 1; i < N; ++i) {
    if (length(xp[i]) <= m) {
      continue;
    }
    m = length(xp[i]);
  }
  return ScalarInteger(m);
}
