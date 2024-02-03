#' Uppercase character vectors
#' @description Ensures all elements of a character vector are uppercase;
#' no lowercase characters.
#' @param x A character vector, of ASCII elements.
#' @param nThread Number of threads to use.
#'
#' @return
#' \describe{
#'  \item{\code{nany_lowercase}}{\code{FALSE} if any char in \code{x} is a lowercase letter.}
#' }
#'
#' @examples
#' nany_lowercase("ABC")
#' nany_lowercase("ABC 123 /--")
#' nany_lowercase("ABC 123 /-- z")
#'
#' @export


nany_lowercase <- function(x, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_noLC", x, nThread, PACKAGE = packageName())
}

ensure_uppercase <- function(x) {
  if (nany_lowercase(x)) {
    return(x)
  }
  toupper_basic(x)
}


