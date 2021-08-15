#' Find the street type within an address
#' @param address A character vector, every string an address.
#' @param m An integer. Values greater than \code{0} are for internal use and
#' encode additional data in the return value:
#'
#' \enumerate{
#'   \item An integer vector \code{y} is returned such that \code{y mod 256} gives
#'   which street code and \code{y / 256} gives the character position in address
#'   at which the street type starts.
#' }
#'

#'
#'

#'
#'
#' @return Which of \code{\link{.permitted_street_type_ord}} appears
#' in \code{address}.
#'
#' @examples
#' cds <- .permitted_street_type_ord()
#' head(cds)
#' match_StreetType("712 FLINDERS STREET MELBOURNE 3004")
#' match_StreetType("712 FLINDERS STREET MELBOURNE 3004", 1L)
#'
#' @export

match_StreetType <- function(address, m = 0L) {
  stopifnot(is.character(address), is.integer(m))
  PSTO <- .permitted_street_type_ord()
  ans <- .Call("Cmatch_StreetType", address, PSTO, m, PACKAGE = packageName())
  ans
}

match_StreetType_Line1 <- function(address, m = 2L) {
  stopifnot(is.character(address), is.integer(m))

  ans <- .Call("Cmatch_StreetType_Line1", address, m, integer(0), PACKAGE = packageName())
  ans
}







