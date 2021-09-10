
#include "healthyAddress.h"
#include "streetcodes.h"

/*
 static const unsigned char letters[26] =
 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 */




static const char LETTERS[26] =
  {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
   'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static char toupper1(char x) {
  unsigned int xi = x - 'a';
  return (xi < 26) ? LETTERS[xi] : x;
}

unsigned int djb2_hash(const char * str, int n, int i) {
  unsigned int hash = 5381;
  //
  // while (c = *str++)
  //   hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

  // using xor instead of + performs slightly better on STREET_NAME
  while (++i < n) {
    unsigned char xi = str[i];
    hash = ((hash << 5) + hash) ^ xi;
  }
  return hash;
}

SEXP C_HashStreetName(SEXP x) {
  if (!isString(x)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(x)));
  }
  R_xlen_t N = xlength(x);
  const SEXP * xp = STRING_PTR(x);
  // http://www.cse.yorku.ca/~oz/hash.html
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] == NA_STRING) {
      ansp[i] = NA_INTEGER;
      continue;
    }

    int n = length(xp[i]);
    const char * xi = CHAR(xp[i]);
    ansp[i] = djb2_hash(xi, n, -1);
  }
  UNPROTECT(1);
  return ans;
}

bool char_is_number(char x) {
  unsigned int xi = x - '0';
  return xi <= 9U;
}

bool char_is_LETTER(char x) {
  // assumes AZ contiguous and in order
  unsigned int xi = x - 'A';
  return xi <= 25u;
}

bool jchar_is_LETTER(const char * x, int j) {
  unsigned char xj = x[j];
  return char_is_LETTER(xj);
}

bool jchar_is_LETTER_or_hyphen(const char * x, int j) {
  unsigned char xj = x[j];
  return char_is_LETTER(xj) || xj == '-';
}

// For detecting things like 'THE ESPLANADE'
// Is the first 'word' the substring 'THE'
bool string_first_word_THE(const char * x, int n, int j) {
  while (++j < n - 5) {
    if (x[j] != ' ') {
      continue;
    }
    if (x[j + 1] == 'T' &&
        x[j + 2] == 'H' &&
        x[j + 3] == 'E' &&
        x[j + 4] == ' ') {
      return true;
    }
    // is a word
    if (jchar_is_LETTER(x, j) && !jchar_is_number(x, j - 1) &&
        jchar_is_LETTER(x, j + 1) && jchar_is_LETTER(x, j + 2)) {
      break;
    }
  }
  return false;
}


int ndigits_positive(int x) {
  if (x == 0) return 0;
  if (x < 10) return 1;
  if (x < 100) return 2;
  if (x < 1000) return 3;
  if (x < 10000) return 4;
  if (x < 100000) return 5;
  if (x < 1000000) return 6;
  if (x < 10000000) return 7;
  if (x < 100000000) return 8;
  if (x < 1000000000) return 9;
  return 10;
}

int which_char_is_space(const char * x, int n) {
  for (int i = 0; i < n; ++i) {
    if (x[i] == ' ') {
      return i + 1;
    }
  }
  return 0;
}


int next_nonnumber(const char * x, int from) {
  while (char_is_number(x[from])) {
    ++from;
  }
  return from;
}

int digit_of_from(const char * x, int * j, unsigned char barrier, int len) {
  // x a string of length len from which the digit is sought from
  // position j, terminating whenever barrier occurs
  int o = 0;
  int k = j[0];
  while (k < len && x[k] != barrier) {
    unsigned int xk = x[k] - '0';
    if (xk > 9U) {
      break;
    }
    o *= 10;
    o += xk;
    ++k;
  }
  j[0] = k;
  return o;
}

// VIC->2
int ste_as_int(const char * x, int ii) {
  int i = ii;
  // we don't know
  while (!char_is_LETTER(x[i])) {
    ++i;
  }
  unsigned char xi = x[i];
  switch(xi) {
  case 'N':
    switch(x[i + 1]) {
    case 'T':
      return 7;
    case 'S':
      return (x[i + 2] == 'W') ? 1 : 0;
    }
    break;
  case 'V':
    return (x[i + 1] == 'I' && x[i + 2] == 'C') ? 2 : 0;
    break;
  case 'Q':
    return (x[i + 1] == 'L' && x[i + 2] == 'D') ? 3 : 0;
    break;
  case 'S':
    return (x[i + 1] == 'A') ? 4 : 0;
    break;
  case 'W':
    return (x[i + 1] == 'A') ? 5 : 0;
    break;
  case 'T':
    return (x[i + 1] == 'A' && x[i + 2] == 'S') ? 6 : 0;
    break;
  case 'A':
    return (x[i + 1] == 'C' && x[i + 2] == 'T') ? 8 : 0;
    break;
  case 'O':
    return (x[i + 1] == 'T') ? 9 : 0;
  }
  return 0;
}

bool has_postcode(const char * x, int n) {
  if (n < 4) {
    return 0;
  }
  int k = n - 4;
  return
    char_is_number(x[k]) &&
      char_is_number(x[k + 1]) &&
      char_is_number(x[k + 2]) &&
      char_is_number(x[k + 3]);
}

bool has_postcode_from(const char * x, int k) {
  return
  char_is_number(x[k]) &&
    char_is_number(x[k + 1]) &&
    char_is_number(x[k + 2]) &&
    char_is_number(x[k + 3]);
}


int xpostcode_unsafe(const char * x, int n) {
  // unsafe = don't check that length is sufficient
  int o = 0;
  const int ten4s[4] = {1000, 100, 10, 1};
  const int n4 = n - 4;
  for (int d = 0; d < 4; ++d) {
    char xj = x[n4 + d];
    if (isdigit(xj)) {
      o += ten4s[d] * (xj - '0');
    }
  }
  return o;
}



int n_spaces(const char * x, int n) {
  int o = 0;
  for (int i = 0; i < n; ++i) {
    o += x[i] == ' ';
  }
  return o;
}

bool has_ste_postcode(const char * x, int n) {
  // <STE> <nnnn>
  // location of space before
  if (n < 4 + 1 + 3) {
    return false;
  }
  // n - 8
  if (x[n - 8] == ' ') {
    // two char
    return ste_as_int(x, n - 7) && has_postcode(x, n);
  }
  return ste_as_int(x, n - 8) && has_postcode(x, n);
}

