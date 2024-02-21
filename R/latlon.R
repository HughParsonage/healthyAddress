

compress_latlon <- function(lat, lon, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_compress_latlon", lat, lon, nThread, PACKAGE = packageName())
}

decompress_latlon <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_decompress_latlon", x, nThread, PACKAGE = packageName())
}


