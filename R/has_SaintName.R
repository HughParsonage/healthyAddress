

has_SaintName <- function(postcode, m = 0L) {
  # TRUE or FALSE depending on whether there is a 'ST < >' street name in that postcode
  .Call("C_has_saint_name", postcode, m, PACKAGE = packageName())
}
