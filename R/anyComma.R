


anyComma <- function(x, o = 0L) {
  .Call("C_anyComma", x, o, PACKAGE = packageName())
}
