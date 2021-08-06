#' Unique postcodes of
#' @param x An integer vector of postcodes.
#'
#' @return A (sorted) integer vector of the unique, non-NA values in \code{x}.
#' @export

unique_Postcodes <- function(x) {
  .Call("C_uniquePostcodes", x, PACKAGE = packageName())
}


