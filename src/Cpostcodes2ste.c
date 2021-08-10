#include "healthyAddress.h"

static const int MULTISTATE_POSTCODES[16] = {872, 2406, 2540, 2611, 2618, 2620, 3644, 3691, 3707, 4375,
                                             4377, 4380, 4383, 4385, 4825};


SEXP C_multistate_postcodes(SEXP x) {
  SEXP ans = PROTECT(allocVector(INTSXP, 15));
  for (int i = 0; i < 15; ++i) {
    SET_INTEGER_ELT(ans, i, MULTISTATE_POSTCODES[i]);
  }
  UNPROTECT(1);
  return ans;
}
