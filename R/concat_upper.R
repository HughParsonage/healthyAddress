#' @noRd
#' @return Equivalent to toupper(paste0(x1, x2, x3, x4))

concat_upper <- function(x1, x2, x3 = NULL, x4 = NULL) {
  .Call("Cconcat_upper", x1, x2, x3, x4, PACKAGE = "healthyAddress")
}
