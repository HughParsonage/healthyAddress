#' Hash a street name quickly and
#'
#'
#' @noRd

HashStreetName <- function(x) {
  .Call("C_HashStreetName", x, PACKAGE = packageName())
}
