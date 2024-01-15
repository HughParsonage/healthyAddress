#include "healthyAddress.h"

int max_nchar(SEXP x) {
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
  return m;
}

void err_if_nchar_geq(SEXP x, int max_nchar, const char * vx) {
  errIfNotStr(x, "x");
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (length(xp[i]) >= max_nchar) {
      const char * xi = CHAR(xp[i]);
      int length_xpi = length(xp[i]);
      error("`%s[%lld] = %s`, where nchar = %d, yet the maximum permissible nchar is %d.",
            vx, (long long)(i + 1), xi, length_xpi, max_nchar);
    }
  }
}

SEXP C_max_nchar(SEXP x) {
  return ScalarInteger(max_nchar(x));
}
