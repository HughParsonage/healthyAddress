


anyComma <- function(x, o = 0L) {
  .Call("C_anyComma", x, o, PACKAGE = packageName())
}

contains_big4 <- function(x) {
  .Call("C_contains_BIG4", x, PACKAGE = packageName())
}
