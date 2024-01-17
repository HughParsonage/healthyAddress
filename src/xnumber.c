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
        o <<= 16;
        do {
          o *= 10;
          o += x[i] - '0';
          ++i;
        } while (isdigit(x[i]));
      }
    }
    v[k] = o;
  }
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
