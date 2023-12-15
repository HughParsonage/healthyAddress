





.MAX_uN_STCDs <- function() {
  .Call("MAX_uN_STCDs", NULL, PACKAGE = packageName())
}






.set_cols_first <- function(DT, cols) {
  return(setcolorder(DT, c(intersect(cols, names(DT)), setdiff(names(DT), cols))))
}








FindSentence <- function(x, word1, word2) {
  .Call("CFindSentence", x, word1, word2, PACKAGE = packageName())
}


test_WordData <- function(x, r = 0L) {
  stopifnot(is.character(x), is.integer(r))
  .Call("Ctest_WordData", x, r)
}


zMatchStreetName <- function(x) {
  .Call("ZMatchStreetName", x)
}


