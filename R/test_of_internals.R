
test_digit_of_from <- function(x, j, b) {
  .Call("Ctest_digit_of_from", x, j, b, PACKAGE = packageName())
}

