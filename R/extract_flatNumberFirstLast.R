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
  setnames(ans, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST"))
  ans[]
}

