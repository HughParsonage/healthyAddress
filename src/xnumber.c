#include "healthyAddress.h"

static void xnumbers(unsigned int ans[5], const char * x, int n) {
  for (int i = 0, j = -1; i < n; ++i) {
    if (isdigit(x[i])) {
      ++j;
      do {
        ans[j] *= 10;
        ans[j] += x[i] - '0';
        ++i;
      } while (isdigit(x[i]));
    }
  }
}

unsigned int uansi(unsigned int ans[5]) {
  unsigned int o = ans[0];
  for (int i = 1; i < 5; ++i) {
    o <<= 10;
    o += ans[i];
  }
  return o;
}

void do_xnumber(__uint128_t * v, const SEXP * xp, R_xlen_t N, int nThread) {
  for (R_xlen_t k = 0; k < N; ++k) {
    __uint128_t o = 0;
    const char * x = CHAR(xp[k]);
    int n = length(xp[k]);
    for (int i = 0; i < n; ++i) {
      if (isdigit(x[i])) {
        o <<= 32;
        uint32_t z = 0;
        do {
          z *= 10;
          z += x[i] - '0';
          ++i;
        } while (isdigit(x[i]));
        o += z;
      }
    }
    v[k] = o;
  }
}

SEXP Cxnumber128(SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  __uint128_t * v = malloc(sizeof(__uint128_t) * N);
  if (v == NULL) {
    return R_NilValue;
  }
  do_xnumber(v, xp, N, 1);
  SEXP ans1 = PROTECT(allocVector(INTSXP, N));
  SEXP ans2 = PROTECT(allocVector(INTSXP, N));
  SEXP ans3 = PROTECT(allocVector(INTSXP, N));
  SEXP ans4 = PROTECT(allocVector(INTSXP, N));
  int * restrict ans1p = INTEGER(ans1);
  int * restrict ans2p = INTEGER(ans2);
  int * restrict ans3p = INTEGER(ans3);
  int * restrict ans4p = INTEGER(ans4);
  for (R_xlen_t i = 0; i < N; ++i) {
    ans1p[i] = v[i] >> 96;
    ans2p[i] = (v[i] >> 64) & INT_MAX;
    ans3p[i] = (v[i] >> 32) & INT_MAX;
    ans4p[i] = v[i] & INT_MAX;
  }
  SEXP ans = PROTECT(allocVector(VECSXP, 4));
  SET_VECTOR_ELT(ans, 0, ans1);
  SET_VECTOR_ELT(ans, 1, ans2);
  SET_VECTOR_ELT(ans, 2, ans3);
  SET_VECTOR_ELT(ans, 3, ans4);
  free(v);
  UNPROTECT(5);
  return ans;
}

int n_numbers(const char * x, int n) {
  int o = 0;
  // if i = n - 1, we have !isdigit(x[i + 1])
  for (int i = 0; i < n; ++i) {
    if (isdigit(x[i]) && !isdigit(x[i + 1])) {
      ++o;
    }
  }
  return o;
}

SEXP Cxnumber(SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  SEXP ans1 = PROTECT(allocVector(INTSXP, N));
  SEXP ans2 = PROTECT(allocVector(INTSXP, N));
  SEXP ans3 = PROTECT(allocVector(INTSXP, N));
  int * restrict ans1p = INTEGER(ans1);
  int * restrict ans2p = INTEGER(ans2);
  int * restrict ans3p = INTEGER(ans3);
  unsigned int maxn = 0;
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int ansi[5] = {0};
    const char * xi = CHAR(xp[i]);
    int ni = length(xp[i]);
    xnumbers(ansi, xi, ni);
    ans1p[i] = ansi[0];
    ans2p[i] = ansi[1] + (ansi[2] << 16);
    ans3p[i] = ansi[3] + (ansi[4] << 16);
    unsigned int n_nos = n_numbers(xi, ni);
    if (n_nos > maxn) {
      maxn = n_nos;
    }
  }
  SEXP ans = PROTECT(allocVector(VECSXP, 4));
  SEXP max_numbers = ScalarInteger(maxn);
  SET_VECTOR_ELT(ans, 0, max_numbers);
  SET_VECTOR_ELT(ans, 1, ans1);
  SET_VECTOR_ELT(ans, 2, ans2);
  SET_VECTOR_ELT(ans, 3, ans3);
  UNPROTECT(4);
  return ans;
}