// Convert number_suffix to raw for compression
unsigned char number_suffix2raw(char x0, char x1) {
  if (x0 == ' ') {
    return 0; // i.e. no suffix
  }
  if (x1 == '\0' || x1 == ' ' || isdigit(x0)) {
    return x0;
  }
  switch(x0) {
  case 'A':
    switch(x1) {
    case 'A':
      return 'a';
    case 'B':
      return 'b';
    default:
      return 254;
    }
  case 'B':
    switch(x1) {
    case 'B':
      return 'c';
    case 'C':
      return 'd';
    default:
      return 253;
    }
  case 'C':
    return 'e';
  case 'G':
    switch(x1) {
    case 'R':
      return 'g';
    case 'X':
      return 'h';
    case 'Z':
      return 'i';
    default:
      return 252;
    }
  case 'M':
    return 'm';
  case 'N':
    return 'n';
  case 'T':
    switch(x1) {
    case 'T':
      return 't';
    case '3':
      return 'u';
    default:
      return 251;
    }
    break;
  }
  return 0;
}




SEXP CPoaHasSt(SEXP Poa, SEXP Type) {
  R_xlen_t N = xlength(Poa);
  if (TYPEOF(Poa) != INTSXP || xlength(Type) != N) {
    return R_NilValue;
  }
  if (TYPEOF(Type) != INTSXP) {
    if (TYPEOF(Type) != STRSXP) {
      return R_NilValue;
    }
    return R_NilValue;
  }


  if (N != xlength(Type)) {
    return R_NilValue;
  }
  const int * poap = INTEGER(Poa);
  const int * typep = INTEGER(Type);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = poa_has_street_type(poap[i], typep[i]);
  }
  UNPROTECT(1);
  return ans;
}

SEXP C_uniquePostcodes(SEXP xx) {
  if (!isInteger(xx)) {
    error("`x` was type '%s' but must be integer.", type2char(TYPEOF(xx)));
  }
  R_xlen_t N = xlength(xx);
  const int * xp = INTEGER(xx);

  unsigned char postcode_tbl[SUP_POSTCODES] = {0};
  for (R_xlen_t i = 0; i < N; ++i) {
    unsigned int xpi = xp[i]; // NA becomes big, one branch only
    if (xpi >= SUP_POSTCODES) {
      continue;
    }
    postcode_tbl[xpi] = 1;
  }
  int n_out = 0; // number of unique postcodes
  // i = 1, we don't want to include zero
  for (int i = 1; i < SUP_POSTCODES; ++i) {
    n_out += postcode_tbl[i];
  }
  SEXP ans = PROTECT(allocVector(INTSXP, n_out));
  int * restrict ansp = INTEGER(ans);
  for (int i = 1, j = 0; i < SUP_POSTCODES; ++i) {
    if (postcode_tbl[i]) {
      ansp[j] = i;
      ++j;
    }
  }
  UNPROTECT(1);
  return ans;
}




SEXP CToUpperBasic(SEXP x) {
  R_xlen_t N = xlength(x);
  if (TYPEOF(x) != STRSXP) {
    error("TYPEOF(x) != STRSXP");
  }
  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP xi = STRING_ELT(x, i);
    if (xi == NA_STRING) {
      SET_STRING_ELT(ans, i, xi);
      continue;
    }
    int nchari = length(xi);
    const char * xpi = CHAR(xi);
    char anspi[nchari + 1];
    for (int j = 0; j < nchari; ++j) {
      unsigned char xpij = xpi[j];
      anspi[j] = toupper1(xpij);
    }
    anspi[nchari] = '\0';
    SET_STRING_ELT(ans, i, mkCharCE(anspi, CE_UTF8));
  }
  UNPROTECT(1);
  return ans;
}







SEXP CExtractPostcode(SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xpp = STRING_PTR(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xpp[i]);
    if (n < 4) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xp = CHAR(xpp[i]);
    ansp[i] = xpostcode_unsafe(xp, n);
  }
  UNPROTECT(1);
  return ans;
}

SEXP MAX_uN_STCDs(SEXP x) {
  return ScalarInteger(MAX_NUMBER_STREET_TYPES_ANY_POSTCODE);
}
SEXP C_N_STREET_TYPES(SEXP x) {
  return ScalarInteger(N_STREET_TYPES);
}

void do_flat_number(const char * x, int n, int ans[2], int jj) {
  ans[0] = 0; // position after last digit of flat number
  ans[0] = 0; // the flat number itself
  if (n < 4) {
    return;
  }
  // position j so that it points to the first digit of the flat number
  int j = jj;
  switch(x[0]) {
  case 'U':
    j = (x[1] == 'N' && x[2] == 'I' && x[3] == 'T') ? 4 : 1;
    break;
  case 'G':
    j = 1;
    break;
  default: {
      // have to seek ahead
      int has_slash = 0;
      if (n < 6) {
        return; // don't bother
      }
      for (int i = 0; i < 6; ++i) {
        if (x[i] == '/') {
          has_slash = i;
          break;
        }
      }
      if (has_slash) {
        j = has_slash;
        int o = 0;
        int ten = 1;
        for (int j = has_slash; j >= 0; --j) {
          if (isdigit(x[j])) {
            o += ten * (x[j] - '0');
            ten *= 10; // no need to check overflow because only looking at first 5 chars
          }
        }
        ans[0] = has_slash;
        ans[1] = o;
      }
      return;
    }
  }
  while (j < n && x[j] == ' ') {
    ++j;
  }
  int o = 0;
  while (j < n && isdigit(x[j])) {
    int digit = x[j] - '0';
    o *= 10;
    o += digit;
    ++j;
  }
  ans[0] = j;
  ans[1] = o;
}


