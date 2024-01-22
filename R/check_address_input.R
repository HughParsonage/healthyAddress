check_address_input <- function(x) {
  .Call("C_check_address_input", x, PACKAGE = packageName())
}
