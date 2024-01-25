
n_words <- function(x) {
  .Call("C_test_n_words", x, PACKAGE = packageName())
}
