#include "healthyAddress.h"

// Observed from PSMA
#define MIN_AUS_LAT -43.583
#define MAX_AUS_LAT -9.229
#define MIN_AUS_LON 96.821
#define MAX_AUS_LON 168.0

// excluding overseas territories gives us quite more lon precision
// note that this excludes lord howe island
#define C_BYRON_LON 153.64
#define STEEP_P_LON 113.369

#define COCOS_MIN_LON 96.82
#define COCOS_MAX_LON 96.9
#define COCOS_MIN_LAT -12.21
#define COCOS_MAX_LAT -12.11
#define XMAS__MIN_LON 105.62
#define XMAS__MAX_LON 105.71
#define XMAS__MIN_LAT -10.49
#define XMAS__MAX_LAT -10.41
#define LHI___MIN_LAT -31.56
#define LHI___MAX_LAT -35.50
#define LHI___MIN_LON 159.05
#define LHI___MAX_LON 159.09
#define NFOLK_MIN_LAT -29.07
#define NFOLK_MAX_LAT -28.98
#define NFOLK_MIN_LON 167.92
#define NFOLK_MAX_LON 168.0


#define LATLON_LHI 1
#define LATLON_NFK 2
#define LATLON_XMA 3
#define LATLON_CCO 4

int status_latlon(double lat, double lon, bool strict) {
  if (ISNAN(lat) || ISNAN(lon)) {
    return -1;
  }
  if (lat > MAX_AUS_LAT || lat < MIN_AUS_LAT) {
    return -2;
  }
  if (lon > STEEP_P_LON && lon < C_BYRON_LON) {
    return 0; // mainland, the latitudes are assumed to be correct
  }
  return 1;
}

// returns the offshore group of the address, 0 for mainland
int isOffshore(double lat, double lon) {
  if (lon > STEEP_P_LON && lon < C_BYRON_LON) {
    return 0; // mainland, the latitudes are assumed to be correct
  }
  int loni = lon;
  if (loni < 113) {
    if (loni > 100) {
      return LATLON_XMA;
    } else {
      return LATLON_CCO;
    }
  }
  if (loni == 159) {
    return LATLON_LHI;
  }
  return LATLON_NFK;
}

// Compress Australian lat lon to a single 32-bit integer
uint32_t compress_latlon(double lat, double lon) {
  // Normalize latitude and longitude to a 0-1 scale
  double normalized_lat = (lat - MIN_AUS_LAT) / (MAX_AUS_LAT - MIN_AUS_LAT);
  double normalized_lon = (lon - MIN_AUS_LON) / (MAX_AUS_LON - MIN_AUS_LON);

  // Scale normalized values to 16-bit range
  uint16_t lat_16bit = (uint16_t)(normalized_lat * 65535);
  uint16_t lon_16bit = (uint16_t)(normalized_lon * 65535);

  // Combine into a single 32-bit integer
  uint32_t compressed = (lat_16bit << 16) | lon_16bit;

  return compressed;
}

void decompress_latlon(uint32_t compressed, double *lat, double *lon) {
  // Extract 16-bit values for latitude and longitude
  uint16_t lat_16bit = (compressed >> 16) & 0xFFFF;
  uint16_t lon_16bit = compressed & 0xFFFF;

  // Normalize to 0-1 scale
  double normalized_lat = lat_16bit / 65535.0;
  double normalized_lon = lon_16bit / 65535.0;

  // Map back to original latitude and longitude ranges
  *lat = MIN_AUS_LAT + (normalized_lat * (MAX_AUS_LAT - MIN_AUS_LAT));
  *lon = MIN_AUS_LON + (normalized_lon * (MAX_AUS_LON - MIN_AUS_LON));
}

uint32_t compress_latlon_mainland(double lat, double lon) {
  // Normalize latitude and longitude to a 0-1 scale
  double normalized_lat = (lat - MIN_AUS_LAT) / (MAX_AUS_LAT - MIN_AUS_LAT);
  double normalized_lon = (lon - STEEP_P_LON) / (C_BYRON_LON - STEEP_P_LON);

  // Scale normalized values to 16-bit range
  uint16_t lat_16bit = (uint16_t)(normalized_lat * 65535);
  uint16_t lon_16bit = (uint16_t)(normalized_lon * 65535);

  // Combine into a single 32-bit integer
  uint32_t compressed = (lat_16bit << 16) | lon_16bit;

  return compressed;
}

uint32_t compress_latlon_arbitrary(double lat, double lon, const double latr[2], const double lonr[2]) {
  // Normalize latitude and longitude to a 0-1 scale
  double normalized_lat = (lat - latr[0]) / (latr[1] - latr[0]);
  double normalized_lon = (lon - lonr[0]) / (lonr[1] - lonr[0]);

  // Scale normalized values to 16-bit range
  uint16_t lat_16bit = (uint16_t)(normalized_lat * 65535);
  uint16_t lon_16bit = (uint16_t)(normalized_lon * 65535);

  // Combine into a single 32-bit integer
  uint32_t compressed = (lat_16bit << 16) | lon_16bit;

  return compressed;
}

SEXP C_compress_latlon(SEXP Lat, SEXP Lon, SEXP nthreads) {
  verifyEquiDouble(Lat, "lat", Lon, "lon");
  const double * lat = REAL(Lat);
  const double * lon = REAL(Lon);
  R_xlen_t N = xlength(Lat);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  FORLOOP({
    ansp[i] = compress_latlon(lat[i], lon[i]);
  })
  UNPROTECT(1);
  return ans;
}

SEXP C_decompress_latlon(SEXP x, SEXP nthreads) {
  if (!isInteger(x)) {
    error("`x` was type '%s' but must be type integer.", type2char(TYPEOF(x)));
  }
  R_xlen_t N = xlength(x);
  const int * xp = INTEGER(x);
  SEXP Lat = PROTECT(allocVector(REALSXP, N));
  SEXP Lon = PROTECT(allocVector(REALSXP, N));
  double * restrict lat = REAL(Lat);
  double * restrict lon = REAL(Lon);
  FORLOOP({
    decompress_latlon(xp[i], &lat[i], &lon[i]);
  })

  SEXP ans = PROTECT(allocVector(VECSXP, 2));
  SET_VECTOR_ELT(ans, 0, Lat);
  SET_VECTOR_ELT(ans, 1, Lon);
  UNPROTECT(3);
  return ans;
}

SEXP C_compress_latlon_general(SEXP Lat, SEXP Lon, SEXP minmaxLat, SEXP minmaxLon, SEXP nthreads) {
  verifyEquiDouble(Lat, "lat", Lon, "lon");
  const double * lat = REAL(Lat);
  const double * lon = REAL(Lon);
  if (xlength(minmaxLat) != 2 || xlength(minmaxLon) != 2) {
    error("(C_compress_latlon_general internal error)minmaxLat or minmaxLon not length-2.");
  }
  const double * minmax_lat = REAL(minmaxLat);
  const double * minmax_lon = REAL(minmaxLon);
  R_xlen_t N = xlength(Lat);
  SEXP ans = PROTECT(allocVector(INTSXP, N));
  int * restrict ansp = INTEGER(ans);
  FORLOOP({
    ansp[i] = compress_latlon_arbitrary(lat[i], lon[i], minmax_lat, minmax_lon);
  })
  UNPROTECT(1);
  return ans;
}

