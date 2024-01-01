#' Extract the postcode from the suffix of a string
#'
#' @param x A character vector.
#'
#' @return An integer vector the same length as \code{x}, giving the
#' postcode as it appears in the last 3 or 4 characters in each
#' string. Returns \code{NA_integer_} for other strings.
#'
#' There is no guarantee made that the postcode is a real postcode.
#'
#' @examples
#' extract_postcode("3000")
#' extract_postcode("Melbourne Vic 3000")
#'
#' @export

extract_postcode <- function(x) {
  .Call("CExtractPostcode", x, PACKAGE = packageName())
}

the__ <- function(x, postcode = NULL) {
  .Call("C_do_the_xxx", x, if (is.null(postcode)) extract_postcode(x) else postcode, PACKAGE = packageName())
}