SEXP C_NumberFirstLast(SEXP xx) {
  if (!isString(xx)) {
    error("`address` was type '%s' but must be a character vector.", type2char(TYPEOF(xx)));
  }
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  int np = 0;
  SEXP n_unit = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP nfirst = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP nfinal = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP posfin = PROTECT(allocVector(INTSXP, N)); ++np;
  SEXP suffix = PROTECT(allocVector(RAWSXP, N)); ++np;

  int * restrict nun = INTEGER(n_unit);
  int * restrict nfp = INTEGER(nfirst);
  int * restrict nfl = INTEGER(nfinal);
  int * restrict pfp = INTEGER(posfin);
  unsigned char * restrict sfp = RAW(suffix);

  for (R_xlen_t i = 0; i < N; ++i) {
    nun[i] = NA_INTEGER;
    nfp[i] = NA_INTEGER;
    nfl[i] = NA_INTEGER;
    pfp[i] = 0;
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    if (n <= 4) {
      continue; // confusion with postcode, can't be anything meaningful (even 1 A ST)
    }
    const char * x = CHAR(xp[i]);
    int j_start = 0;
    const char x0 = x[0];
    if (!isdigit(x[0])) {
      const char x1 = x[1];
      const char x2 = x[2];
      if (x0 == 'C' && x1 == '/' && (x2 == '-' || x2 == 'O')) {
        // careof
        j_start = 3;
      }
    }
    int flat_number2i[2] = {0};
    do_flat_number(x, n, flat_number2i, j_start);
    nun[i] = flat_number2i[1];

    int o1 = 0;
    int o2 = 0;

    // two numbers are separated by a dash
    bool two_numbers = false;
    // move after flat number:
    j_start = flat_number2i[1] > 0 ? (flat_number2i[0] + 1) : j_start;
    int j = j_start;
    for (; j < n - 4; ++j) {
      if (jchar_is_number(x, j)) {
        int digit = x[j] - '0';
        if (two_numbers) {
          o2 *= 10;
          o2 += digit;
        } else {
          o1 *= 10;
          o1 += digit;
        }
        continue;
      }
      if (x[j] == '-') {
        two_numbers = true;
        continue;
      }
      break; // don't continue on first encounter with non-number/dash
    }

    unsigned char this_suffix = number_suffix2raw(x[j], x[j + 1]);
    j += (this_suffix == 0 ? 0 : (islower(this_suffix) ? 2 : 1));
    sfp[i] = this_suffix;

    nfp[i] = o1;
    nfl[i] = o2;
    pfp[i] = j;

  }
  SEXP ans = PROTECT(allocVector(VECSXP, np)); ++np;
  SET_VECTOR_ELT(ans, 0, n_unit);
  SET_VECTOR_ELT(ans, 1, nfirst);
  SET_VECTOR_ELT(ans, 2, nfinal);
  SET_VECTOR_ELT(ans, 3, posfin);
  SET_VECTOR_ELT(ans, 4, suffix);

  UNPROTECT(np);
  return ans;

}








// Is y a substring within x, starting at position i?
// x The string within which y is suspected to exist
// i the character position of x from which y is expected
// n The (entire) length of x
// y The search term/the substring
// m The length of this substring
bool substring_within(const char * x, int i, int n, const char * y, int m) {
  // if the remaining length of x is insufficient to contain y, then no
  if (n - i < m) {
    return false;
  }
  for (int j = 0; j < m; ++j) {
    if (x[i + j] != y[j]) {
      return false;
    }
  }
  return true;
}



bool jchar_is_number(const char * x, int j) {
  return isdigit(x[j]);
}

unsigned int pos_preceding_word(const char * x, int i) {
  for (int j = i - 3; j > 0; --j) {
    // want the position of the preceding word (following a number)
    // because we're really after the street name
    if (x[j] == ' ' && isdigit(x[j - 1]) && jchar_is_LETTER(x, j + 1)) {
      return j + 1;
    }
  }
  return 0;
}


int has_comma(const char * x, int n) {
  int i = n - 1;
  while (i >= 0 && x[i] != ',') {
    --i;
  }
  return i;
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






bool noLC(SEXP x) {
  R_xlen_t N = xlength(x);
  bool char_array[256] = {0};
  const SEXP * xp = STRING_PTR(x);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    const char * xi = CHAR(xp[i]);
    for (int j = 0; j < n; ++j) {
      unsigned char xj = xi[j];
      unsigned int xju = xj;
      char_array[xju] = true;
    }
  }

  for (unsigned int c = 0; c < 255; ++c) {
    unsigned char uc = (unsigned char)c;
    if (islower(uc) && char_array[c]) {
      return false;
    }
  }
  return true;
}

