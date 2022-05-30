#include "healthyAddress.h"

void errIfNotStr(SEXP x, const char * xx) {
  if (!isString(x)) {
    error("`%s` was type '%s' but must be a character vector.", xx, type2char(TYPEOF(x)));
  }
}

void errIfNotLen(SEXP x, const char * xx, R_xlen_t N) {
  if (xlength(x) != N) {
    error("`%s` was length '%lld' but must be length %lld.", xx, xlength(x), N);
  }
}

void errIfNotLen1orN(SEXP x, const char * xx, R_xlen_t N) {
  if (xlength(x) != N && xlength(x) != 1) {
    error("`%s` was length '%lld' but must be length %lld or length-one.", xx, xlength(x), N);
  }
}

void verifyEquiStr2(SEXP x, const char * xx,
                    SEXP y, const char * yy) {
  errIfNotStr(x, xx);
  errIfNotStr(y, yy);
  R_xlen_t N = xlength(x);
  errIfNotLen(y, yy, N);
}

void verifyEquiOrLen1Str2(SEXP x, const char * xx,
                          SEXP y, const char * yy) {
  errIfNotStr(x, xx);
  errIfNotStr(y, yy);
  R_xlen_t N = xlength(x);
  errIfNotLen1orN(y, yy, N);
}

void verifyEquiStr4(SEXP x, const char * xx,
                    SEXP y, const char * yy,
                    SEXP z, const char * zz,
                    SEXP w, const char * ww) {
  errIfNotStr(x, xx);
  errIfNotStr(y, yy);
  errIfNotStr(z, zz);
  errIfNotStr(w, ww);
  R_xlen_t N = xlength(x);
  errIfNotLen(y, yy, N);
  errIfNotLen(z, zz, N);
  errIfNotLen(w, ww, N);
}
