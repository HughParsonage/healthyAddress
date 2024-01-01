#' Elements of addresses with THE
#' @description Some addresses contain 'THE' which is a string often at the
#' beginning of some street names.
#'

get_the_XXX <- function(o = TRUE) {
  # if o == 1, the string are returned;
  # otherwise the indices of localities that are common to those strings
  # are returned.
  .Call("C_getTHEXXX", o, PACKAGE = packageName())
}