SEXP C_noLC(SEXP x) {
  if (TYPEOF(x) != STRSXP) {
    error("Internal error(EnsureUC): TYPEOF(x) != STRSXP.");
  }
  return ScalarLogical(noLC(x));
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

SEXP Cmatch_StreetType_Line1(SEXP xx, SEXP mm, SEXP jPos) {
  // This differs from Cmatch without Line1 in that we can assume the last
  // word in the string is the street type

  // m = return type
  // yy = Permitted street type
  // xx = address
  int np = 0;
  if (TYPEOF(xx) != STRSXP) {
    error("Wrong types"); // # nocov
  }

  R_xlen_t N = xlength(xx);
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;
  const bool hasNumberPosition = isInteger(jPos) && xlength(jPos) == N;
  const int * last_number_p = hasNumberPosition ? INTEGER(jPos) : INTEGER(mm);
  const SEXP * xp = STRING_PTR(xx);

  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    const char * x = CHAR(xp[i]);
    if (substring_within(x, n - 3, n, " RD", 3)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " DPS", 4)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " ROAD", 5)) {
      ansp[i] = ST_CODE_ROAD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " ST", 3)) {
      ansp[i] = ST_CODE_STREET + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 7, n, " STREET", 7)) {
      ansp[i] = ST_CODE_STREET;
      ansp[i] += m1 * (n - 7);
      if (hasNumberPosition) {
        ansp[i] += m2 * last_number_p[i];
        continue;
      }
      ansp[i] += m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " CT", 3)) {
      ansp[i] = ST_CODE_COURT + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " COURT", 6)) {
      ansp[i] = ST_CODE_COURT + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " AV", 3)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " AVE", 4)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " AVENUE", 7)) {
      ansp[i] = ST_CODE_AVENUE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " PL", 3)) {
      ansp[i] = ST_CODE_PLACE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " PLACE", 6)) {
      ansp[i] = ST_CODE_PLACE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " LN", 3)) {
      ansp[i] = ST_CODE_LANE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 5, n, " LANE", 5)) {
      ansp[i] = ST_CODE_LANE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " DR", 3)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 4, n, " DVE", 4)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " DRIVE", 6)) {
      ansp[i] = ST_CODE_DRIVE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " CL", 3)) {
      ansp[i] = ST_CODE_CLOSE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " CLOSE", 6)) {
      ansp[i] = ST_CODE_CLOSE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " TRK", 4)) {
      ansp[i] = ST_CODE_TRACK + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " TRACK", 6)) {
      ansp[i] = ST_CODE_TRACK + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 3, n, " CR", 3)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 5, n, " CRES", 5)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " CRESCENT", 9)) {
      ansp[i] = ST_CODE_CRESCENT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " WAY", 4)) {
      ansp[i] = ST_CODE_WAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 4, n, " WAY", 4)) {
      ansp[i] = ST_CODE_WAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 4, n, " TRL", 4)) {
      ansp[i] = ST_CODE_TRAIL + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " TRAIL", 6)) {
      ansp[i] = ST_CODE_TRAIL + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " HWY", 4)) {
      ansp[i] = ST_CODE_HIGHWAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " HIGHWAY", 8)) {
      ansp[i] = ST_CODE_HIGHWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " TCE", 4)) {
      ansp[i] = ST_CODE_TERRACE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " TERRACE", 8)) {
      ansp[i] = ST_CODE_TERRACE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " PDE", 4)) {
      ansp[i] = ST_CODE_PARADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " PARADE", 7)) {
      ansp[i] = ST_CODE_PARADE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 3, n, " GR", 3)) {
      ansp[i] = ST_CODE_GROVE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " GROVE", 6)) {
      ansp[i] = ST_CODE_GROVE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " ACCS", 5)) {
      ansp[i] = ST_CODE_ACCESS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " ACCESS", 7)) {
      ansp[i] = ST_CODE_ACCESS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " CCT", 4)) {
      ansp[i] = ST_CODE_CIRCUIT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " CIRCUIT", 8)) {
      ansp[i] = ST_CODE_CIRCUIT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " RAMP", 5)) {
      ansp[i] = ST_CODE_RAMP + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " BVD", 4)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " BLVD", 5)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BVDE", 5)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " BLVDE", 6)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " BOULEVARD", 10)) {
      ansp[i] = ST_CODE_BOULEVARD + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 5, n, " WALK", 5)) {
      ansp[i] = ST_CODE_WALK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " RISE", 5)) {
      ansp[i] = ST_CODE_RISE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " FIRETRAIL", 10)) {
      ansp[i] = ST_CODE_FIRETRAIL + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 6, n, " BREAK", 6)) {
      ansp[i] = ST_CODE_BREAK + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " LOOP", 5)) {
      ansp[i] = ST_CODE_LOOP + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MEWS", 5)) {
      ansp[i] = ST_CODE_MEWS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " LINK", 5)) {
      ansp[i] = ST_CODE_LINK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " GDNS", 5)) {
      ansp[i] = ST_CODE_GARDENS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " GARDENS", 8)) {
      ansp[i] = ST_CODE_GARDENS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " CIR", 4)) {
      ansp[i] = ST_CODE_CIRCLE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " CIRCLE", 7)) {
      ansp[i] = ST_CODE_CIRCLE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PKWY", 5)) {
      ansp[i] = ST_CODE_PARKWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PARKWAY", 8)) {
      ansp[i] = ST_CODE_PARKWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " FREEWAY", 8)) {
      ansp[i] = ST_CODE_FREEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " VIEW", 5)) {
      ansp[i] = ST_CODE_VIEW + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " RTT", 4)) {
      ansp[i] = ST_CODE_RETREAT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " RETREAT", 8)) {
      ansp[i] = ST_CODE_RETREAT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " COVE", 5)) {
      ansp[i] = ST_CODE_COVE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " ESP", 4)) {
      ansp[i] = ST_CODE_ESPLANADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 10, n, " ESPLANADE", 10)) {
      ansp[i] = ST_CODE_ESPLANADE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 3, n, " SQ", 3)) {
      ansp[i] = ST_CODE_SQUARE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 7, n, " SQUARE", 7)) {
      ansp[i] = ST_CODE_SQUARE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PASS", 5)) {
      ansp[i] = ST_CODE_PASS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " MOTORWAY", 9)) {
      ansp[i] = ST_CODE_MOTORWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " PHWY", 5)) {
      ansp[i] = ST_CODE_PATHWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PATHWAY", 8)) {
      ansp[i] = ST_CODE_PATHWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " VISTA", 6)) {
      ansp[i] = ST_CODE_VISTA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " TURN", 5)) {
      ansp[i] = ST_CODE_TURN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BEND", 5)) {
      ansp[i] = ST_CODE_BEND + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 3, n, " CH", 3)) {
      ansp[i] = ST_CODE_CHASE + m1 * (n - 3) + m2 * pos_preceding_word(x, n - 3); continue;
    }
    if (substring_within(x, n - 6, n, " CHASE", 6)) {
      ansp[i] = ST_CODE_CHASE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " GRN", 4)) {
      ansp[i] = ST_CODE_GREEN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GREEN", 6)) {
      ansp[i] = ST_CODE_GREEN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " ENTRANCE", 9)) {
      ansp[i] = ST_CODE_ENTRANCE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " HEIGHTS", 8)) {
      ansp[i] = ST_CODE_HEIGHTS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " GLEN", 5)) {
      ansp[i] = ST_CODE_GLEN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " PROMENADE", 10)) {
      ansp[i] = ST_CODE_PROMENADE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " ROW", 4)) {
      ansp[i] = ST_CODE_ROW + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " RDGE", 5)) {
      ansp[i] = ST_CODE_RIDGE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " RIDGE", 6)) {
      ansp[i] = ST_CODE_RIDGE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " FIREBREAK", 10)) {
      ansp[i] = ST_CODE_FIREBREAK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " GLD", 4)) {
      ansp[i] = ST_CODE_GLADE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GLADE", 6)) {
      ansp[i] = ST_CODE_GLADE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " APPROACH", 9)) {
      ansp[i] = ST_CODE_APPROACH + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " PATH", 5)) {
      ansp[i] = ST_CODE_PATH + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " RUN", 4)) {
      ansp[i] = ST_CODE_RUN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " BYPASS", 7)) {
      ansp[i] = ST_CODE_BYPASS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " ALLEY", 6)) {
      ansp[i] = ST_CODE_ALLEY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " ARCADE", 7)) {
      ansp[i] = ST_CODE_ARCADE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " ELBOW", 6)) {
      ansp[i] = ST_CODE_ELBOW + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " BRACE", 6)) {
      ansp[i] = ST_CODE_BRACE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " CNR", 4)) {
      ansp[i] = ST_CODE_CORNER + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " CORNER", 7)) {
      ansp[i] = ST_CODE_CORNER + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " RTE", 4)) {
      ansp[i] = ST_CODE_ROUTE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " ROUTE", 6)) {
      ansp[i] = ST_CODE_ROUTE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " RAMBLE", 7)) {
      ansp[i] = ST_CODE_RAMBLE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " FIRELINE", 9)) {
      ansp[i] = ST_CODE_FIRELINE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 9, n, " CROSSING", 9)) {
      ansp[i] = ST_CODE_CROSSING + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " GTE", 4)) {
      ansp[i] = ST_CODE_GATE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " GATE", 5)) {
      ansp[i] = ST_CODE_GATE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " GRA", 4)) {
      ansp[i] = ST_CODE_GRANGE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " GRANGE", 7)) {
      ansp[i] = ST_CODE_GRANGE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 8, n, " FAIRWAY", 8)) {
      ansp[i] = ST_CODE_FAIRWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " LOOKOUT", 8)) {
      ansp[i] = ST_CODE_LOOKOUT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " PNT", 4)) {
      ansp[i] = ST_CODE_POINT + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " POINT", 6)) {
      ansp[i] = ST_CODE_POINT + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " HILL", 5)) {
      ansp[i] = ST_CODE_HILL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " CRST", 5)) {
      ansp[i] = ST_CODE_CREST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " CREST", 6)) {
      ansp[i] = ST_CODE_CREST + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " LANEWAY", 8)) {
      ansp[i] = ST_CODE_LANEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 11, n, " EXPRESSWAY", 11)) {
      ansp[i] = ST_CODE_EXPRESSWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 5, n, " LINE", 5)) {
      ansp[i] = ST_CODE_LINE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MALL", 5)) {
      ansp[i] = ST_CODE_MALL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " MEANDER", 8)) {
      ansp[i] = ST_CODE_MEANDER + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " OUTLOOK", 8)) {
      ansp[i] = ST_CODE_OUTLOOK + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " BAY", 4)) {
      ansp[i] = ST_CODE_BAY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " CROSS", 6)) {
      ansp[i] = ST_CODE_CROSS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " WALKWAY", 8)) {
      ansp[i] = ST_CODE_WALKWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 10, n, " FIRETRACK", 10)) {
      ansp[i] = ST_CODE_FIRETRACK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 7, n, " BRIDGE", 7)) {
      ansp[i] = ST_CODE_BRIDGE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " PARK", 5)) {
      ansp[i] = ST_CODE_PARK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " PLAZA", 6)) {
      ansp[i] = ST_CODE_PLAZA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " NOOK", 5)) {
      ansp[i] = ST_CODE_NOOK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " WYND", 5)) {
      ansp[i] = ST_CODE_WYND + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " VALE", 5)) {
      ansp[i] = ST_CODE_VALE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " DOWNS", 6)) {
      ansp[i] = ST_CODE_DOWNS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " SPUR", 5)) {
      ansp[i] = ST_CODE_SPUR + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " BUSWAY", 7)) {
      ansp[i] = ST_CODE_BUSWAY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " CIRCUS", 7)) {
      ansp[i] = ST_CODE_CIRCUS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " POCKET", 7)) {
      ansp[i] = ST_CODE_POCKET + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 10, n, " BOARDWALK", 10)) {
      ansp[i] = ST_CODE_BOARDWALK + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 10, n, " CONCOURSE", 10)) {
      ansp[i] = ST_CODE_CONCOURSE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 4, n, " RVR", 4)) {
      ansp[i] = ST_CODE_RIVER + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " RIVER", 6)) {
      ansp[i] = ST_CODE_RIVER + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " QUAYS", 6)) {
      ansp[i] = ST_CODE_QUAYS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " RESERVE", 8)) {
      ansp[i] = ST_CODE_RESERVE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " DALE", 5)) {
      ansp[i] = ST_CODE_DALE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " ISLAND", 7)) {
      ansp[i] = ST_CODE_ISLAND + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " REST", 5)) {
      ansp[i] = ST_CODE_REST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 11, n, " CONNECTION", 11)) {
      ansp[i] = ST_CODE_CONNECTION + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 4, n, " END", 4)) {
      ansp[i] = ST_CODE_END + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " QUAY", 5)) {
      ansp[i] = ST_CODE_QUAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " VIEWS", 6)) {
      ansp[i] = ST_CODE_VIEWS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 4, n, " KEY", 4)) {
      ansp[i] = ST_CODE_KEY + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 9, n, " TRAVERSE", 9)) {
      ansp[i] = ST_CODE_TRAVERSE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 11, n, " BOULEVARDE", 11)) {
      ansp[i] = ST_CODE_BOULEVARDE + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 10, n, " FORMATION", 10)) {
      ansp[i] = ST_CODE_FORMATION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 7, n, " OUTLET", 7)) {
      ansp[i] = ST_CODE_OUTLET + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " DRWY", 5)) {
      ansp[i] = ST_CODE_DRIVEWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " DRIVEWAY", 9)) {
      ansp[i] = ST_CODE_DRIVEWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " LANDING", 8)) {
      ansp[i] = ST_CODE_LANDING + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " EDGE", 5)) {
      ansp[i] = ST_CODE_EDGE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 9, n, " QUADRANT", 9)) {
      ansp[i] = ST_CODE_QUADRANT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 7, n, " VALLEY", 7)) {
      ansp[i] = ST_CODE_VALLEY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " WATERS", 7)) {
      ansp[i] = ST_CODE_WATERS + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " CAUSEWAY", 9)) {
      ansp[i] = ST_CODE_CAUSEWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " BEACH", 6)) {
      ansp[i] = ST_CODE_BEACH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 11, n, " SERVICEWAY", 11)) {
      ansp[i] = ST_CODE_SERVICEWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 7, n, " CENTRE", 7)) {
      ansp[i] = ST_CODE_CENTRE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " EASEMENT", 9)) {
      ansp[i] = ST_CODE_EASEMENT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " PASSAGE", 8)) {
      ansp[i] = ST_CODE_PASSAGE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " STRIP", 6)) {
      ansp[i] = ST_CODE_STRIP + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " TARN", 5)) {
      ansp[i] = ST_CODE_TARN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " BRAE", 5)) {
      ansp[i] = ST_CODE_BRAE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 10, n, " DEVIATION", 10)) {
      ansp[i] = ST_CODE_DEVIATION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 9, n, " JUNCTION", 9)) {
      ansp[i] = ST_CODE_JUNCTION + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " STEPS", 6)) {
      ansp[i] = ST_CODE_STEPS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " WHARF", 6)) {
      ansp[i] = ST_CODE_WHARF + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " BOWL", 5)) {
      ansp[i] = ST_CODE_BOWL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " COURSE", 7)) {
      ansp[i] = ST_CODE_COURSE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " GAP", 4)) {
      ansp[i] = ST_CODE_GAP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " GULLY", 6)) {
      ansp[i] = ST_CODE_GULLY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " TUNNEL", 7)) {
      ansp[i] = ST_CODE_TUNNEL + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 8, n, " CUTTING", 8)) {
      ansp[i] = ST_CODE_CUTTING + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 4, n, " EST", 4)) {
      ansp[i] = ST_CODE_ESTATE + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " ESTATE", 7)) {
      ansp[i] = ST_CODE_ESTATE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 10, n, " EXTENSION", 10)) {
      ansp[i] = ST_CODE_EXTENSION + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 10, n, " FORESHORE", 10)) {
      ansp[i] = ST_CODE_FORESHORE + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 8, n, " GATEWAY", 8)) {
      ansp[i] = ST_CODE_GATEWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " HAVEN", 6)) {
      ansp[i] = ST_CODE_HAVEN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " ROTARY", 7)) {
      ansp[i] = ST_CODE_ROTARY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " COMMON", 7)) {
      ansp[i] = ST_CODE_COMMON + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " COPSE", 6)) {
      ansp[i] = ST_CODE_COPSE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 12, n, " DISTRIBUTOR", 12)) {
      ansp[i] = ST_CODE_DISTRIBUTOR + m1 * (n - 12) + m2 * pos_preceding_word(x, n - 12); continue;
    }
    if (substring_within(x, n - 7, n, " FOLLOW", 7)) {
      ansp[i] = ST_CODE_FOLLOW + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " FRONTAGE", 9)) {
      ansp[i] = ST_CODE_FRONTAGE + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 4, n, " TOR", 4)) {
      ansp[i] = ST_CODE_TOR + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 9, n, " ARTERIAL", 9)) {
      ansp[i] = ST_CODE_ARTERIAL + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " BANK", 5)) {
      ansp[i] = ST_CODE_BANK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " NORTH", 6)) {
      ansp[i] = ST_CODE_NORTH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " ROADS", 6)) {
      ansp[i] = ST_CODE_ROADS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " UNDERPASS", 10)) {
      ansp[i] = ST_CODE_UNDERPASS + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 5, n, " BROW", 5)) {
      ansp[i] = ST_CODE_BROW + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " HEATH", 6)) {
      ansp[i] = ST_CODE_HEATH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " LADDER", 7)) {
      ansp[i] = ST_CODE_LADDER + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " PRECINCT", 9)) {
      ansp[i] = ST_CODE_PRECINCT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " RANGE", 6)) {
      ansp[i] = ST_CODE_RANGE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " SOUTH", 6)) {
      ansp[i] = ST_CODE_SOUTH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " TRUNKWAY", 9)) {
      ansp[i] = ST_CODE_TRUNKWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 6, n, " AMBLE", 6)) {
      ansp[i] = ST_CODE_AMBLE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " BANAN", 6)) {
      ansp[i] = ST_CODE_BANAN + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " BRANCH", 7)) {
      ansp[i] = ST_CODE_BRANCH + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 6, n, " CORSO", 6)) {
      ansp[i] = ST_CODE_CORSO + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " DIVIDE", 7)) {
      ansp[i] = ST_CODE_DIVIDE + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " DOCK", 5)) {
      ansp[i] = ST_CODE_DOCK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " FORD", 5)) {
      ansp[i] = ST_CODE_FORD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " FORK", 5)) {
      ansp[i] = ST_CODE_FORK + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " GDN", 4)) {
      ansp[i] = ST_CODE_GARDEN + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 7, n, " GARDEN", 7)) {
      ansp[i] = ST_CODE_GARDEN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " HIKE", 5)) {
      ansp[i] = ST_CODE_HIKE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " HOLLOW", 7)) {
      ansp[i] = ST_CODE_HOLLOW + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 12, n, " INTERCHANGE", 12)) {
      ansp[i] = ST_CODE_INTERCHANGE + m1 * (n - 12) + m2 * pos_preceding_word(x, n - 12); continue;
    }
    if (substring_within(x, n - 6, n, " PALMS", 6)) {
      ansp[i] = ST_CODE_PALMS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " RIDE", 5)) {
      ansp[i] = ST_CODE_RIDE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " ROUND", 6)) {
      ansp[i] = ST_CODE_ROUND + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " SLOPE", 6)) {
      ansp[i] = ST_CODE_SLOPE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " STRAIT", 7)) {
      ansp[i] = ST_CODE_STRAIT + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 7, n, " SUBWAY", 7)) {
      ansp[i] = ST_CODE_SUBWAY + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 4, n, " TOP", 4)) {
      ansp[i] = ST_CODE_TOP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 8, n, " TRAMWAY", 8)) {
      ansp[i] = ST_CODE_TRAMWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 9, n, " BROADWAY", 9)) {
      ansp[i] = ST_CODE_BROADWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " CLUSTER", 8)) {
      ansp[i] = ST_CODE_CLUSTER + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " DELL", 5)) {
      ansp[i] = ST_CODE_DELL + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 7, n, " DOMAIN", 7)) {
      ansp[i] = ST_CODE_DOMAIN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " FLAT", 5)) {
      ansp[i] = ST_CODE_FLAT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " HUB", 4)) {
      ansp[i] = ST_CODE_HUB + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 6, n, " LYNNE", 6)) {
      ansp[i] = ST_CODE_LYNNE + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " MEAD", 5)) {
      ansp[i] = ST_CODE_MEAD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MILE", 5)) {
      ansp[i] = ST_CODE_MILE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " PORT", 5)) {
      ansp[i] = ST_CODE_PORT + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " REACH", 6)) {
      ansp[i] = ST_CODE_REACH + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 7, n, " RETURN", 7)) {
      ansp[i] = ST_CODE_RETURN + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 9, n, " STRAIGHT", 9)) {
      ansp[i] = ST_CODE_STRAIGHT + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 8, n, " VILLAGE", 8)) {
      ansp[i] = ST_CODE_VILLAGE + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 5, n, " WEST", 5)) {
      ansp[i] = ST_CODE_WEST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " WOODS", 6)) {
      ansp[i] = ST_CODE_WOODS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " ACRE", 5)) {
      ansp[i] = ST_CODE_ACRE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " BYWAY", 6)) {
      ansp[i] = ST_CODE_BYWAY + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " CENTREWAY", 10)) {
      ansp[i] = ST_CODE_CENTREWAY + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 8, n, " COMMONS", 8)) {
      ansp[i] = ST_CODE_COMMONS + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 8, n, " CONCORD", 8)) {
      ansp[i] = ST_CODE_CONCORD + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 10, n, " COURTYARD", 10)) {
      ansp[i] = ST_CODE_COURTYARD + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 6, n, " CRIEF", 6)) {
      ansp[i] = ST_CODE_CRIEF + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 10, n, " CRUISEWAY", 10)) {
      ansp[i] = ST_CODE_CRUISEWAY + m1 * (n - 10) + m2 * pos_preceding_word(x, n - 10); continue;
    }
    if (substring_within(x, n - 11, n, " CUL-DE-SAC", 11)) {
      ansp[i] = ST_CODE_CULDESAC + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 5, n, " DASH", 5)) {
      ansp[i] = ST_CODE_DASH + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " DENE", 5)) {
      ansp[i] = ST_CODE_DENE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 4, n, " DIP", 4)) {
      ansp[i] = ST_CODE_DIP + m1 * (n - 4) + m2 * pos_preceding_word(x, n - 4); continue;
    }
    if (substring_within(x, n - 5, n, " DOWN", 5)) {
      ansp[i] = ST_CODE_DOWN + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " EAST", 5)) {
      ansp[i] = ST_CODE_EAST + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " FLATS", 6)) {
      ansp[i] = ST_CODE_FLATS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 8, n, " HARBOUR", 8)) {
      ansp[i] = ST_CODE_HARBOUR + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 6, n, " HILLS", 6)) {
      ansp[i] = ST_CODE_HILLS + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " KEYS", 5)) {
      ansp[i] = ST_CODE_KEYS + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 6, n, " MANOR", 6)) {
      ansp[i] = ST_CODE_MANOR + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 5, n, " MART", 5)) {
      ansp[i] = ST_CODE_MART + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 5, n, " MAZE", 5)) {
      ansp[i] = ST_CODE_MAZE + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " PURSUIT", 8)) {
      ansp[i] = ST_CODE_PURSUIT + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 7, n, " RISING", 7)) {
      ansp[i] = ST_CODE_RISING + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
    }
    if (substring_within(x, n - 5, n, " RDWY", 5)) {
      ansp[i] = ST_CODE_ROADWAY + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }
    if (substring_within(x, n - 8, n, " ROADWAY", 8)) {
      ansp[i] = ST_CODE_ROADWAY + m1 * (n - 8) + m2 * pos_preceding_word(x, n - 8); continue;
    }
    if (substring_within(x, n - 11, n, " THROUGHWAY", 11)) {
      ansp[i] = ST_CODE_THROUGHWAY + m1 * (n - 11) + m2 * pos_preceding_word(x, n - 11); continue;
    }
    if (substring_within(x, n - 6, n, " TWIST", 6)) {
      ansp[i] = ST_CODE_TWIST + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 6, n, " VILLA", 6)) {
      ansp[i] = ST_CODE_VILLA + m1 * (n - 6) + m2 * pos_preceding_word(x, n - 6); continue;
    }
    if (substring_within(x, n - 9, n, " WATERWAY", 9)) {
      ansp[i] = ST_CODE_WATERWAY + m1 * (n - 9) + m2 * pos_preceding_word(x, n - 9); continue;
    }
    if (substring_within(x, n - 5, n, " YARD", 5)) {
      ansp[i] = ST_CODE_YARD + m1 * (n - 5) + m2 * pos_preceding_word(x, n - 5); continue;
    }

  }
  UNPROTECT(np);
  return ans;
}


