#' @name toupper_basic
#' @title Uppercase
#' @param x A character vector
#' @return The same as \code{toupper(x)} for ASCII entries. For implementation
#' reasons, strings wider than 32767 characters (bytes) will be ignored.
#' @export
toupper_basic <- function(x) {
  stopifnot(is.character(x))
  .Call("CToUpperBasic", x, PACKAGE = packageName())
}


