#' Match Street Name
#'
#' @param address A character vector of addresses.
#' @param StreetMatch2 The integer vector result of \code{match_StreetType(address, m = 2L)}.
#' If \code{NULL} the vector is evaluated internally.
#'
#' @param Numbers If not \code{NULL}, then a list from \code{extract_flatNumberFirstLast}.
#'
#' @param hash Whether to hash the result as an integer vector.
#' @export

match_StreetName <- function(address, StreetMatch2 = NULL, Numbers = NULL, hash = FALSE) {
  if (is.null(StreetMatch2)) {
    StreetMatch2 <- match_StreetType(address, m = 2L)
  }
  jPos <- integer(0)
  if (!is.null(Numbers) && hasName(Numbers, "j_POSITION")) {
    jPos <- .subset2(Numbers, "j_POSITION")
  }

  .Call("Cmatch_StreetName",
        address,
        StreetMatch2,
        jPos,
        isTRUE(hash),
        PACKAGE = packageName());
}