SEXP Cmatch_StreetType(SEXP xx, SEXP yy, SEXP mm) {
  // m = return type
  // yy = Permitted street type
  // xx = address
  int np = 0;
  if (TYPEOF(xx) != STRSXP || TYPEOF(yy) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  R_xlen_t N = xlength(xx);
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;


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

// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
  }


// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(STRING_ELT(xx, i));
    // almost impossible (but required because we multiply the character position
    // by 256 to encode the position of the match
    //
    if (__builtin_expect(n >= 32768, 0)) {
      continue;
    }
    const char * x = CHAR(STRING_ELT(xx, i));

    // First check for 'THE ESPLANADE' etc
    if (string_first_word_THE(x, n, 0)) {
      ansp[i] = ST_CODE_ESPLANADE;
      continue;
    }





    int j = n - 4; // postcode
    while (j >= 4 && x[j] == ' ') {
      --j; // maybe 800
    }
    // Contemplate at least the street name and numbers
    while (--j > 10) {
      // not end of word
      if (x[j + 1] != ' ' && x[j + 1] != ',') {
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

  // Special case 'ST' may be Street but could also be e.g. 'ST KILDA' 'ST LEONARDS' 'ST ALBANS'
//#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int j = 4;
    bool maybe_street = false;
    for (; j < n - 6; ++j) {
      if (x[j] != ' ' && x[j] != ',') {
        continue;
      }
      if (x[j + 1] == 'S' &&
          x[j + 2] == 'T') {
        if (x[j + 3] == ' ' || x[j + 3] == ',') {
          j = j + 4;
          maybe_street = true;
          break;
        }
        if (x[j + 3] == '.' && (x[j + 4] == ' ' || x[j + 4] == ',')) {
          j = j + 4;
          maybe_street = true;
          break;
        }
        j += 2;
      }
    }
    if (!maybe_street) {
      continue;
    }
    if (substring_within(x, j, n, "IVES", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KILDA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "THOMAS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARYS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENA", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ALBANS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PETERS", 6)) {
      maybe_street = false;
      continue;
    }

    if (substring_within(x, j, n, "CLAIR", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS CREEK", 14)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "IVES", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGES BASIN", 13)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS PARK", 10)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PATRICKS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS PARK", 11)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ANDREWS", 7)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARYS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "VIDGEONS' STATION", 17)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGE", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHN", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KILDA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARY", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "AUBYN", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "RUTH", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LAWRENCE", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "AGNES", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "HELENS BEACH", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "BEES ISLAND", 11)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHN", 4)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LUCIA", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MORRIS", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.GEORGES", 10)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KITTS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.MORRIS", 9)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.CLAIR", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.PETERS", 9)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.AGNES", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.MARYS", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "KITTS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ST.KILDA", 8)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PATRICKS RIVER", 14)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ARNAUD", 6)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JAMES", 5)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "PETERS PLACE ESTATE", 19)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "ANTHONYS PLACE ESTATE", 21)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MARGARETS ESTATE", 16)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LUCIA ESTATE", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "JOHNS WOOD ESTATE", 17)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "MICHEL PRIVATE GARDEN ESTATE", 28)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "THOMAS PRIVATE ESTATE", 21)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "CLAIR ESTATE", 12)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LEONARDS ESTATE", 15)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "LAWRENCE ESTATE", 15)) {
      maybe_street = false;
      continue;
    }
    if (substring_within(x, j, n, "GEORGE RANGES", 13)) {
      maybe_street = false;
      continue;
    }



    // Note j - 2 not j - 6 because it's ST not STREET
    ansp[i] = ST_CODE_STREET + m1 * (j - 4) + m2 * pos_preceding_word(x, j - 4);





  }


  // A street name is more likely to follow a comma than a space
  // if commas are present.  Check commas:
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int last_comma = has_comma(x, n);
    if (!last_comma) {
      continue;
    }
    int word_sizes[16] = {0};
    int word_positions[16] = {0};
    unsigned int wsk = 0; // index of word_sizes
    // Find the sizes, positions of words preceding commas
    int this_word_size = 0;
    for (int jj = 0; jj <= last_comma; ++jj) {
      switch(x[jj]) {
      case ',':
    {
      // when ',' we record the size thus far and hence the position of the start
      word_positions[wsk] = jj - this_word_size;
      word_sizes[wsk] = this_word_size;
      this_word_size = 0;
      ++wsk;
    }
        break;
      case ' ':
        this_word_size = 0; // when ' ' we reset (i.e. don't count words preceding commas)
        break;
      default:
        ++this_word_size;
      }
    }

    bool matched = false;
    for (int w_ = 0; w_ < 16; ++w_) {
      int w = w_; // don't jump around

      if (matched) {
        break;
      }
      int len_word_i = word_sizes[w];
      if (len_word_i == 0) {
        continue;
      }

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
          ansp[i] = (k + 1) + m1 * (wpw - 1) + m2 * pos_preceding_word(x, wpw - 1);
        }
      }
    }

  }



