#' Hash a street name quickly and accurately
#' @param x A character vector of uppercase street names (without the street type).
#'
#' @examples
#' HashStreetName("FLINDERS")
#'
#' @export

HashStreetName <- function(x) {
  .Call("C_HashStreetName", x, PACKAGE = packageName())
}

unHashStreetName <- function(x) {
  noms <- .subset2(read_ste_fst(columns = "STREET_NAME"), 1L)
  homs <- HashStreetName(noms)
  noms[fmatchp(x, homs)]
}
