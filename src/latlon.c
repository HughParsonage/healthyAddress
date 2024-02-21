#include "healthyAddress.h"

// Observed from PSMA
#define MIN_AUS_LAT -43.583
#define MAX_AUS_LAT -9.229
#define MIN_AUS_LON 96.821
#define MAX_AUS_LON 168.0

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


