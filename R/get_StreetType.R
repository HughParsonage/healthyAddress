get_StreetType <- function(x) {
  stopifnot(is.integer(x))
  .Call("C_get_StreetType", x, PACKAGE = packageName())
}
get_oZTC <- function() {
  .Call("C_get_oZTC", 0L, PACKAGE = packageName())
}

static_assert <- function() {
  .Call("C_StaticAssert", 0L, PACKAGE = "healthyAddress")
}
