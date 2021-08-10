


NumberSuffix2Raw <- function(x) {
  .Call("C_NumberSuffix2Raw", x, PACKAGE = packageName())
}
