#include "healthyAddress.h"

static bool last4rdigs(const char * x, int n) {
  return n >= 4 && isdigit(x[n - 4]) && isdigit(x[n - 3]) && isdigit(x[n - 2]) && isdigit(x[n - 1]);
}

bool followed_by_STE_POSTCODE(int w_i, WordData * wd) {
  int n_words = wd->n_words;
  // THE BASIN VIC 3154
  //     ^     ^   ^  ^
  //     w_i          n_words
  if (n_words != w_i + 3) {
    return false;
  }
  const char * x = wd->x;
  int n = wd->n;
  if (!last4rdigs(x, n)) {
    return false;
  }

  int j = wd->lhs[w_i + 1];
  switch(x[j]) {
  case 'A':
    return x[j + 1] == 'C' && x[j + 2] == 'T' && !isUPPER(x[j + 3]);
  case 'N':
    return (x[j + 1] == 'T' && !isUPPER(x[j + 2])) || (x[j + 1] == 'S' && x[j + 2] == 'W');
  case 'Q':
    return x[j + 1] == 'L' && x[j + 2] == 'D' && !isUPPER(x[j + 3]);
  case 'S':
    return x[j + 1] == 'A' && !isUPPER(x[j + 2]);
  case 'T':
    return x[j + 1] == 'A' && x[j + 2] == 'S' && !isUPPER(x[j + 3]);
  case 'W':
    return x[j + 1] == 'A' && !isUPPER(x[j + 2]);
  case 'V':
    return x[j + 1] == 'I' && x[j + 2] == 'C' && !isUPPER(x[j + 3]);
  }
  return false;
}

SEXP Cfollowed_by_STE_POSTCODE(SEXP Wi, SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  const int * wip = INTEGER(Wi);
  errIfNotLen(Wi, "wi", N);
  SEXP ans = PROTECT(allocVector(LGLSXP, N));
  int * restrict ansp = LOGICAL(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    WordData wd = word_data(CHAR(xp[i]), length(xp[i]));
    ansp[i] = followed_by_STE_POSTCODE(wip[i], &wd);
  }
  UNPROTECT(1);
  return ans;
}
