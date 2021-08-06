#include "healthyAddress.h"

// space unless a number or letter then uppercase
static const unsigned char UPPERS_SPACE_HYPHEN[256] =
  {' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','-',' ',' ',
   '0','1','2','3','4','5','6','7','8','9',' ',' ',' ',' ',' ',' ',
   ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
   'P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',
   ' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O',
   'P','Q','R','S','T','U','V','W','X','Y','Z',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',
   ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '};

bool is_uppercase_or_space_or_hyphen(unsigned char x) {
  return ((x - 'A') <= 26u) || x == ' ' || x == '-';
}

unsigned char toupper_hyphen_or_space(unsigned char x, unsigned char a) {
  return is_uppercase_or_space_or_hyphen(x) ? x : a;
}

bool string_equal(const char * x, int n, const char * y, int m) {
  if (n != m) {
    return false;
  }
  for (int i = 0; i < n; ++i) {
    if (x[i] != y[i]) {
      return false;
    }
  }
  return true;
}

bool string_equal_ij(const char * x, int n, const char * y, int ix, int iy) {
  for (int i = ix, j = iy; i < n; ++i) {
    if (x[i] != y[j]) {
      return false;
    }
    ++j;
  }
  return true;
}

bool uchar_is_number(unsigned char x) {
  return isdigit(x);
}

bool jchar_is_number(const char * x, int j) {
  return isdigit(x[j]);
}

unsigned int pos_preceding_word(const char * x, int i) {
  // ignore leading spaces
  while (--i >= 1) {
    if (x[i] == ' ') {
      return i + 1;
    }
  }
  return 0;
}

// array to project uncommon letters to 16
static unsigned  int StreetLetter2uint[32] =  {  0, 13, 11,  9,  1, 20, 15, 12,  6, 22, 16,  4, 10,  3,  5, 19, 25,  2,  7,  8, 14, 21, 18, 24, 17, 23};

static unsigned char uint2Streetletter[32] =  {'A','E','R','N','L','O','I','S','T','D','M','C','H',' ','B','U','G','K','Y','W','P','F','V','J','-','Z'};//,'X','Q',39,'1','.','2','3','4','0','&','5','6','8','9','7','(',')'};


unsigned int encodeWORD_16_2(const char * x, int k, int n) {
  unsigned int o = n;
  unsigned int base = 16u;
  for (int i = k; i < n; i += 2) {
    unsigned char xi = x[i];
    unsigned int li = xi - 'A';
    unsigned int li16 = StreetLetter2uint[li & 31] & 15u;
    o += base * li16;
    base *= 16u;
  }
  return o;
}

SEXP CDecodeWord_16_2(SEXP xx) {
  unsigned int x = asInteger(xx);
  SEXP ans = PROTECT(allocVector(STRSXP, 1));
  int n = x & 15u;
  char o[n + 1];
  unsigned int base = 16u;
  for (int i = 0; i < n; i += 2) {
    x /= 16;
    o[i] = uint2Streetletter[x & 15];
    if (i < n - 1) {
      o[i + 1] = '_';
    }
  }
  o[n] = '\0';
  const char * oo = (const char *)o;
  SET_STRING_ELT(ans, 0, mkCharCE(oo, CE_UTF8));
  UNPROTECT(1);
  return ans;

}

SEXP CEncodeWord_16_2(SEXP xx) {
  if (!isString(xx)) error("x");
  const char * x = CHAR(STRING_ELT(xx, 0));
  int n = length(STRING_ELT(xx, 0));
  unsigned int o = encodeWORD_16_2(x, 0, n);
  return ScalarInteger(o);
}


// Encode upper case words (i.e. upper case letters and spaces
// Return an integer
SEXP CEncodeUppercaseWords(SEXP xx, SEXP nn, SEXP nn_confirm) {
  const int max_n = asInteger(nn);
  const bool confirm_nn = asLogical(nn_confirm);
  if (TYPEOF(xx) != STRSXP) {
    error("xx in CEncodeUppercaseWords not a STRSXP.");
  }
  R_xlen_t N = xlength(xx);
  int np = 0;
  if (confirm_nn) {
    SEXP ncharxx = PROTECT(allocVector(INTSXP, N)); ++np;
    int * restrict ncharxp = INTEGER(ncharxx);
    int actual_max_n = max_n;
    for (R_xlen_t i = 0; i < N; ++i) {
      int ncharxpi = length(STRING_ELT(xx, i));
      if (ncharxpi > actual_max_n) {
        actual_max_n = ncharxpi;
      }
      ncharxp[i] = ncharxpi;
    }
    if (max_n != actual_max_n) {
      UNPROTECT(np);
      return CEncodeUppercaseWords(xx, ScalarInteger(actual_max_n), ScalarLogical(0));
    }
  }

  SEXP ans = PROTECT(allocVector(INTSXP, N)); ++np;
  int * restrict ansp = INTEGER(ans);
  const unsigned char Am2 = 'A' - 2u;

  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = 0;
    const char * x = CHAR(STRING_ELT(xx, i));
    int n = length(STRING_ELT(xx, i));
    unsigned int t7 = 1u;
    for (int j = 0; j < n; ++j) {
      unsigned char xj = x[j];
      unsigned int xju = (xj == ' ') ? 1 : (xj - Am2);
      ansp[i] += t7 * xju;
      t7 *= 27u;
    }
  }
  UNPROTECT(np);
  return ans;
}

