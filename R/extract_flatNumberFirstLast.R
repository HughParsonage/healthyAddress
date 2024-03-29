#' Extract the flat number, number first/last from an address
#'
#' @param address A character vector from which the numbers are to be extracted.
#'
#' @return A \code{data.table} of three components: the flat number,
#' the number first, and number last.
#'
#' @export

extract_flatNumberFirstLast <- function(address) {
  ans <- .Call("C_NumberFirstLast", address, PACKAGE = packageName())
  setDT(ans)
  setnames(ans, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST", "j_POSITION", "NUMBER_SUFFIX"))
  ans[]
}

xnumbers <- function(x) {
  ans <- .Call("Cxnumber", x)
}

xnumber128 <- function(x) {
  .Call("Cxnumber128", x, PACKAGE = packageName())
}

uint128_not_supported <- function() {
  .Call("C_uint128_not_supported", NULL, PACKAGE = packageName())
}

x_FlatFirstLast <- function(x) {
  stopifnot(is.character(x))
  .Call("C_xFlatFirstLast", x, PACKAGE = packageName())
}
