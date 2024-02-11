#' Unique postcodes of
#' @param x An integer vector of postcodes.
#' @param strict (logical, default: \code{TRUE}) If \code{TRUE}, only
#' postcodes (at time of package development) with actual addresses are returned.
#' Otherwise, any postcode in the range 1:8192 are returned.
#'
#' @return
#' \describe{
#' \item{\code{unique_Postcodes}}{A (sorted) integer vector of the unique, non-NA values in \code{x}.}
#' \item{\code{uniqueN_Postcodes}}{The number of unique postcodes.}
#' }
#' @export

unique_Postcodes <- function(x, strict = TRUE) {
  .Call("C_uniquePostcodes", x, strict, FALSE, PACKAGE = packageName())
}

#' @rdname unique_Postcodes
#' @export
uniqueN_Postcodes <- function(x, strict = TRUE) {
  .Call("C_uniquePostcodes", x, strict, TRUE, PACKAGE = packageName())
}

get_N_POSTCODES <- function() {
  .Call("C_N_POSTCODES", NULL, PACKAGE = packageName())
}

get_MAX_POSTCODE <- function() {
  .Call("C_MAX_POSTCODE", NULL, PACKAGE = packageName())
}