SEXP CFindSentence(SEXP xx, SEXP W1, SEXP W2) {
  int np = 0;
  R_xlen_t N = xlength(xx);
  if (TYPEOF(xx) != STRSXP || TYPEOF(W1) != STRSXP || TYPEOF(W2) != STRSXP) {
    error("Arguments must be character.");
  }
  if (xlength(W1) != xlength(W2)) {
    error("length(W1) != length(W2)");
  }
  int WN = length(W1);

  SEXP W1_widths = PROTECT(allocVector(INTSXP, WN)); np++;
  SEXP W2_widths = PROTECT(allocVector(INTSXP, WN)); np++;
  int * restrict w1_width = INTEGER(W1_widths);
  int * restrict w2_width = INTEGER(W2_widths);
  for (int j = 0; j < WN; ++j) {
    w1_width[j] = length(STRING_ELT(W1, j));
    w2_width[j] = length(STRING_ELT(W2, j));
  }

  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);
  // only check 8 words
  int word_widths[8] = {0};
  int word_pos[9] = {0};

  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_width_i = 0;
    int d = 0;
    for (int c = 0; c < n; ++c) {
      bool is_space = x[c] == ' ';
      if (is_space) {
        d = c + 1;
      }
      // the word grows with each space,
      // unless the spaces are consecutive
      word_widths[word_width_i] += (!is_space);
      word_pos[word_width_i + 1] = d;
      word_width_i += is_space && c > 0 && x[c - 1] != ' ';
      word_width_i &= 7; // ensure only use last 8 trailing widths.
    }

    // Now go through the widths
    for (int j = 0; j < WN; ++j) {
      int w1j = w1_width[j];
      int w2j = w2_width[j];
      bool matches = false;
      for (int wwi = 1; wwi < 8; ++wwi) {
        if (matches) {
          break;
        }
        if (word_widths[wwi - 1] == w1j &&
            word_widths[wwi] == w2j) {
          const char * w1 = CHAR(STRING_ELT(W1, j));
          const char * w2 = CHAR(STRING_ELT(W2, j));
          const int c1_start = word_pos[wwi - 1];
          const int c2_start = word_pos[wwi];
          if ((w2j - 1 + c2_start) >= n) {
            // unexpected: word 2 would trails of target
            continue;
          }
          // provisionally
          matches = true;
          for (int c = 0; c < w1j; ++c) {
            if (w1[c] != x[c + c1_start]) {
              matches = false;
              break;
            }
          }
          for (int c = 0; c < w2j; ++c) {
            if (w2[c] != x[c + c2_start]) {
              matches = false;
              break;
            }
          }
        }
      }
      if (matches) {
        ansp[i] = j + 1;
        break;
      }
    }


  }
  UNPROTECT(np);
  return ans;
}






