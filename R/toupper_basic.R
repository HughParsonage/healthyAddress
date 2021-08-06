
#' @name toupper_basic
#' @title Uppercase
#' @param x A character vector
#' @export
toupper_basic <- function(x) {
  stopifnot(is.character(x))
  .Call("CToUpperBasic", x, PACKAGE = packageName())
}

