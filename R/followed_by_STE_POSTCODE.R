followed_by_STE_POSTCODE <- function(w_i, x) {
  stopifnot(is.integer(w_i), is.character(x))
  .Call("Cfollowed_by_STE_POSTCODE", w_i, x, PACKAGE = packageName())
}
