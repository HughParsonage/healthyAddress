#' Find word within a sentence
#' @param x A character vector of uppercase sentences.
#' @param tbl A table of words. Long vectors are not permitted.
#'
#' @return An integer vector the same length as \code{x}, where the
#' \code{i}-th entry
#' is the integer position of the first word in \code{tbl}
#' detected in \code{x[i]}. Non-matches return \code{NA}. Words
#' are strings of uppercase separated by spaces.
#'
#' @export
match_word <- function(x, tbl) {
  stopifnot(is.character(x), is.character(tbl))
  .Call("Cmatch_word", x, tbl, PACKAGE = packageName())
}


has_word <- function(x, m = 0L) {
  .Call("C_has_word", x, m, PACKAGE = packageName())
}
