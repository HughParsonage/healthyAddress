#' Hash a street name quickly and
#' @param x A character vector of uppercase street names (without the street type).
#'
#' @examples
#' HashStreetName("FLINDERS")
#'
#' @export

HashStreetName <- function(x) {
  .Call("C_HashStreetName", x, PACKAGE = packageName())
}
