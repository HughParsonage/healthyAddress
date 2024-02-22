#' Compress latitude and longitude to a 32-bit integer
#' @description Although lat and lon are represented by doubles, this is usually
#' slightly wasteful. This function allows you to represent coordinates as single
#' integer, vastly reducing memory footprint.
#' @param lat,lon Coordinates to compress.
#' @param nThread Number of threads to use.
#' @param x An integer vector formed by one of the compression functions.
#'
#' @return
#' The `_general` version of the compression/decompression use the observed
#' range of the latitude and longitude to form a \eqn{2^16} grid, while the
#' bare versions use the known limits of Australian address coordinates
#' (including the overseas territories). Since, in the latter, the grid
#' will be much less fine, you should expect greater loss of information,
#' possibly exceeding 100 metres.
#'
#'
#' \describe{
#' \item{\code{compress_latlon}}{An integer vector.}
#' \item{\code{decompress_latlon}}{The original \code{lat,lon}, with some information loss}
#' \item{\code{compress_latlon_general}}{An integer vector, with attributes `minmaxLat` and `minmaxLon`.}
#' \item{\code{decompress_latlon_general}}{The original \code{lat,lon}, with some information loss.}
#' }
#'
#' @export

compress_latlon <- function(lat, lon, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_compress_latlon", lat, lon, nThread, PACKAGE = packageName())
}

#' @rdname compress_latlon
#' @export
decompress_latlon <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_decompress_latlon", x, nThread, PACKAGE = packageName())
}

#' @rdname compress_latlon
#' @export
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

#' @rdname compress_latlon
#' @export
decompress_latlon_general <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  stopifnot(is.integer(x))
  minmaxLat <- attr(x, "minmaxLat")
  minmaxLon <- attr(x, "minmaxLon")
  .Call("C_decompress_latlon_general", x, minmaxLat, minmaxLon, nThread, PACKAGE = packageName())
}
