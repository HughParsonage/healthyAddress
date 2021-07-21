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





