#include "healthyAddress.h"

static const unsigned char letters[26] =
  {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
   'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

static const unsigned char LETTERS[26] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};


SEXP CToUpperBasic(SEXP x) {
  R_xlen_t N = xlength(x);
  if (TYPEOF(x) != STRSXP) {
    error("TYPEOF(x) != STRSXP");
  }
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP xi = STRING_ELT(x, i);
    if (xi == NA_STRING) {
      SET_STRING_ELT(x, i, xi);
      continue;
    }
    int nchari = length(xi);
    const char * xpi = CHAR(xi);
    char anspi[nchari + 1];
    for (int j = 0; j < nchari; ++j) {
      unsigned char xpij = xpi[j];
      unsigned int xpiju = (unsigned int)(xpij - 'a');
      anspi[j] = (xpiju < 26) ? LETTERS[xpiju] : xpij;
    }
    anspi[nchari] = '\0';
    SET_STRING_ELT(ans, i, mkCharCE(anspi, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}

SEXP CExtractStdAddress(SEXP address, SEXP street_names) {
  /*
  R_xlen_t N = xlength(address);
  R_xlen_t nNames = xlength(street_names);
  if (TYPEOF(address) != STRSXP) {
    error("TYPEOF(address) != STRSXP");
  }
  if (TYPEOF(street_names) != STRSXP) {
    error("TYPEOF(street_names) != STRSXP");
  }
*/



  return R_NilValue;
}

