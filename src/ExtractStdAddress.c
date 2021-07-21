
#include "healthyAddress.h"
#include "streetcodes.h"

/*
 static const unsigned char letters[26] =
 {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
 */




static const unsigned char LETTERS[26] =
{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

static unsigned char toupper1(unsigned char x) {
  unsigned int xi = x - 'a';
  return (xi < 26) ? LETTERS[xi] : x;
}

static const char * touppers(const char * x, int len) {
  char a[len + 1];
  for (int i = 0; i < len; ++i) {
    unsigned char xi = x[i];
    a[i] = toupper1(xi);
  }
  a[len] = '\0';
  char * ans = a;
  return ans;
}

bool char_is_number(unsigned char x) {
  return x - '0' <= 9U;
}

bool char_is_LETTER(unsigned char x) {
  // assumes AZ contiguous and in order
  return x - 'A' <= 25;
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
  unsigned char x1 = x[n - 1];
  unsigned char x2 = x[n - 2];
  unsigned char x3 = x[n - 3];
  unsigned char x4 = x[n - 4];
  unsigned int d1 = x1 - '0';
  unsigned int d2 = x2 - '0';
  unsigned int d3 = x3 - '0';
  unsigned int d4 = x4 - '0';
  int is_digit = (d1 < 10) & (d2 < 10) & (d3 < 10) & (d4 < 10);
  o = d1 + 10u * d2 + 100u * d3 + 1000u * d4;
  return is_digit ? o : 0;
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
    const char * xc = touppers(CHAR(xi), len);
    int j = 0;
    int J[1] = {0};
    unsigned char xcj = xc[j];
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

#define FMT_N__ST_LOC_POA 1
#define FMT_NS_ST_LOC_POA 2

SEXP Cidentify_address_format(SEXP xx) {
  R_xlen_t N = xlength(xx);
  if (TYPEOF(xx) != STRSXP) {
    error("TYPEOF(xx) != STRSXP");
  }
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);

  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP CX = STRING_ELT(xx, i);
    int n = length(CX);
    const char * x = touppers(CHAR(CX), n);
    unsigned char x0 = (unsigned char)x[0];
    bool no_unit = x0 != 'U';
    ansp[i] = 0;
    if (has_ste_postcode(x, n)) {
      if (char_is_number(x0)) {
        ansp[i] = FMT_N__ST_LOC_POA;
      }
    }
  }
  UNPROTECT(1);
  return ans;
}

SEXP CFindLocality(SEXP xx) {
  if (TYPEOF(xx) != STRSXP) {
    error("(CFindLocality): TYPEOF(xx) != STRSXP"); // # nocov
  }
  R_xlen_t N = xlength(xx);
  int np = 0;

  SEXP Spostcode = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict Postcode = INTEGER(Spostcode);
  SEXP SState = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict State = INTEGER(SState);
  SEXP SLocality = PROTECT(allocVector(INTSXP, N)); np++;
  int * restrict Locality = INTEGER(SLocality);

  for (R_xlen_t i = 0; i < N; ++i) {
    SEXP CX = STRING_ELT(xx, i);
    int n = length(CX);
    const char * x = touppers(CHAR(CX), n);
    Postcode[i] = NA_INTEGER;
    State[i] = NA_INTEGER;
    Locality[i] = NA_INTEGER;
    if (n <= 8) {
      continue;
    }
    Postcode[i] = xpostcode_unsafe(x, n);
    State[i] = ste_as_int(x, n - 8);
    // Press backward from end
    // for each space char, see whether
    // it's plausibly a street type
    // then assume it's the locality
    // mark the position

    int j = n - 8;
    // j >= 5 because whichstreetname requires it
    unsigned char xj = x[j];
    while (j >= 5 && xj != ' ') {
      xj = x[j];
      --j;
    }
    ++j;
    int which_street_namei[2] = {0};
    whichStreetName(x, j, which_street_namei);
    while (which_street_namei[1] == 0 && j >= 5 && xj != ' ') {
      j = x[j];
      --j;
    }
    whichStreetName(x, j, which_street_namei);
    if (which_street_namei[1]) {
      Locality[i] = j;
    }
  }
  SEXP ans = PROTECT(allocVector(VECSXP, 3)); np++;
  SET_VECTOR_ELT(ans, 0, Spostcode);
  SET_VECTOR_ELT(ans, 1, SState);
  SET_VECTOR_ELT(ans, 2, SLocality);
  UNPROTECT(np);
  return ans;
}