// #pragma omp parallel for
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
// #pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    int xi = x[i];
    ansp[i] = xi == NA_INTEGER ? xi : xi & 255;
  }
  UNPROTECT(1);
  return ans;
}

SEXP digit2561(SEXP xx) {
  R_xlen_t N = xlength(xx);
  const int * x = INTEGER(xx);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
//// #pragma omp parallel for
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
// #pragma omp parallel for
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
// #pragma omp parallel for
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
                       SEXP StreetMatch1,
                       SEXP jPos,
                       SEXP ReturnHash) {
  R_xlen_t N = xlength(xx);
  if (!isString(xx)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(xx)));
  }
  if (!isInteger(StreetMatch1)) {
    error("`StreetMatch1` was type '%s' but must be an integer vector.", type2char(TYPEOF(StreetMatch1)));
  }
  if (!isInteger(jPos)) {
    error("`jPos` was type '%s' but must be an integer vector.", type2char(TYPEOF(jPos)));
  }
  const bool return_hash = asLogical(ReturnHash);

  const SEXP * xp = STRING_PTR(xx);
  const int * streetMatch1p = INTEGER(StreetMatch1);
  const int * last_number_p = INTEGER(jPos);
  const bool use_last_number = xlength(jPos) == N;
  if (xlength(StreetMatch1) != N) {
    error("Lengths differ(%d,%d).", use_last_number, xlength(StreetMatch1) & INT_MAX);
  }

  if (return_hash && use_last_number) {
    SEXP ans = PROTECT(allocVector(INTSXP, N));
    int * restrict ansp = INTEGER(ans);
    for (R_xlen_t i = 0; i < N; ++i) {

      int n = length(xp[i]);
      unsigned int si = streetMatch1p[i];
      if (n <= 4 || si > INT_MAX) {
        ansp[i] = NA_INTEGER;
        continue;
      }
      int lhs = last_number_p[i];
      int rhs = (si >> 8u) & 255;
      const char * x = CHAR(xp[i]);
      ansp[i] = djb2_hash(x, rhs, lhs);
    }
    UNPROTECT(1);
    return ans;
  }

  SEXP ans = PROTECT(allocVector(STRSXP, N));

  if (use_last_number) {
    for (R_xlen_t i = 0; i < N; ++i) {
      SEXP CX = xp[i];
      int n = length(xp[i]);
      unsigned int si = streetMatch1p[i];
      if (n <= 4 || si > INT_MAX) {
        SET_STRING_ELT(ans, i, NA_STRING);
        continue;
      }
      int si2 = last_number_p[i] + 1;
      int si1 = (si >> 8u) & 255;
      if (si1 <= si2) {
        if (i == 0) {
          Rprintf("(%d,%d)\n", si1, si2);
          continue;
        }
      }

      const char * x = CHAR(CX);
      char oy[si1 - si2 + 1];
      for (int j = si2; j < si1; ++j) {
        oy[j - si2] = x[j];
      }
      oy[si1 - si2] = '\0';
      const char * o = (const char *)oy;
      SET_STRING_ELT(ans, i, mkCharCE(o, CE_UTF8));

    }
  } else {
    for (R_xlen_t i = 0; i < N; ++i) {
      SEXP CX = STRING_ELT(xx, i);
      if (CX == NA_STRING) {
        SET_STRING_ELT(ans, i, CX);
        continue;
      }

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
  }
  UNPROTECT(1);
  return ans;
}




