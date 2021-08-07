
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
  for (int i = 0; i < SUP_POSTCODES; ++i) {
    n_out += postcode_tbl[i];
  }
  SEXP ans = PROTECT(allocVector(INTSXP, n_out));
  int * restrict ansp = INTEGER(ans);
  for (int i = 0, j = 0; i < SUP_POSTCODES; ++i) {
    if (postcode_tbl[i]) {
      ansp[j] = i;
      ++j;
    }
  }
  UNPROTECT(1);
  return ans;
}


SEXP fast_nchar(SEXP x, SEXP na) {
  if (TYPEOF(x) != STRSXP || TYPEOF(na) != INTSXP || xlength(na) != 1) {
    error("fast_nchar only accepts STRSXP,INTSXP");
  }
  const int nai = asInteger(na);
  R_xlen_t N = xlength(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP xi = STRING_ELT(x, i);
    ansp[i] = xi == NA_STRING ? nai : length(xi);
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



SEXP Ctest_digit_of_from(SEXP X, SEXP J, SEXP Barrier) {
  if (!isString(X)) {
    error("X must be string");
  }
  if (!isInteger(J)) {
    error("J must be integer.");
  }
  if (!isString(Barrier)) {
    error("Barrier must be string.");
  }
  int j[1] = {asInteger(J)};
  const char * x = CHAR(STRING_ELT(X, 0));
  const char * barrier = CHAR(STRING_ELT(Barrier, 0));
  unsigned char b = barrier[0];
  int o = digit_of_from(x, j, b, strlen(x));
  return ScalarInteger(o);
}

static bool endsWith(const char * x, const char * y, int lenx, int leny) {
  // '012345'  len 6
  // 'abc345' : x
  //    '345' : 3

  int pos = lenx - leny;
  if (pos < 1) {
    return false;
  }
  // expect a space before
  if (x[pos - 1] != ' ') {
    return false;
  }
  char ans = true;
  for (int j = 0; j < leny; ++j) {
    ans &= x[pos + j] == y[j];
  }
  return ans;
}

static int whichStreetName3(const char * x, unsigned int len) {
  unsigned char x1 = x[len - 3];
  unsigned char x2 = x[len - 2];
  unsigned char x3 = x[len - 1];

  switch(x1) {
  case 'A':
    if (x2 == 'V' && x3 == 'E') {
      return ST_CODE_AVENUE;
    }
    break;
  case 'B':
    switch(x2) {
    case 'A':
      if (x3 == 'Y') {
        return ST_CODE_BAY;
      }
      break;
    case 'V':
      switch(x3) {
      case 'D':
        return ST_CODE_BOULEVARD;
      }
      break;
    case 'L':
      switch(x3) {
      case 'D':
        return ST_CODE_BOULEVARD;
      }
      break;
    }
    break;
  case 'C':
    if (x3 == 'T') {
      switch(x2) {
      case 'R':
        return ST_CODE_COURT;
      case 'C':
        return ST_CODE_CIRCUIT;
      }
    }
    if (x2 == 'I' && x3 == 'R') {
      return ST_CODE_CIRCLE;
    }
    if (x2 == 'R' && x3 == 'S') {
      return ST_CODE_CROSS;
    }
    break;
  case 'D':
    if ((x2 == 'R' && x3 == 'V') ||
        (x2 == 'V' && x3 == 'E')) {
      return ST_CODE_DRIVE;
    }
  case 'E':
    if (x2 == 'S' && x3 == 'P') {
      return ST_CODE_ESPLANADE;
    }
    break;
  case 'G':
    if (x2 == 'D' && x3 == 'N') {
      return ST_CODE_GARDEN;
    }
    if (x2 == 'L' && x3 == 'N') {
      return ST_CODE_GLEN;
    }
    if (x2 == 'R' && x3 == 'N') {
      return ST_CODE_GREEN;
    }
    if (x2 == 'R' && x3 == 'V') {
      return ST_CODE_GROVE;
    }
    if (x2 == 'V' && x3 == 'E') {
      return ST_CODE_GROVE;
    }
    break;
  case 'H':
    if (x2 == 'W' && x3 == 'Y') {
      return ST_CODE_HIGHWAY;
    }
    break;
  case 'P':
    if ((x2 == 'D' && x3 == 'E') ||
        (x2 == 'R' && x3 == 'D')) {
      return ST_CODE_PARADE;
    }
    break;
  case 'T':
    if (x2 == 'C' && x3 == 'E') {
      return ST_CODE_TERRACE;
    }
    break;
  case 'W':
    switch(x2) {
    case 'A':
      switch(x3) {
      case 'Y':
        return ST_CODE_WAY;
      }
    case 'L':
      switch(x3) {
      case 'K':
        return ST_CODE_WALK;
      }
      break;
    }
    break;
  }
  return NA_INTEGER;
}

SEXP CwhichStreetName3(SEXP x) {
  R_xlen_t N = xlength(x);
  if (N == 0 || TYPEOF(x) != STRSXP) {
    error("Internal error: N == 0 || TYPEOF(x) != STRSXP");
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  for (R_xlen_t i = 0; i < N; ++i) {
    if (STRING_ELT(x, i) == NA_STRING ||
        length(STRING_ELT(x, i)) != 3) {
      ansp[i] = NA_INTEGER;
      continue;
    }
    const char * xi = CHAR(STRING_ELT(x, i));

    ansp[i] = whichStreetName3(xi, 3U);
  }
  UNPROTECT(1);
  return ans;
}

static void whichStreetName(const char * x, unsigned int len, int ans[]) {
  // ans[0] = position of street name
  // ans[1] = which street name
  if (len < 5) {
    ans[0] = 0;
    ans[1] = 1;
    return;
  }

  // short forms
  if (x[len - 3] == ' ') {
    ans[0] = len - 3;
    unsigned char x1 = x[len - 2];
    unsigned char x2 = x[len - 1];
    if (x1 == 'D' && x2 == 'R') {
      ans[1] = ST_CODE_DRIVE;
      return;
    }
    if (x1 == 'R') {
      if (x2 == 'D') {
        ans[1] = 1;
        return;
      }
    }
    if (x1 == 'S') {
      if (x2 == 'T') {
        ans[1] = ST_CODE_STREET;
        return;
      }
      if (x2 == 'Q') {
        ans[1] = ST_CODE_SQUARE; // SQUARE
      }
    }
    if (x1 == 'C') {
      if (x1 == 'T') {
        ans[1] = 3;
        return;
      }
      if (x1 == 'L') {
        ans[1] = 8;
      }
      if (x1 == 'R') {
        ans[1] = 10;
      }
    }
  }
  if (x[len - 4] == ' ') {
    ans[0] = len - 4;
    ans[1] = whichStreetName3(x, len);
    return;
  }

  if (x[len - 1] == 'D' &&
      x[len - 2] == 'A' &&
      x[len - 3] == 'O' &&
      x[len - 4] == 'R') {
    ans[0] = len - 5;
    ans[1] = 1;
    return;
  }
  if (endsWith(x, "ROAD", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 1;
    return;
  }

  if (endsWith(x, "STREET", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 2;
    return;
  }

  if (endsWith(x, "COURT", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 3;
    return;
  }

  if (endsWith(x, "AVENUE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 4;
    return;
  }

  if (endsWith(x, "PLACE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 5;
    return;
  }

  if (endsWith(x, "LANE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 6;
    return;
  }

  if (endsWith(x, "DRIVE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 7;
    return;
  }

  if (endsWith(x, "CLOSE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 8;
    return;
  }

  if (endsWith(x, "TRACK", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 9;
    return;
  }

  if (endsWith(x, "CRESCENT", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 10;
    return;
  }

  if (endsWith(x, "WAY", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 11;
    return;
  }

  if (endsWith(x, "TRAIL", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 12;
    return;
  }

  if (endsWith(x, "HIGHWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 13;
    return;
  }

  if (endsWith(x, "TERRACE", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 14;
    return;
  }

  if (endsWith(x, "PARADE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 15;
    return;
  }

  if (endsWith(x, "GROVE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 16;
    return;
  }

  if (endsWith(x, "ACCESS", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 17;
    return;
  }

  if (endsWith(x, "CIRCUIT", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 18;
    return;
  }

  if (endsWith(x, "RAMP", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 19;
    return;
  }

  if (endsWith(x, "BOULEVARD", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 20;
    return;
  }

  if (endsWith(x, "WALK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 21;
    return;
  }

  if (endsWith(x, "RISE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 22;
    return;
  }

  if (endsWith(x, "FIRETRAIL", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 23;
    return;
  }

  if (endsWith(x, "BREAK", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 24;
    return;
  }

  if (endsWith(x, "LOOP", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 25;
    return;
  }

  if (endsWith(x, "MEWS", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 26;
    return;
  }

  if (endsWith(x, "LINK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 27;
    return;
  }

  if (endsWith(x, "GARDENS", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 28;
    return;
  }

  if (endsWith(x, "CIRCLE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 29;
    return;
  }

  if (endsWith(x, "PARKWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 30;
    return;
  }

  if (endsWith(x, "FREEWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 31;
    return;
  }

  if (endsWith(x, "VIEW", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 32;
    return;
  }

  if (endsWith(x, "RETREAT", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 33;
    return;
  }

  if (endsWith(x, "COVE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 34;
    return;
  }

  if (endsWith(x, "ESPLANADE", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 35;
    return;
  }

  if (endsWith(x, "SQUARE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 36;
    return;
  }

  if (endsWith(x, "PASS", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 37;
    return;
  }

  if (endsWith(x, "MOTORWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 38;
    return;
  }

  if (endsWith(x, "PATHWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 39;
    return;
  }

  if (endsWith(x, "VISTA", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 40;
    return;
  }

  if (endsWith(x, "TURN", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 41;
    return;
  }

  if (endsWith(x, "BEND", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 42;
    return;
  }

  if (endsWith(x, "CHASE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 43;
    return;
  }

  if (endsWith(x, "GREEN", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 44;
    return;
  }

  if (endsWith(x, "ENTRANCE", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 45;
    return;
  }

  if (endsWith(x, "HEIGHTS", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 46;
    return;
  }

  if (endsWith(x, "GLEN", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 47;
    return;
  }

  if (endsWith(x, "PROMENADE", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 48;
    return;
  }

  if (endsWith(x, "ROW", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 49;
    return;
  }

  if (endsWith(x, "RIDGE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 50;
    return;
  }

  if (endsWith(x, "FIREBREAK", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 51;
    return;
  }

  if (endsWith(x, "GLADE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 52;
    return;
  }

  if (endsWith(x, "APPROACH", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 53;
    return;
  }

  if (endsWith(x, "PATH", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 54;
    return;
  }

  if (endsWith(x, "RUN", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 55;
    return;
  }

  if (endsWith(x, "BYPASS", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 56;
    return;
  }

  if (endsWith(x, "ALLEY", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 57;
    return;
  }

  if (endsWith(x, "ARCADE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 58;
    return;
  }

  if (endsWith(x, "ELBOW", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 59;
    return;
  }

  if (endsWith(x, "BRACE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 60;
    return;
  }

  if (endsWith(x, "CORNER", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 61;
    return;
  }

  if (endsWith(x, "ROUTE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 62;
    return;
  }

  if (endsWith(x, "RAMBLE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 63;
    return;
  }

  if (endsWith(x, "FIRELINE", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 64;
    return;
  }

  if (endsWith(x, "CROSSING", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 65;
    return;
  }

  if (endsWith(x, "GATE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 66;
    return;
  }

  if (endsWith(x, "GRANGE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 67;
    return;
  }

  if (endsWith(x, "FAIRWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 68;
    return;
  }

  if (endsWith(x, "LOOKOUT", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 69;
    return;
  }

  if (endsWith(x, "POINT", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 70;
    return;
  }

  if (endsWith(x, "HILL", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 71;
    return;
  }

  if (endsWith(x, "CREST", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 72;
    return;
  }

  if (endsWith(x, "LANEWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 73;
    return;
  }

  if (endsWith(x, "EXPRESSWAY", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 74;
    return;
  }

  if (endsWith(x, "LINE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 75;
    return;
  }

  if (endsWith(x, "MALL", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 76;
    return;
  }

  if (endsWith(x, "MEANDER", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 77;
    return;
  }

  if (endsWith(x, "OUTLOOK", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 78;
    return;
  }

  if (endsWith(x, "BAY", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 79;
    return;
  }

  if (endsWith(x, "CROSS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 80;
    return;
  }

  if (endsWith(x, "WALKWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 81;
    return;
  }

  if (endsWith(x, "FIRETRACK", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 82;
    return;
  }

  if (endsWith(x, "BRIDGE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 83;
    return;
  }

  if (endsWith(x, "PARK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 84;
    return;
  }

  if (endsWith(x, "PLAZA", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 85;
    return;
  }

  if (endsWith(x, "NOOK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 86;
    return;
  }

  if (endsWith(x, "WYND", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 87;
    return;
  }

  if (endsWith(x, "VALE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 88;
    return;
  }

  if (endsWith(x, "DOWNS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 89;
    return;
  }

  if (endsWith(x, "SPUR", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 90;
    return;
  }

  if (endsWith(x, "BUSWAY", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 91;
    return;
  }

  if (endsWith(x, "CIRCUS", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 92;
    return;
  }

  if (endsWith(x, "POCKET", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 93;
    return;
  }

  if (endsWith(x, "BOARDWALK", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 94;
    return;
  }

  if (endsWith(x, "CONCOURSE", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 95;
    return;
  }

  if (endsWith(x, "RIVER", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 96;
    return;
  }

  if (endsWith(x, "QUAYS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 97;
    return;
  }

  if (endsWith(x, "RESERVE", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 98;
    return;
  }

  if (endsWith(x, "DALE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 99;
    return;
  }

  if (endsWith(x, "ISLAND", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 100;
    return;
  }

  if (endsWith(x, "REST", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 101;
    return;
  }

  if (endsWith(x, "CONNECTION", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 102;
    return;
  }

  if (endsWith(x, "END", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 103;
    return;
  }

  if (endsWith(x, "QUAY", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 104;
    return;
  }

  if (endsWith(x, "VIEWS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 105;
    return;
  }

  if (endsWith(x, "KEY", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 106;
    return;
  }

  if (endsWith(x, "TRAVERSE", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 107;
    return;
  }

  if (endsWith(x, "BOULEVARDE", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 108;
    return;
  }

  if (endsWith(x, "FORMATION", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 109;
    return;
  }

  if (endsWith(x, "OUTLET", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 110;
    return;
  }

  if (endsWith(x, "DRIVEWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 111;
    return;
  }

  if (endsWith(x, "LANDING", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 112;
    return;
  }

  if (endsWith(x, "EDGE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 113;
    return;
  }

  if (endsWith(x, "QUADRANT", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 114;
    return;
  }

  if (endsWith(x, "VALLEY", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 115;
    return;
  }

  if (endsWith(x, "WATERS", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 116;
    return;
  }

  if (endsWith(x, "CAUSEWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 117;
    return;
  }

  if (endsWith(x, "BEACH", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 118;
    return;
  }

  if (endsWith(x, "SERVICEWAY", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 119;
    return;
  }

  if (endsWith(x, "CENTRE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 120;
    return;
  }

  if (endsWith(x, "EASEMENT", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 121;
    return;
  }

  if (endsWith(x, "PASSAGE", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 122;
    return;
  }

  if (endsWith(x, "STRIP", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 123;
    return;
  }

  if (endsWith(x, "TARN", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 124;
    return;
  }

  if (endsWith(x, "BRAE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 125;
    return;
  }

  if (endsWith(x, "DEVIATION", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 126;
    return;
  }

  if (endsWith(x, "JUNCTION", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 127;
    return;
  }

  if (endsWith(x, "STEPS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 128;
    return;
  }

  if (endsWith(x, "WHARF", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 129;
    return;
  }

  if (endsWith(x, "BOWL", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 130;
    return;
  }

  if (endsWith(x, "COURSE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 131;
    return;
  }

  if (endsWith(x, "GAP", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 132;
    return;
  }

  if (endsWith(x, "GULLY", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 133;
    return;
  }

  if (endsWith(x, "TUNNEL", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 134;
    return;
  }

  if (endsWith(x, "CUTTING", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 135;
    return;
  }

  if (endsWith(x, "ESTATE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 136;
    return;
  }

  if (endsWith(x, "EXTENSION", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 137;
    return;
  }

  if (endsWith(x, "FORESHORE", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 138;
    return;
  }

  if (endsWith(x, "GATEWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 139;
    return;
  }

  if (endsWith(x, "HAVEN", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 140;
    return;
  }

  if (endsWith(x, "ROTARY", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 141;
    return;
  }

  if (endsWith(x, "COMMON", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 142;
    return;
  }

  if (endsWith(x, "COPSE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 143;
    return;
  }

  if (endsWith(x, "DISTRIBUTOR", len, 11)) {
    ans[0] = len - 11;
    ans[1] = 144;
    return;
  }

  if (endsWith(x, "FOLLOW", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 145;
    return;
  }

  if (endsWith(x, "FRONTAGE", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 146;
    return;
  }

  if (endsWith(x, "TOR", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 147;
    return;
  }

  if (endsWith(x, "ARTERIAL", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 148;
    return;
  }

  if (endsWith(x, "BANK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 149;
    return;
  }

  if (endsWith(x, "NORTH", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 150;
    return;
  }

  if (endsWith(x, "ROADS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 151;
    return;
  }

  if (endsWith(x, "UNDERPASS", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 152;
    return;
  }

  if (endsWith(x, "BROW", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 153;
    return;
  }

  if (endsWith(x, "HEATH", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 154;
    return;
  }

  if (endsWith(x, "LADDER", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 155;
    return;
  }

  if (endsWith(x, "PRECINCT", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 156;
    return;
  }

  if (endsWith(x, "RANGE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 157;
    return;
  }

  if (endsWith(x, "SOUTH", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 158;
    return;
  }

  if (endsWith(x, "TRUNKWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 159;
    return;
  }

  if (endsWith(x, "AMBLE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 160;
    return;
  }

  if (endsWith(x, "BANAN", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 161;
    return;
  }

  if (endsWith(x, "BRANCH", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 162;
    return;
  }

  if (endsWith(x, "CORSO", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 163;
    return;
  }

  if (endsWith(x, "DIVIDE", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 164;
    return;
  }

  if (endsWith(x, "DOCK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 165;
    return;
  }

  if (endsWith(x, "FORD", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 166;
    return;
  }

  if (endsWith(x, "FORK", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 167;
    return;
  }

  if (endsWith(x, "GARDEN", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 168;
    return;
  }

  if (endsWith(x, "HIKE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 169;
    return;
  }

  if (endsWith(x, "HOLLOW", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 170;
    return;
  }

  if (endsWith(x, "INTERCHANGE", len, 11)) {
    ans[0] = len - 11;
    ans[1] = 171;
    return;
  }

  if (endsWith(x, "PALMS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 172;
    return;
  }

  if (endsWith(x, "RIDE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 173;
    return;
  }

  if (endsWith(x, "ROUND", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 174;
    return;
  }

  if (endsWith(x, "SLOPE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 175;
    return;
  }

  if (endsWith(x, "STRAIT", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 176;
    return;
  }

  if (endsWith(x, "SUBWAY", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 177;
    return;
  }

  if (endsWith(x, "TOP", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 178;
    return;
  }

  if (endsWith(x, "TRAMWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 179;
    return;
  }

  if (endsWith(x, "BROADWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 180;
    return;
  }

  if (endsWith(x, "CLUSTER", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 181;
    return;
  }

  if (endsWith(x, "DELL", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 182;
    return;
  }

  if (endsWith(x, "DOMAIN", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 183;
    return;
  }

  if (endsWith(x, "FLAT", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 184;
    return;
  }

  if (endsWith(x, "HUB", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 185;
    return;
  }

  if (endsWith(x, "LYNNE", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 186;
    return;
  }

  if (endsWith(x, "MEAD", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 187;
    return;
  }

  if (endsWith(x, "MILE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 188;
    return;
  }

  if (endsWith(x, "PORT", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 189;
    return;
  }

  if (endsWith(x, "REACH", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 190;
    return;
  }

  if (endsWith(x, "RETURN", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 191;
    return;
  }

  if (endsWith(x, "STRAIGHT", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 192;
    return;
  }

  if (endsWith(x, "VILLAGE", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 193;
    return;
  }

  if (endsWith(x, "WEST", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 194;
    return;
  }

  if (endsWith(x, "WOODS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 195;
    return;
  }

  if (endsWith(x, "ACRE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 196;
    return;
  }

  if (endsWith(x, "BYWAY", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 197;
    return;
  }

  if (endsWith(x, "CENTREWAY", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 198;
    return;
  }

  if (endsWith(x, "COMMONS", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 199;
    return;
  }

  if (endsWith(x, "CONCORD", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 200;
    return;
  }

  if (endsWith(x, "COURTYARD", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 201;
    return;
  }

  if (endsWith(x, "CRIEF", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 202;
    return;
  }

  if (endsWith(x, "CRUISEWAY", len, 9)) {
    ans[0] = len - 9;
    ans[1] = 203;
    return;
  }

  if (endsWith(x, "CUL-DE-SAC", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 204;
    return;
  }

  if (endsWith(x, "DASH", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 205;
    return;
  }

  if (endsWith(x, "DENE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 206;
    return;
  }

  if (endsWith(x, "DIP", len, 3)) {
    ans[0] = len - 3;
    ans[1] = 207;
    return;
  }

  if (endsWith(x, "DOWN", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 208;
    return;
  }

  if (endsWith(x, "EAST", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 209;
    return;
  }

  if (endsWith(x, "FLATS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 210;
    return;
  }

  if (endsWith(x, "HARBOUR", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 211;
    return;
  }

  if (endsWith(x, "HILLS", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 212;
    return;
  }

  if (endsWith(x, "KEYS", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 213;
    return;
  }

  if (endsWith(x, "MANOR", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 214;
    return;
  }

  if (endsWith(x, "MART", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 215;
    return;
  }

  if (endsWith(x, "MAZE", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 216;
    return;
  }

  if (endsWith(x, "PURSUIT", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 217;
    return;
  }

  if (endsWith(x, "RISING", len, 6)) {
    ans[0] = len - 6;
    ans[1] = 218;
    return;
  }

  if (endsWith(x, "ROADWAY", len, 7)) {
    ans[0] = len - 7;
    ans[1] = 219;
    return;
  }

  if (endsWith(x, "THROUGHWAY", len, 10)) {
    ans[0] = len - 10;
    ans[1] = 220;
    return;
  }

  if (endsWith(x, "TWIST", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 221;
    return;
  }

  if (endsWith(x, "VILLA", len, 5)) {
    ans[0] = len - 5;
    ans[1] = 222;
    return;
  }

  if (endsWith(x, "WATERWAY", len, 8)) {
    ans[0] = len - 8;
    ans[1] = 223;
    return;
  }

  if (endsWith(x, "YARD", len, 4)) {
    ans[0] = len - 4;
    ans[1] = 224;
    return;
  }



  return;
}


SEXP CExtractStdAddress(SEXP address, SEXP street_names) {

  R_xlen_t N = xlength(address);
  // R_xlen_t nNames = xlength(street_names);
  if (TYPEOF(address) != STRSXP) {
    error("TYPEOF(address) != STRSXP");
  }
  if (TYPEOF(street_names) != STRSXP) {
    error("TYPEOF(street_names) != STRSXP");
  }


  SEXP flat_number = PROTECT(allocVector(INTSXP, N));

  SEXP number_first = PROTECT(allocVector(INTSXP, N));
  SEXP number_final = PROTECT(allocVector(INTSXP, N));
  SEXP street_name = PROTECT(allocVector(STRSXP, N));
  SEXP street_type = PROTECT(allocVector(INTSXP, N));

  int * restrict flat_numberp = INTEGER(flat_number);
  int * restrict street_typep = INTEGER(street_type);
  int * restrict number_firstp = INTEGER(number_first);
  int * restrict number_finalp = INTEGER(number_final);

  for (R_xlen_t i = 0; i < N; ++i) {
    flat_numberp[i] = NA_INTEGER;
    street_typep[i] = NA_INTEGER;
    number_firstp[i] = NA_INTEGER;
    SEXP xi = STRING_ELT(address, i);
    if (xi == NA_STRING || length(xi) == 0) {

      SET_STRING_ELT(street_name, i, NA_STRING);
      continue;
    }
    int unit_no = NA_INTEGER;
    int len = length(xi);
    const char * xc = CHAR(xi);
    int j = 0;
    int J[1] = {0};
    char xcj = toupper1(xc[j]);
    // trim whitespace
    while (xcj == ' ') {
      ++j;
    }
    // Find units
    if (xcj == 'U' &&
        len > j + 5 &&
        xc[j + 1] == ' ' &&
        char_is_number(xc[j + 2])) {
      // U 25  Abc
      int j2[1] = {j + 2};
      unit_no = digit_of_from(xc, j2, ' ', len);
      j = j2[0];
    } else if (xcj == 'G' && char_is_number(xc[j + 1])) {
      int j1[1] = {j + 1};
      unit_no = digit_of_from(xc, j1, '/', len);
      j = j1[0];
    } else {
      // check for /
      int where_is_slash = 0; // note that a slash at position 0 means no unit
      for (int k = 1; k < len; ++k) {
        if (xc[k] == '/') {
          where_is_slash = k;
          break;
        }
      }
      if (where_is_slash) {
        int j1[1] = {0};
        unit_no = digit_of_from(xc, j1, '/', len);
        j = j1[0] + 1;
      }
    }

    // street numbers
    while (j < len && !char_is_number(xc[j])) {
      ++j;
    }
    J[0] = j;
    int street_number = digit_of_from(xc, J, ' ', len);
    j = J[0];

    // Now we work backwards to find the street name
    int street_name_pos[2] = {j, NA_INTEGER};
    whichStreetName(xc, len, street_name_pos);

    int a = J[0], b = street_name_pos[0];
    if (b <= a) {
      b = len;
    }
    // trimws
    while (a < b && xc[a] == ' ') {
      ++a;
    }
    while (b > a && xc[b - 1] == ' ') {
      --b;
    }
    int nchar_street_names = b - a;
    if (nchar_street_names <= 0) {
      SET_STRING_ELT(street_name, i, mkCharCE("", CE_UTF8));
    } else {
      char nom[nchar_street_names + 1];
      for (int jj = a; jj < b; ++jj) {
        nom[jj - a] = xc[jj];
      }
      nom[nchar_street_names] = '\0';
      SET_STRING_ELT(street_name, i, mkCharCE((const char *)nom, CE_UTF8));
    }

    flat_numberp[i] = unit_no;
    number_firstp[i] = street_number;
    street_typep[i] = street_name_pos[1];
  }
  SEXP ans = PROTECT(allocVector(VECSXP, 4));
  SET_VECTOR_ELT(ans, 0, flat_number);
  SET_VECTOR_ELT(ans, 1, street_name);
  SET_VECTOR_ELT(ans, 2, street_type);
  SET_VECTOR_ELT(ans, 3, number_first);
  UNPROTECT(5);

  return ans;
}



int whichIsntValidStreetType(SEXP x, SEXP yy) {
  R_xlen_t N = xlength(x);
  if (TYPEOF(yy) == INTSXP && N == xlength(yy)) {

    const int * y = INTEGER(yy);
    int miny = 1;
    for (R_xlen_t i = 1; i < N; ++i) {
      if (miny > y[i]) {
        miny = y[i];
      }
    }
    return miny > 0 ? 0 : 1;
  }

  if (TYPEOF(x) != STRSXP) {
    return 1;
  }
  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP CX = STRING_ELT(x, i);
    // if (__builtin_expect(CX == NA_STRING, 0)) {
    //   return i + 1;
    // }
    int n = length(CX);
    const char * xp = CHAR(CX);
    for (int j = 0; j < n; ++j) {
      if (!jchar_is_LETTER_or_hyphen(xp, j)) {
        return i + 1;
      }
    }
  }
  return 0;
}

SEXP Ctest_touppers(SEXP xx) {
  if (!isString(xx)) {
    error("Not string");
  }
  SEXP ans = PROTECT(allocVector(STRSXP, 1));
  const char * xp = CHAR(STRING_ELT(xx, 0));
  int len = length(STRING_ELT(xx, 0));
  char o[len + 1];
  for (int i = 0; i < len; ++i) {
    o[i] = toupper1(xp[i]);
  }
  o[len] = '\0';
  const char * yp = (const char *)o;
  SET_STRING_ELT(ans, 0, mkCharCE(yp, CE_UTF8));
  UNPROTECT(1);
  return ans;
}

SEXP CExtractPostcode(SEXP x) {
  R_xlen_t N = xlength(x);
  const SEXP * xpp = STRING_PTR(x);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
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

SEXP Extract2(SEXP xx, SEXP id, SEXP Postcodes, SEXP StreetTypes, SEXP StreetNames, SEXP Numbers,
              SEXP StreetTypeCd) {
  if (TYPEOF(xx) != STRSXP ||
      TYPEOF(id) != INTSXP ||
      TYPEOF(Postcodes) != INTSXP ||
      TYPEOF(StreetTypes) != STRSXP ||
      TYPEOF(StreetNames) != STRSXP ||
      TYPEOF(Numbers) != INTSXP) {
    error("Extract2 wrong types.");
  }
  R_xlen_t N = xlength(xx);
  int M = length(id);
  if (M != xlength(StreetTypes) ||
      M != xlength(Postcodes) ||
      M != xlength(StreetNames) ||
      M != xlength(Numbers)) {
    error("Wrong lengths.");
  }
  const int * idp = INTEGER(id);
  const int * postcodes = INTEGER(Postcodes);
  if (N_POSTCODES >= 32768) {
    error("N_POSTCODES >= 32768");
  }
  if (postcodes[0] < 800) {
    error("postcodes[0] = %d < 800", postcodes[0]);
  }
  if (postcodes[M - 1] > 8192) {
    error("postcodes[M - 1] = %d > 8192", postcodes[M - 1]);
  }
  int wrong_street_type = whichIsntValidStreetType(StreetTypes, StreetTypeCd);
  if (wrong_street_type) {
    error("StreetTypes had invalid street type (not uppercase or hyphen) at position %d ", wrong_street_type);
  }

  // 8192 > max(POSTCODE)
  unsigned int postcode_starts[8192] = {0};
  unsigned int postcode_finals[8192] = {0};
  postcode_starts[postcodes[0]] = 0;
  for (int i = 1; i < M; ++i) {
    int p0 = postcodes[i - 1];
    int p1 = postcodes[i];
    if (p0 != p1) {
      postcode_starts[p1] = i;
      postcode_finals[p0] = i;
    }
  }
  postcode_finals[postcodes[M - 1]] = M;

  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);

  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int n = length(STRING_ELT(xx, i));
    if (n < 10) {
      continue;
    }
    const char * x = CHAR(STRING_ELT(xx, i));

    int postcodei = xpostcode_unsafe(x, n);
    const int postcode_start = postcode_starts[postcodei];
    const int postcode_final = postcode_finals[postcodei];
    // find spaces and first string of non-numbers
    int space_locs[8] = {0}; // the position of spaces as words boundaries
    int word_widths[8] = {0}; // the width of every word following space_locs
    int pos_last_number = 0;
    int s_j = 0;
    // j < n - 4 to avoid numbers in postcode
    for (int j = 1; j < (n - 4); ++j) {
      char xj = x[j];
      char xj0 = x[j - 1];

      if (xj0 == ' ') {
        continue;
      }
      if (xj == ' ') {
        space_locs[s_j] = j;
        ++s_j;
        if (char_is_number(xj)) {
          pos_last_number = j;
        }
      }
    }
    for (int sj = 0; sj < 8; ++sj) {
      if (!space_locs[sj]) {
        continue;
      }
      // Move until next space, but only increment word_widths
      // when not space.  The distinction is important because
      // non-letters/numbers such as ',' are mapped to spaces,
      // causing repeated ' ' and we only care about the widths
      // of the words proper (and not numbers).
      int j_min = space_locs[sj] + 1;
      int j_max = sj == 7 ? n : space_locs[sj + 1];
      for (int j = j_min; j < j_max; ++j) {
        word_widths[sj] += jchar_is_LETTER(x, j);
      }
    }

    // now look from the pos last number and see if it's street name street type
    bool matched = false;
    for (int sj = 0; sj < 7; ++sj) {
      if (matched) {
        break;
      }
      int j = space_locs[sj];
      if (j < pos_last_number) {
        continue;
      }
      ++j;
      int j2 = space_locs[sj + 1] + 1;
      // N.B. only the StreetType have no spaces
      int len_this_word = word_widths[sj];
      int len_next_word = word_widths[sj + 1];
      if (len_this_word) {
      } else {
        continue;
      }

      // We are now at the first character of a candidate
      // street name. Designate s as the index of StreetNames,StreetType
      // and k as the character position relative to the start of the word
      // in each.
      for (int s = postcode_start; s < postcode_final; ++s) {
        int id_if_matched = idp[s];
        const char * street_name_s = CHAR(STRING_ELT(StreetNames, s));
        const char * street_type_s = CHAR(STRING_ELT(StreetTypes, s));
        int len_name = length(STRING_ELT(StreetNames, s));
        int len_type = length(STRING_ELT(StreetTypes, s));

        int wcis = which_char_is_space(street_name_s, len_name);
        if (!wcis) {
          // now we can just assume that the first word is the street name
          // and the second is the type
          if (len_this_word != len_name || len_next_word != len_type) {
            continue;
          }
          matched = true;
          // note len_this_word == len_name necessarily
          for (int k = 0; k < len_name; ++k) {
            unsigned char xjk = x[j + k];
            unsigned char yjk = street_name_s[k];
            if (xjk != yjk) {
              matched = false;
              break;
            }
          }
          if (!matched) {
            continue;
          }
          for (int k = 0; k < len_type; ++k) {
            unsigned char xjk = x[j2 + k];
            unsigned char yjk = street_type_s[k];
            if (xjk != yjk) {
              matched = false;
              break;
            }
          }
        }

        if (matched) {
          ansp[i] = id_if_matched;
          break; // from postcode loop, but will immediately break on outer loop.
        }
      }

    }
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

int NamePresent(int j, const char * x, int n, SEXP Names, int from, int to) {
  if (!char_is_LETTER(x[j])) {
    return NA_INTEGER;
  }
  const char first_letter = x[j];

  for (int k = from; k < to; ++k) {
    int nk = length(STRING_ELT(Names, k));
    if (j + nk > n) {
      continue;
    }
    if (x[j + nk] != ' ') {
      continue;
    }
    const char * nomk = CHAR(STRING_ELT(Names, k));
    if (nomk[0] != first_letter) {
      continue;
    }
    bool matched = true; // provisional
    for (int kk = 1; kk < nk; ++nk) {
      if (nomk[kk] != x[j + kk]) {
        matched = false;
        break;
      }
    }
    if (matched) {
      return k;
    }
  }
  return NA_INTEGER;
}

SEXP CNamePresent(SEXP J, SEXP X, SEXP Names, SEXP From, SEXP To) {
  const int j = asInteger(J);
  if (TYPEOF(X) != STRSXP || xlength(X) != 1 || TYPEOF(Names) != STRSXP) {
    error("TYPEOF(X) != STRSXP");
  }
  const int from = asInteger(From);
  const int to = asInteger(To);
  if (from > to || to >= xlength(Names)) {
    error("from,to bad");
  }
  int n = length(STRING_ELT(X, 0));
  const char * x = CHAR(STRING_ELT(X, 0));
  int o = NamePresent(j, x, n, Names, from, to);
  return ScalarInteger(o);
}




void do_flat_number(const char * x, int n, int ans[2]) {
  ans[0] = 0; // position after last digit of flat number
  ans[0] = 0; // the flat number itself
  if (n < 4) {
    return;
  }
  // position j so that it points to the first digit of the flat number
  int j = 0;
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

  int * restrict nun = INTEGER(n_unit);
  int * restrict nfp = INTEGER(nfirst);
  int * restrict nfl = INTEGER(nfinal);

  for (R_xlen_t i = 0; i < N; ++i) {
    nun[i] = NA_INTEGER;
    nfp[i] = NA_INTEGER;
    nfl[i] = NA_INTEGER;
    if (xp[i] == NA_STRING) {
      continue;
    }
    int n = length(xp[i]);
    const char * x = CHAR(xp[i]);
    int flat_number2i[2] = {0};
    do_flat_number(x, n, flat_number2i);
    nun[i] = flat_number2i[1];

    int o1 = 0;
    int o2 = 0;

    // two numbers are separated by a dash
    bool two_numbers = false;
    // move after flat number:
    int j_start = flat_number2i[0] + 1;
    for (int j = j_start; j < n - 4; ++j) {
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
    nfp[i] = o1;
    nfl[i] = o2;

  }
  SEXP ans = PROTECT(allocVector(VECSXP, 3)); ++np;
  SET_VECTOR_ELT(ans, 0, n_unit);
  SET_VECTOR_ELT(ans, 1, nfirst);
  SET_VECTOR_ELT(ans, 2, nfinal);

  UNPROTECT(np);
  return ans;

}



SEXP CExtractAddressID(SEXP xx,
                       SEXP xxPostcodes,
                       SEXP id,
                       SEXP Postcodes,
                       SEXP StreetTypesCd, SEXP StreetNames, SEXP Numbers,
                       SEXP Postcode2,
                       SEXP StreetTypes2,
                       SEXP Checks) {
  int np = 0;
  const bool check = asLogical(Checks);
  R_xlen_t N = xlength(xx);
  if (TYPEOF(xx) != STRSXP ||
      TYPEOF(xxPostcodes) != INTSXP ||
      xlength(xxPostcodes) != N) {
    error("(ExtractAddressID_AA): wrong types.");
  }
  if (TYPEOF(id) != INTSXP) {
    error("id not INTSXP");
  }
  if (TYPEOF(Postcodes) != INTSXP) {
    error("Postcodes not INTSXP");
  }
  if (TYPEOF(StreetTypesCd) != INTSXP) {
    error("(ExtractAddressID_AA): StreetTypesCd != INTSXP.");
  }
  if (TYPEOF(StreetNames) != STRSXP ||
      TYPEOF(Numbers) != INTSXP) {
    error("(ExtractAddressID_B): wrong types.");
  }
  int M = length(id);
  if (M != xlength(StreetTypesCd) ||
      M != xlength(Postcodes) ||
      M != xlength(StreetNames) ||
      M != xlength(Numbers)) {
    error("(ExtractAddressID):Wrong lengths.");
  }
  int M2 = length(Postcode2);
  if (TYPEOF(Postcode2) != INTSXP) {
    error("Postcode2 is not INT");
  }
  if (TYPEOF(StreetTypes2) != INTSXP) {
    error("StreetTypes2 not INTSXP");
  }
  if (xlength(StreetTypes2) != M2) {
    error("(ExtractAddressID): (2) wrong types.");
  }

  if (check && isnt_sorted_asc(xxPostcodes)) {
    error("Addresses were not sorted by their (extracted) postcodes at position %d",
          isnt_sorted_asc(xxPostcodes));
  }
  if (check && isnt_sorted_asc(Postcodes)) {
    error("Postcodes was not sorted at position %d.", isnt_sorted_asc(Postcodes));
  }

  const int * xxpostcodes = INTEGER(xxPostcodes);
  const int * idp = INTEGER(id);
  const int * postcodes = INTEGER(Postcodes);
  const int * street_types_cd = INTEGER(StreetTypesCd);
  const int * numbers = INTEGER(Numbers);

  unsigned int postcode_starts[8192] = {0};
  unsigned int postcode_finals[8192] = {0};
  postcode_starts[postcodes[0]] = 0;
  for (int i = 1; i < M; ++i) {
    int p0 = postcodes[i - 1];
    int p1 = postcodes[i];
    if (p0 != p1) {
      postcode_starts[p1] = i;
      postcode_finals[p0] = i;
    }
  }
  postcode_finals[postcodes[M - 1]] = M;

  const int * postcodes2 = INTEGER(Postcode2);
  const int * street_types2 = INTEGER(StreetTypes2);

  unsigned int postcode2_starts[8192] = {0};
  unsigned int postcode2_finals[8192] = {0};
  postcode2_starts[postcodes2[0]] = 0;
  for (int i = 1; i < M2; ++i) {
    int p0 = postcodes2[i - 1];
    int p1 = postcodes2[i];
    if (p0 != p1) {
      postcode2_starts[p1] = i;
      postcode2_finals[p0] = i;
    }
  }
  postcode2_finals[postcodes2[M2 - 1]] = M2;



  SEXP ans = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict ansp = INTEGER(ans);

  // Now we create a vector where
  //                                      /   1  if street_type exists in postcode
  //   v[i * postcode + street_type_cd] = |
  //                                      \   0 if not
  unsigned int npostcode_nsttype = SUP_POSTCODES * N_STREET_TYPES;
  SEXP ST_TYPES_POSTCODE = PROTECT(allocVector(RAWSXP, npostcode_nsttype)); np++;
  unsigned char * ST_TYPES_POSTCODEp = RAW(ST_TYPES_POSTCODE);
  for (unsigned int k = 0; k < npostcode_nsttype; ++k) {
    ST_TYPES_POSTCODEp[k] = 0;
  }
  if (false) {

    for (int i = 0; i < M2; ++i) {
      unsigned int postcode2i = postcodes2[i];
      unsigned int street_type_enc = street_types2[i];
      unsigned int k = postcode2i * SUP_POSTCODES + street_type_enc;


      ST_TYPES_POSTCODEp[k] = 1;
    }
  }


  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = NA_INTEGER;
    int postcodei = xxpostcodes[i];
    if (postcodei == NA_INTEGER) {
      continue;
    }
    int postcode2_start = postcode2_starts[postcodei];
    int postcode2_final = postcode2_finals[postcodei];

    int n = length(STRING_ELT(xx, i));
    if (n < 10) {
      continue;
    }
    const char * x = CHAR(STRING_ELT(xx, i));
    int pos_last_number = n - 4;
    for (; pos_last_number >= 0; --pos_last_number) {
      if (char_is_number(x[pos_last_number])) {
        break;
      }
    }

    if (poa_has_ROAD(postcodei) && has_ROAD(x, n)) {
      ansp[i] = ST_CODE_ROAD;
      continue;
    }
    if (poa_has_street_type(postcodei, ST_CODE_STREET) && has_STREET(x, n)) {
      for (int j = pos_last_number; j < n; ++j) {
        // char xj = x[j];

      }

      ansp[i] = ST_CODE_STREET;
      continue;
    }
    if (has_COURT(x, n)) {
      ansp[i] = ST_CODE_COURT;
      continue;
    }
    if (has_DRIVE(x, n)) {
      ansp[i] = ST_CODE_DRIVE;
      continue;
    }
    if (has_AVENUE(x, n)) {
      ansp[i] = ST_CODE_AVENUE;
      continue;
    }
    if (has_PLACE(x, n)) {
      ansp[i] = ST_CODE_PLACE;
      continue;
    }
    if (has_LANE(x, n)) {
      ansp[i] = ST_CODE_LANE;
      continue;
    }
    if (has_WAY(x, n)) {
      ansp[i] = ST_CODE_WAY;
      continue;
    }
    if (has_CLOSE(x, n)) {
      ansp[i] = ST_CODE_CLOSE;
      continue;
    }

    // for (int k = n - 4; k >= 1; --k) {
    //
    //   unsigned char xk0 = x[k - 1];
    //   unsigned char xk1 = x[k];
    //   unsigned char xk2 = x[k + 1];
    //
    //   int street_cd_k = 0;
    // }

  }


  UNPROTECT(np);
  return ans;
}





