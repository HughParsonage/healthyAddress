multistate_postcodes <- function() {
  .Call("C_multistate_postcodes", NULL, PACKAGE = packageName())
}