SEXP C_NumberSuffix2Raw(SEXP xx) {
  if (!isString(xx)) {
    error("`x` was type '%s' but must be a character vector.", type2char(TYPEOF(xx))); // # nocov
  }
  R_xlen_t N = xlength(xx);
  const SEXP * xp = STRING_PTR(xx);
  SEXP ans = PROTECT(allocVector(RAWSXP, N));
  unsigned char * ansp = RAW(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    int n = length(xp[i]);
    ansp[i] = 0;
    if (n) {
      const char * x = CHAR(xp[i]);
      char x0 = x[0];
      char x1 = n > 1 ? x[1] : '\0';
      ansp[i] = number_suffix2raw(x0, x1);
    }
  }
  UNPROTECT(1);
  return ans;
}

void do_standard_address(const char * x, int n, int numberFirstLast[3], int Street[2], int Postcode[2]) {
  int number_rhs = 0;
  int j_start = 0;
  const char x0 = x[0];
  if (!isdigit(x[0])) {
    const char x1 = x[1];
    const char x2 = x[2];
    if (x0 == 'C' && x1 == '/' && (x2 == '-' || x2 == 'O')) {
      // careof
      j_start = 3;
    }
  }
  int flat_number2i[2] = {0};
  do_flat_number(x, n, flat_number2i, j_start);

  int o1 = 0;
  int o2 = 0;

  // two numbers are separated by a dash
  bool two_numbers = false;
  // move after flat number:
  j_start = flat_number2i[1] > 0 ? (flat_number2i[0] + 1) : j_start;
  int j = j_start;
  for (; j < n - 4; ++j) {
    if (jchar_is_number(x, j)) {
      int digit = x[j] - '0';
      if (two_numbers) {
        o2 *= 10;
        o2 += digit;
      } else {
        o1 *= 10;
        o1 += digit;
      }
      continue;
    }
    if (x[j] == '-') {
      two_numbers = true;
      continue;
    }
    break; // don't continue on first encounter with non-number/dash
  }
  unsigned char this_suffix = number_suffix2raw(x[j], x[j + 1]);
  j += (this_suffix == 0 ? 0 : (islower(this_suffix) ? 2 : 1));


  int next_space_or_commas[4] = {0};
  bool has_comma = false;
  int b = 0;
  for (int k = j; (k < n && b < 4); ++k) {
    if (x[k] == ' ') {
      next_space_or_commas[b] = k;
      ++b;
      continue;
    }
    if (x[k] == ',') {
      has_comma = true;
      next_space_or_commas[b] = (k << 8u);
      ++b;
      continue;
    }
  }





  // int hstreet_name = djb2_hash();


}