bool isUC(SEXP x) {
  R_xlen_t N = xlength(x);
  if (TYPEOF(x) != STRSXP) {
    error("Internal error(EnsureUC): TYPEOF(x) != STRSXP.");
  }
  bool all_uc = true;
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(STRING_ELT(x, i));
    const char * xi = CHAR(STRING_ELT(x, i));
    for (int j = 0; j < n; ++j) {
      unsigned char xij = xi[j];
      if (!is_uppercase_or_space_or_hyphen(xij)) {
        all_uc = false;
        break;
      }
    }
  }
  return all_uc;
}

SEXP CEnsureUC(SEXP x) {
  if (TYPEOF(x) != STRSXP) {
    error("Internal error(EnsureUC): TYPEOF(x) != STRSXP.");
  }
  if (isUC(x)) {
    return x;
  }
  R_xlen_t N = xlength(x);

  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    const char * xi = CHAR(STRING_ELT(x, i));
    int n = length(STRING_ELT(x, i));
    char oi[n + 1];
    for (int j = 0; j < n; ++j) {
      oi[j] = toupper_hyphen_or_space(xi[j], ' ');
    }
    oi[n] = '\0';
    const char * oic = (const char *)oi;
    SET_STRING_ELT(ans, i, mkCharCE(oic, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}

// x a string of street codes like 'STREET' but also 'ST'
// m mathches on a table of
// street codes in a fixed order, but only 'STREET'
// returns an integer vector
SEXP CEncodeStCd(SEXP x, SEXP m, SEXP Abbrev, SEXP Abbrevi) {
  if (TYPEOF(x) != STRSXP ||
      TYPEOF(m) != INTSXP ||
      TYPEOF(Abbrev) != STRSXP ||
      TYPEOF(Abbrevi) != INTSXP ||
      xlength(Abbrev) != xlength(Abbrevi)) {
    error("Wrong types."); // # nocov
  }
  R_xlen_t N = xlength(x);
  int an = length(Abbrev);
  const int * mp = INTEGER(m);
  const int * Abbrevip = INTEGER(Abbrevi);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    int mpi = mp[i];
    ansp[i] = mpi;
    if (mpi) {
      // already matched
      continue;
    }
    const char * xi = CHAR(STRING_ELT(x, i));
    for (int a = 0; a < an; ++a) {
      const char * aa = CHAR(STRING_ELT(Abbrev, a));
      if (!strcmp(aa, xi)) {
        ansp[i] = Abbrevip[a];
        break;
      }
    }
  }
  UNPROTECT(1);
  return ans;
}

SEXP Cmatch_word(SEXP xx, SEXP yy) {
  int np = 0;
  if (TYPEOF(xx) != STRSXP || TYPEOF(yy) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  R_xlen_t N = xlength(xx);
  R_xlen_t M = xlength(yy);
  SEXP nchar_yy = PROTECT(allocVector(INTSXP, M)); np++;
  int * restrict nchar_yyp = INTEGER(nchar_yy);
  for (R_xlen_t j = 0; j < M; ++j) {
    nchar_yyp[j] = length(STRING_ELT(yy, j));
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);

  // order to look for words
  const int W_ORD[16] = { 3,  4,  5,  2,  6, 0, 1, 7,
                          11, 12, 13, 10, 14, 8, 9, 15};

  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    int j = 0;
    unsigned int wsk = 0, wpk = 0; // index of word_sizes
    word_sizes[0] = 1;
    while (++j < n && x[j] != ' ') {
      word_sizes[0] += 1;
    }
    j = n - 1;
    wsk = 1, wpk = 1;
    while (--j >= 1) {
      bool isnt_space = x[j] != ' ';
      bool follows_space = x[j - 1] == ' ';
      bool eow = !isnt_space && !follows_space;
      bool sow = isnt_space && follows_space;
      word_sizes[wsk] += isnt_space;
      word_positions[wpk] = j;
      wsk += eow;
      wsk &= 15u;
      wpk += sow;
      wpk &= 15u;
    }
    j = 0;
    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = W_ORD[w_];

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];

      for (R_xlen_t k = 0; k < M; ++k) {
        if (matched) {
          break;
        }
        int len_k = nchar_yyp[k];
        if (len_k != len_word_i) {
          continue;
        }
        matched = true; // provisional
        const char * y = CHAR(STRING_ELT(yy, k));
        const int wpw = word_positions[w];
        for (int c = 0; c < len_k; ++c) {
          unsigned char xc = x[c + wpw];
          unsigned char yc = y[c];
          if (xc != yc) {
            matched = false;
            break;
          }
        }
        if (matched) {
          ansp[i] = k + 1;
        }
      }
    }

  }
  UNPROTECT(np);
  return ans;
}

