#' @noRd
#' @return Equivalent to toupper(paste(x1, x2, x3, x4, sep ))

concat_upper <- function(x1, x2, x3 = NULL, x4 = NULL, sep = ", ") {
  .sep <- chmatch(sep, ", ", nomatch = 0L)
  .Call("Cconcat_upper", x1, x2, x3, x4, .sep, PACKAGE = "healthyAddress")
}
