#' Find the street type within an address
#' @param address A character vector, every string an address.
#'
#'
#' @return A list of two elements. The first element are the indices of
#' street type in \code{.permitted_street_type_ord()} that is found in the
#' address. The second element are the corresponding string positions of
#' the street so identified.
#'
#' @examples
#' cds <- .permitted_street_type_ord()
#' head(cds)
#' match_StreetType("712 FLINDERS STREET MELBOURNE 3004")
#' #                 012345678901234
#' match_StreetType("712 FLINDERS ST MELBOURNE 3004")
#'
#' @export

match_StreetType <- function(address) {
  stopifnot(is.character(address))
  Ans <- match_StreetType_trie(ensure_uppercase(address))
}

match_StreetType_Line1 <- function(address, m = 2L) {
  stopifnot(is.character(address), is.integer(m))

  ans <- .Call("Cmatch_StreetType_Line1", address, m, integer(0), PACKAGE = packageName())
  ans
}

match_StreetType_trie <- function(x) {
  .Call("C_trie_streetType", x, PACKAGE = packageName())
}





