
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





// space unless a number or letter then uppercase
/*
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
 */

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

int has_comma(const char * x, int n) {
  int i = n - 1;
  while (i >= 0 && x[i] != ',') {
    --i;
  }
  return i;
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
      if (islower(xij)) {
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
  // if (isUC(x)) {
  //   return x;
  // }
  R_xlen_t N = xlength(x);

  SEXP ans = PROTECT(allocVector(STRSXP, N));
  for (R_xlen_t i = 0; i < N; ++i) {
    const char * xi = CHAR(STRING_ELT(x, i));
    int n = length(STRING_ELT(x, i));
    char oi[n + 1];
    for (int j = 0; j < n; ++j) {
      oi[j] = toupper(xi[j]);
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

SEXP Cmatch_StreetType_Line1(SEXP xx, SEXP mm) {
  // This differs from Cmatch without Line1 in that we can assume the last
  // word in the string is the street type

  // m = return type
  // yy = Permitted street type
  // xx = address
  int np = 0;
  if (TYPEOF(xx) != STRSXP) {
    error("Wrong types"); // # nocov
  }
  const int m = asInteger(mm) ;
  const unsigned int m1 = m > 0 ? 256 : 0;
  const unsigned int m2 = m == 2 ? 65536 : 0;
  R_xlen_t N = xlength(xx);
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
      ansp[i] = ST_CODE_STREET + m1 * (n - 7) + m2 * pos_preceding_word(x, n - 7); continue;
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
#pragma omp parallel for
  for (R_xlen_t i = 0; i < N; ++i) {
    if (ansp[i] != NA_INTEGER) {
      continue;
    }
    int n = length(STRING_ELT(xx, i));
    const char * x = CHAR(STRING_ELT(xx, i));
    int j = 10;
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
          j = j + 5;
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
#pragma omp parallel for
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












