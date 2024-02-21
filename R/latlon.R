

compress_latlon <- function(lat, lon, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_compress_latlon", lat, lon, nThread, PACKAGE = packageName())
}

decompress_latlon <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_decompress_latlon", x, nThread, PACKAGE = packageName())
}

compress_latlon_general <- function(lat, lon, nThread = getOption("healthyAddress.nThread", 1L)) {
  minmaxLat <- minmax(lat)
  minmaxLon <- minmax(lon)
  if (anyNA(minmaxLat) || anyNA(minmaxLon)) {
    stop("lat or lon contain nas.")
  }
  ans <- .Call("C_compress_latlon_general", lat, lon, minmaxLat, minmaxLon, nThread, PACKAGE = packageName())
  setattr(ans, "minmaxLat", minmaxLat)
  setattr(ans, "minmaxLon", minmaxLon)
  ans
}

decompress_latlon_general <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  stopifnot(is.integer(x))
  minmaxLat <- attr(x, "minmaxLat")
  minmaxLon <- attr(x, "minmaxLon")
  .Call("C_decompress_latlon_general", x, minmaxLat, minmaxLon, nThread, PACKAGE = packageName())
}
