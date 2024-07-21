#include "healthyAddress.h"

static const char LETTERS[26] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static char toupper1(char x) {
  unsigned int xi = x - 'a';
  return (xi < 26) ? LETTERS[xi] : x;
}

#define SEP_COMMA_SPACE 1



SEXP Cconcat_upper2(SEXP xx1, SEXP xx2, int sep) {
  verifyEquiOrLen1Str2(xx1, "x1", xx2, "x2");
  R_xlen_t N = xlength(xx1);
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  int m2 = 0;
  switch(sep) {
  case SEP_COMMA_SPACE:
    m2 = 2;
    break;
  }
  if (xlength(xx2) == 1) {
    int n2 = length(STRING_ELT(xx2, 0));
    const char * x2 = CHAR(STRING_ELT(xx2, 0));
    for (R_xlen_t i = 0; i < N; ++i) {
      int n1 = length(STRING_ELT(xx1, i));
      const char * x1 = CHAR(STRING_ELT(xx1, i));
      char oi[n1 + n2 + m2 + 1];
      for (int j = 0; j < n1; ++j) {
        oi[j] = toupper1(x1[j]);
      }
      if (sep == SEP_COMMA_SPACE) {
        oi[n1] = ',';
        oi[n1 + 1] = ' ';
      }
      for (int j = 0; j < n2; ++j) {
        oi[j + m2 + n1] = toupper1(x2[j]);
      }
      oi[n1 + n2 + m2] = '\0';
      SET_STRING_ELT(ans, i, mkCharCE((const char *)oi, CE_UTF8));
    }
    UNPROTECT(1);
    return ans;
  }
  if (xlength(xx2) != N) {
    error("Internal error: xlength(xx2) != N"); // # nocov
  }

  for (R_xlen_t i = 0; i < N; ++i) {
    int n1 = length(STRING_ELT(xx1, i));
    const char * x1 = CHAR(STRING_ELT(xx1, i));
    int n2 = length(STRING_ELT(xx2, i));
    const char * x2 = CHAR(STRING_ELT(xx2, i));
    char oi[n1 + m2 + n2 + 1];
    for (int j = 0; j < n1; ++j) {
      oi[j] = toupper1(x1[j]);
    }
    if (sep == SEP_COMMA_SPACE) {
      oi[n1] = ',';
      oi[n1 + 1] = ' ';
    }
    for (int j = 0; j < n2; ++j) {
      oi[j + m2 + n1] = toupper1(x2[j]);
    }
    oi[n1 + m2 + n2] = '\0';
    SET_STRING_ELT(ans, i, mkCharCE((const char *)oi, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}

SEXP Cconcat_upper3(SEXP xx1, SEXP xx2, SEXP xx3, int sep) {
  if (TYPEOF(xx3) == NILSXP) {
    return Cconcat_upper2(xx1, xx2, sep);
  }

  verifyEquiOrLen1Str2(xx1, "xx1", xx2, "xx2");
  verifyEquiOrLen1Str2(xx1, "xx1", xx3, "xx3");
  int m2 = 0;
  switch(sep) {
  case SEP_COMMA_SPACE:
    m2 = 2;
    break;
  }

  R_xlen_t N = xlength(xx1);
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  if (xlength(xx2) == 1 && xlength(xx3) == 1) {

    int n2 = length(STRING_ELT(xx2, 0));
    int n3 = length(STRING_ELT(xx3, 0));
    const char * xx2p = CHAR(STRING_ELT(xx2, 0));
    const char * xx3p = CHAR(STRING_ELT(xx3, 0));


    char x2[n2 + n3 + m2 + 1];
    for (int j = 0; j < n2; ++j) {
      x2[j] = xx2p[j];
    }
    if (sep == SEP_COMMA_SPACE) {
      x2[n2] = ',';
      x2[n2 + 1] = ' ';
    }
    for (int j = 0; j < n3; ++j) {
      x2[j + m2 + n2] = xx3p[j];
    }

    int n2n3 = n2 + n3 + m2;
    for (R_xlen_t i = 0; i < N; ++i) {
      int n1 = length(STRING_ELT(xx1, i));
      const char * x1 = CHAR(STRING_ELT(xx1, i));
      char oi[n1 + m2 + n2n3 + 1];
      for (int j = 0; j < n1; ++j) {
        oi[j] = toupper1(x1[j]);
      }
      if (sep == SEP_COMMA_SPACE) {
        oi[n1] = ',';
        oi[n1 + 1] = ' ';
      }
      for (int j = 0; j < n2n3; ++j) {
        oi[j + n1 + m2] = toupper1(x2[j]);
      }
      oi[n1 + m2 + n2n3] = '\0';
      SET_STRING_ELT(ans, i, mkCharCE((const char *)oi, CE_UTF8));
    }
    UNPROTECT(1);
    return ans;
  }
  verifyEquiStr2(xx1, "xx1", xx2, "xx2");
  if (xlength(xx3) == 1) {
    int n3 = length(STRING_ELT(xx3, 0));
    char x3[n3 + 1];
    for (int j = 0; j < n3; ++j) {
      x3[j] = toupper1(CHAR(STRING_ELT(xx3, 0))[j]);
    }
    x3[n3] = '\0';
    for (R_xlen_t i = 0; i < N; ++i) {
      int n1 = length(STRING_ELT(xx1, i));
      const char * x1 = CHAR(STRING_ELT(xx1, i));
      int n2 = length(STRING_ELT(xx2, i));
      const char * x2 = CHAR(STRING_ELT(xx2, i));
      char oi[n1 + m2 + n2 + m2 + n3 + 1];
      for (int j = 0; j < n1; ++j) {
        oi[j] = toupper1(x1[j]);
      }
      if (sep == SEP_COMMA_SPACE) {
        oi[n1] = ',';
        oi[n1 + 1] = ' ';
      }
      for (int j = 0; j < n2; ++j) {
        oi[j + n1 + m2] = toupper1(x2[j]);
      }
      if (sep == SEP_COMMA_SPACE) {
        oi[n1 + m2 + n2] = ',';
        oi[n1 + m2 + n2 + 1] = ' ';
      }
      for (int j = 0; j < n3; ++j) {
        oi[j + n1 + m2 + n2 + m2] = x3[j];
      }
      oi[n1 + m2 + n2 + m2 + n3] = '\0';
      SET_STRING_ELT(ans, i, mkCharCE((const char *)oi, CE_UTF8));
    }
    UNPROTECT(1);
    return ans;
  }
  verifyEquiStr2(xx1, "xx1", xx3, "xx3");
  for (R_xlen_t i = 0; i < N; ++i) {
    int n1 = length(STRING_ELT(xx1, i));
    const char * x1 = CHAR(STRING_ELT(xx1, i));
    int n2 = length(STRING_ELT(xx2, i));
    const char * x2 = CHAR(STRING_ELT(xx2, i));
    int n3 = length(STRING_ELT(xx3, i));
    const char * x3 = CHAR(STRING_ELT(xx3, i));
    char oi[n1 + m2 + n2 + m2 + n3 + 1];
    for (int j = 0; j < n1; ++j) {
      oi[j] = toupper1(x1[j]);
    }
    if (sep == SEP_COMMA_SPACE) {
      oi[n1] = ',';
      oi[n1 + 1] = ' ';
    }
    for (int j = 0; j < n2; ++j) {
      oi[j + m2 + n1] = toupper1(x2[j]);
    }
    if (sep == SEP_COMMA_SPACE) {
      oi[n1 + m2 + n2] = ',';
      oi[n1 + m2 + n2 + 1] = ' ';
    }

    for (int j = 0; j < n3; ++j) {
      oi[n1 + m2 + n2 + m2 + j] = toupper1(x3[j]);
    }

    oi[n1 + m2 + n2 + m2 + n3] = '\0';
    SET_STRING_ELT(ans, i, mkCharCE((const char *)oi, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}

static SEXP xpaste4(const char * x1, int n1,
                    const char * x2, int n2,
                    const char * x3, int n3,
                    const char * x4, int n4,
                    bool comma_sep) {
  int n = n1 + n2 + n3 + n4;
  if (comma_sep) {
    if (n1) {
      n += 2; // in particular if zero char, do not sep
    }
    if (n2) {
      n += 2;
    }
    if (n3) {
      n += 2;
    }
  }

  char oi[n + 1];
  int k = 0;
  for (int j = 0; j < n1; ++j) {
    oi[k++] = toupper1(x1[j]);
  }
  if (comma_sep && n1) {
    oi[k++] = ',';
    oi[k++] = ' ';
  }
  for (int j = 0; j < n2; ++j) {
    oi[k++] =  toupper1(x2[j]);
  }
  if (comma_sep && n2) {
    oi[k++] = ',';
    oi[k++] = ' ';
  }
  for (int j = 0; j < n3; ++j) {
    oi[k++] =  toupper1(x3[j]);
  }
  if (comma_sep && n3) {
    oi[k++] = ',';
    oi[k++] = ' ';
  }
  for (int j = 0; j < n4; ++j) {
    oi[k++] =  toupper1(x4[j]);
  }
  oi[k] = '\0';

  return mkCharCE((const char *)oi, CE_UTF8);
}

SEXP Cconcat_upper(SEXP xx1, SEXP xx2, SEXP xx3, SEXP xx4, SEXP ssep) {
  int sep = asInteger(ssep);
  R_xlen_t N = xlength(xx1);
  if (TYPEOF(xx4) == NILSXP) {
    return Cconcat_upper3(xx1, xx2, xx3, sep);
  }
  const SEXP * x1p = STRING_PTR_RO(xx1);
  const SEXP * x2p = STRING_PTR_RO(xx2);
  const SEXP * x3p = STRING_PTR_RO(xx3);
  const SEXP * x4p = STRING_PTR_RO(xx4);
  // int m2 = 0;
  const bool comma_sep = sep == SEP_COMMA_SPACE;
  // if (comma_sep) {
  //   m2 = 2;
  // }


  if (xlength(xx2) == 1 ||
      xlength(xx3) == 1 ||
      xlength(xx4) == 1) {
    return R_NilValue;
  }
  verifyEquiStr4(xx1, "x1", xx2, "x2", xx3, "x3", xx4, "x4");
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    int n1 = length(x1p[i]);
    int n2 = length(x2p[i]);
    int n3 = length(x3p[i]);
    int n4 = length(x4p[i]);
    const char * x1 = CHAR(x1p[i]);
    const char * x2 = CHAR(x2p[i]);
    const char * x3 = CHAR(x3p[i]);
    const char * x4 = CHAR(x4p[i]);
    SET_STRING_ELT(ans, i, xpaste4(x1, n1, x2, n2, x3, n3, x4, n4, comma_sep));
  }
  UNPROTECT(1);
  return ans;
}