SEXP Cmatch_StreetType(SEXP xx, SEXP yy, SEXP mm) {
  int np = 0;
  if (TYPEOF(xx) != STRSXP || TYPEOF(yy) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;
  R_xlen_t N = xlength(xx);
  R_xlen_t M = xlength(yy);
  if (M < 16) {
    error("M < 16 unexpected (should be at least 200)");
  }
  SEXP nchar_yy = PROTECT(allocVector(INTSXP, M)); np++;
  int * restrict nchar_yyp = INTEGER(nchar_yy);
  for (R_xlen_t j = 0; j < M; ++j) {
    nchar_yyp[j] = length(STRING_ELT(yy, j));
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);

  // order to look for words
  const int W_ORD[16] = { 3,  4,  5,  2,  6,  0, 1, 7,
                          11, 12, 13, 10, 14, 8, 9, 15};

  // last chars of top 13
  // const char suffix12[6] = {'D', 'E', 'K', 'L', 'T', 'Y'};

  // Difference with match_word is that we check the first 10 entries
  // First iteration
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    // almost impossible (but required because we multiply the character position
    // by 256 to encode the position of the match
    //
    if (__builtin_expect(n >= 32768, 0)) {
      continue;
    }
    const char * x = CHAR(STRING_ELT(xx, i));
    int j = n - 4; // postcode
    while (j >= 4 && x[j] == ' ') {
      --j; // maybe 800
    }
    // Contemplate at least the street name and numbers
    while (--j > 10) {
      // not end of word
      if (x[j + 1] != ' ') {
        continue;
      }
      char xj = x[j];
      if (xj == 'D' &&
          x[j - 1] == 'A' &&
          x[j - 2] == 'O' &&
          x[j - 3] == 'R' &&
          x[j - 4] == ' ') {
        ansp[i] = ST_CODE_ROAD + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);
        break;
      }
      if (xj == 'T') {
        if (x[j - 4] == 'C' &&
            x[j - 3] == 'O' &&
            x[j - 2] == 'U' &&
            x[j - 1] == 'R' &&
            x[j - 5] == ' ') {
          ansp[i] = ST_CODE_COURT + m1 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
          break;
        }
        if (x[j - 6] == ' ' &&
            x[j - 5] == 'S' &&
            x[j - 4] == 'T' &&
            x[j - 3] == 'R' &&
            x[j - 2] == 'E' &&
            x[j - 1] == 'E') {
          ansp[i] = ST_CODE_STREET + m1 * (j - 6) + m2 * pos_preceding_word(x, j - 6);
          break;
        }
        if (x[j - 8] == ' ' &&
            x[j - 7] == 'C' &&
            x[j - 6] == 'R' &&
            x[j - 5] == 'E' &&
            x[j - 4] == 'S' &&
            x[j - 3] == 'C' &&
            x[j - 2] == 'E' &&
            x[j - 1] == 'N') {
          ansp[i] = ST_CODE_CRESCENT + m1 * (j - 8) + m2 * pos_preceding_word(x, j - 8);
          break;
        }
        --j;
        continue;
      }
      if (xj == 'E') {
        if (x[j - 1] == 'N' &&
            x[j - 2] == 'A' &&
            x[j - 3] == 'L' &&
            x[j - 4] == ' ') {
          ansp[i] = ST_CODE_LANE + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);
          break;
        }
        if (x[j - 5] == ' ') {
          if (x[j - 4] == 'P' &&
              x[j - 3] == 'L' &&
              x[j - 2] == 'A' &&
              x[j - 1] == 'C') {
            ansp[i] = ST_CODE_PLACE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
          if (x[j - 4] == 'D' &&
              x[j - 3] == 'R' &&
              x[j - 2] == 'I' &&
              x[j - 1] == 'V') {
            ansp[i] = ST_CODE_DRIVE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
          if (x[j - 4] == 'C' &&
              x[j - 3] == 'L' &&
              x[j - 2] == 'O' &&
              x[j - 1] == 'S') {
            ansp[i] = ST_CODE_CLOSE + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
            break;
          }
        }
        if (x[j - 6] == ' ' &&
            x[j - 5] == 'A' &&
            x[j - 4] == 'V' &&
            x[j - 3] == 'E' &&
            x[j - 2] == 'N' &&
            x[j - 1] == 'U') {
          ansp[i] = ST_CODE_AVENUE + 256 * (j - 6) + m2 * pos_preceding_word(x, j - 6);
          break;
        }
        --j;
        continue; // must not be in top 13
      }

      if (x[j - 5] == ' ' &&
          x[j - 4] == 'T' &&
          x[j - 3] == 'R' &&
          x[j - 2] == 'A') {
        if (x[j - 1] == 'C' &&
            xj == 'K') {
          ansp[i] = ST_CODE_TRACK + 256 * (j - 5) + m2 * pos_preceding_word(x, j - 5);
          break;
        }
        if (x[j - 1] == 'I' &&
            xj == 'L') {
          ansp[i] = ST_CODE_TRAIL + 256 * (j - 5) +  m2 * pos_preceding_word(x, j - 5);
          break;
        }
        j -= 5;
        continue;
      }
    }


  }
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    int j = 0;
    unsigned int wsk = 0, wpk = 0; // index of word_sizes
    word_sizes[0] = 1;
    while (++j < n && x[j] != ' ') {
      word_sizes[0] += 1;
    }
    j = n - 1;
    wsk = 1, wpk = 1;
    while (--j >= 1) {
      bool isnt_space = x[j] != ' ';
      bool follows_space = x[j - 1] == ' ';
      bool eow = !isnt_space && !follows_space;
      bool sow = isnt_space && follows_space;
      word_sizes[wsk] += isnt_space;
      word_positions[wpk] = j;
      wsk += eow;
      wsk &= 15u;
      wpk += sow;
      wpk &= 15u;
    }
    j = 0;
    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = W_ORD[w_];

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];

      for (R_xlen_t k = 0; k < M; ++k) {
        if (matched) {
          break;
        }
        int len_k = nchar_yyp[k];
        if (len_k != len_word_i) {
          continue;
        }

        bool matched = true; // provisional
        const char * y = CHAR(STRING_ELT(yy, k));
        const int wpw = word_positions[w];
        for (int c = 0; c < len_k; ++c) {
          unsigned char xc = x[c + wpw];
          unsigned char yc = y[c];
          if (xc != yc) {
            matched = false;
            break;
          }
        }
        if (matched) {
          ansp[i] = (k + 1) + m1 * (wpw - 1) + m2 * pos_preceding_word(x, wpw - 1);
        }
      }
    }

  }
  UNPROTECT(np);
  return ans;
}

