#include "healthyAddress.h"

const unsigned int PACK_ST_POA[256] =
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   526336, 0, 32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100696064, 2064671906, -2088566781,
   -1608757104, -2136997872, -1901943028, -536313852, 35711488, 11798016, 159872,
   -1845387263, 139271, 0, 687865888, 1082137600, 3235840, 270533160, -1610605245,
   4751600, 4202496, 35880960, 0, 19070976, -1526726656, 1759523392, 1027, 8192,
   16777218, 0, 0, 0, 704643072, -205891568, -306115552, -1872704145, -1840313057,
   367769594, 1158658606, 155641915, 256, 1097728, 262152, 216009472, 17309700,
   2097408, 524312, 11829266, 536942592, 1610612816, 4, 0, 8208, 268435456, 131136,
   147456, 1108417184, -1135591423, -2147417590, 1073742344, 0, -1493041088,
   589948, 201327424, 1073741824, 0, 4096, 80, 0, 131072, 50855936, 4, 8388608,
   0, 536870912, 0, 0, 0, 0, 524288, 0, 1058816, 0, 0, 1073758720, 268435456,
   67108870, 32, 0, 2, 0, 32, 0, 0, 0, 1416937600, 236638464, 2030547936,
   188482004, -2147450800, 1574518, 201850880, 134217728, -2134900670, 1536, 0,
   805346432, 0, 16777504, 1055744, 268435456, 65536, 2097152, -2147452460,
   1073741856, 0, 0, 67108864, 0, 0, 0, 0, 0, 0, 0, 0, 709132288, 17575774,
   135393474, -448790528, 0, 495461632, 1073741824, 153616386, 0, -1610608256,
   34078720, 0, 0, 536870912, 131072, 0, 268435456, 10, 34, 0, 0, 0, 0, 4718592,
   0, 0, 0, 0, 0, 0, 0, -1744830464, 65601, 0, 0, 32768, 0, 2097152, 53248,
   67239936, 4096, 16786560, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};


unsigned int count_bits(unsigned int v) {
  v = v - ((v >> 1U) & 0x55555555);                    // reuse input as temporary
  v = (v & 0x33333333) + ((v >> 2U) & 0x33333333);     // temp
  return (((v + (v >> 4U)) & 0xF0F0F0F) * 0x1010101) >> 24U; // count
}

bool has_saint_name(unsigned int poa, unsigned char * res) {
  if ((poa - 1u) > SUP_POSTCODE_) {
    return 0;
  }
  if (res) {
    return res[poa];
  }
  --poa;
  unsigned int poa_s = (poa >> 5);
  unsigned int poa_m = poa & 31;
  unsigned int pack = PACK_ST_POA[poa_s];
  bool pack32[32] = {0};
  for (int k = 0, j = 0; k < 32; ++k, pack >>= 1) {
    pack32[j++] = pack & 1;
  }
  return pack32[poa_m];
}

static void memoize_saint_res(unsigned char * res) {
  memset(res, 0, 8192);
  for (int p = 812; p <= 7321; ++p) {
    res[p] = has_saint_name(p, NULL);
  }
}

SEXP C_has_saint_name(SEXP x, SEXP mm) {
  if (!isInteger(x) || !isInteger(mm)) {
    return R_NilValue;
  }
  R_xlen_t N = xlength(x);
  const int * xp = INTEGER(x);
  const int m = asInteger(mm);
  SEXP ans = PROTECT(allocVector(LGLSXP, N));
  int * restrict ansp = LOGICAL(ans);
  unsigned char * res = m ? malloc(sizeof(char) * 8192) : NULL;
  if (m) {
    memset(res, 0, 8192);
    for (int p = 812; p <= 7321; ++p) {
      res[p] = has_saint_name(p, NULL);
    }
  }
  for (R_xlen_t i = 0; i < N; ++i) {
    ansp[i] = has_saint_name(xp[i], res);
  }
  free(res);
  UNPROTECT(1);
  return ans;
}


