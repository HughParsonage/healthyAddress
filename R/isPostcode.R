
isPostcode <- function(x) {
  if (is.numeric(x)) {
    return(.Call("C_isPostcode", as.integer(x), PACKAGE = packageName()))
  }
  stop("x not numeric")
}
