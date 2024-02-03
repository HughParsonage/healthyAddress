check_address_input <- function(x, m = 0L, nThread = getOption("healthyAddress.nThread", 1L)) {
  .Call("C_check_address_input", x, m, nThread, PACKAGE = packageName())
}
