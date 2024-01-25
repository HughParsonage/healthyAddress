check_address_input <- function(x, m = 0L) {
  .Call("C_check_address_input", x, m, PACKAGE = packageName())
}
