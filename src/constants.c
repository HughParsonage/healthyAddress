#include "healthyAddress.h"

SEXP C_N_POSTCODES(SEXP x) {
  return ScalarInteger(N_POSTCODES);
}

SEXP C_MAX_POSTCODE(SEXP x) {
  return ScalarInteger(MAX_POSTCODE);
}
