

max_nchar <- function(x) {
  .Call("C_max_nchar", x, PACKAGE = packageName())
}