SEXP digit2560(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = x[i] & 255;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2561(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2562(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    xi /= 256u;
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2563(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xi = x[i];
    xi /= 256u;
    xi /= 256u;
    xi /= 256u;
    xi &= 255u;
    ansp[i] = xi;
  }
  UNPROTECT(1);
  return ans;
}

SEXP Cdigit256(SEXP xx, SEXP dd) {
  if (!isInteger(xx) || !isInteger(dd)) {
    error("xx,dd");
  }
  const int d = asInteger(dd);
  R_xlen_t N = xlength(xx);
  switch(d) {
  case 0:
    return digit2560(xx);
  case 1:
    return digit2561(xx);
  case 2:
    return digit2562(xx);
  case 3:
    return digit2563(xx);
  }
  return xx;
}

SEXP Cmatch_StreetName(SEXP xx,
                       SEXP Postcode, SEXP StreetMatch1,
                       SEXP Postcode2,
                       SEXP StreetCode2,
                       SEXP StreetName2) {
  R_xlen_t N = xlength(xx), M = xlength(StreetName2);
  if (!isString(xx) ||
      !isInteger(Postcode) ||
      !isInteger(StreetMatch1) ||
      !isInteger(Postcode2) ||
      !isString(StreetName2)) {
      error("Wrong types.");
  }
  if (M != xlength(StreetName2)) {
    error("M != xlength(StreetName2)");
  }
  const int * streetMatch1p = INTEGER(StreetMatch1);

  SEXP ans = PROTECT(allocVector(STRSXP, N));

  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP CX = STRING_ELT(xx, i);
    if (CX == NA_STRING) {
      SET_STRING_ELT(ans, i, CX);
      continue;
    }
    int n = length(CX);
    unsigned int si = streetMatch1p[i];
    if (si > INT_MAX) {
      SET_STRING_ELT(ans, i, NA_STRING);
      continue;
    }

    // int si0 = si & 255;
    int si1 = (si / 256) & 255;
    int si2 = si / 65536;

    const char * x = CHAR(CX);
    char oy[si1 - si2 + 1];
    for (int j = si2; j < si1; ++j) {
      oy[j - si2] = x[j];
    }
    oy[si1 - si2] = '\0';
    const char * o = (const char *)oy;
    SET_STRING_ELT(ans, i, mkCharCE(o, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}

SEXP CextractNumber(SEXP xx, SEXP ss, SEXP mm) {
  if (!isString(xx)) {
    error("Address was type '%s' but must be a character vector.", type2char(TYPEOF(xx)));
  }
  if (!isInteger(ss)) {
    error("Address was type '%s' but must be an integer vector.", type2char(TYPEOF(ss)));
  }
  const int m = asInteger(mm);
  R_xlen_t N = xlength(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  const SEXP * xp = STRING_PTR(xx);
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP CX = xp[i];
    int n = length(CX);
    const char * x = CHAR(CX);
    bool maybe_unit = false;
    int n_numbers = 0;
    unsigned char number_fmt = '1';
    // '1' one number |
    // '-' number-first_number-last
    // '/' unit/number_first
    int pos_last_number = 0;
    // n - 5 due postcode
    for (int j = 0; j < n - 5; ++j) {
      unsigned char xj = x[j];
      unsigned char xjj = x[j + 1];
      if (uchar_is_number(xj)) {

        n_numbers += !uchar_is_number(xjj);
        pos_last_number = j;
      }
    }
    for (int j = 0; j < pos_last_number; ++j) {
      unsigned char xj = x[j];
      unsigned char xk = x[j + 1];
      maybe_unit = xj == '/' || xj == 'U' || xj == 'G';
    }
    if (n_numbers == 0) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    int j = pos_last_number;
    unsigned int number_last = x[j] - '0';
    int ten = 10;
    while (--j >= 0 && jchar_is_number(x, j) && ten <= 1e5) {
      number_last += ten * (x[j] - '0');
      ten *= 10;
    }
    unsigned int number_first = 0;
    if (n_numbers == 2) {
      ten = 10;
      while (--j >= 0 && jchar_is_number(x, j) && ten <= 1e5) {
        number_first += ten * (x[j] - '0');
        ten *= 10;
      }
    }

    unsigned int oi = number_last;
    oi += (unsigned int)(65536u * number_first);
    ansp[i] = oi;

  }

  UNPROTECT(1);
  return ans;
}





