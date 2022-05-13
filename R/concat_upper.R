#' @noRd
#' @return Equivalent to toupper(paste(x1, x2, x3, x4, sep ))

concat_upper <- function(x1, x2, x3 = NULL, x4 = NULL, sep = ", ") {
  .sep <- chmatch(sep, ", ", nomatch = 0L)
  ans <- .Call("Cconcat_upper", x1, x2, x3, x4, .sep, PACKAGE = "healthyAddress")
  if (is.null(ans)) {
    N <- length(x1)
    ans <- .Call("Cconcat_upper", x1, rep_len(x2, N), rep_len(x3, N), rep_len(x4, N), .sep, PACKAGE = "healthyAddress")
  }
  ans
}


