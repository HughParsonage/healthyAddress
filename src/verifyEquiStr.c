#include "healthyAddress.h"

void errIfNotStr(SEXP x, const char * xx) {
  if (!isString(x)) {
    error("`%s` was type '%s' but must be a character vector.", xx, type2char(TYPEOF(x)));
  }
}

void errIfNotLen(SEXP x, const char * xx, R_xlen_t N) {
  if (xlength(x) != N) {
    error("`%s` was length '%lld' but must be length %lld.", xx, (long long)xlength(x), (long long)N);
  }
}

void errIfNotLen1orN(SEXP x, const char * xx, R_xlen_t N) {
  if (xlength(x) != N && xlength(x) != 1) {
    error("`%s` was length '%lld' but must be length %lld or length-one.", xx, (long long)xlength(x), (long long)N);
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

void errifnotLogical(SEXP x, const char * v) {
  if (!isLogical(x)) {
    error("`%s` was type '%s' but must be type logical", v, type2char(TYPEOF(x)));
  }
}

void errifNotTF(SEXP x, const char * v) {
  errifnotLogical(x, v);
  errIfNotLen(x, v, 1);
  const int o = asLogical(x);
  if (o == NA_LOGICAL) {
    error("`%s` was NA, must be TRUE or FALSE", v);
  }
}

void verifyEquiDouble(SEXP x, const char * xx, SEXP y, const char * yy) {
  if (xlength(x) != xlength(y)) {
    error("xlength(%s) = %lld, yet xlength(%s) = %lld. Lengths must be equal.",
          xx, xlength(x), yy, xlength(y));
  }
  if (!isReal(x)) {
    error("`%s` was type '%s' but must be double", xx, type2char(TYPEOF(x)));
  }
  if (!isReal(y)) {
    error("`%s` was type '%s' but must be double", yy, type2char(TYPEOF(y)));
  }
}
