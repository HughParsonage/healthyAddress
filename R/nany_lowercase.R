#' Uppercase character vectors
#' @description Ensures all elements of a character vector are uppercase;
#' no lowercase characters.
#' @param x A character vector, of ASCII elements.
#'
#' @return
#' \describe{
#'  \item{\code{nany_lowercase}}{\code{FALSE} is any char in \code{x} is a lowercase letter.}
#' }
#'
#' @examples
#' nany_lowercase("ABC")
#' nany_lowercase("ABC 123 /--")
#' nany_lowercase("ABC 123 /-- z")
#'
#' @export


nany_lowercase <- function(x) {
  .Call("C_noLC", x, PACKAGE = packageName())
}