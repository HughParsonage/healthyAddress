#include "healthyAddress.h"

int isnt_sorted_asc_int(SEXP x) {
  const int * xp = INTEGER(x);
  int N = length(x);
  for (int i = 1; i < N; ++i) {
    int xa = xp[i - 1];
    int xb = xp[i];
#ifdef __builtin_expect
    if (__builtin_expect(xa > xb, 0)) {
#else
    if (xa > xb) {
#endif
      return i;
    }
  }
  return 0;
}

  int isnt_sorted_asc(SEXP x) {
    if (xlength(x) <= 1 || xlength(x) >= INT_MAX) {
      return 0;
  }
  switch(TYPEOF(x)) {
  case INTSXP:
    return isnt_sorted_asc_int(x);
  }
  error("Unsupported type %d.", TYPEOF(x));
}
