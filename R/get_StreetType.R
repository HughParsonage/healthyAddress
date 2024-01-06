get_StreetType <- function(x) {
  stopifnot(is.integer(x))
  .Call("C_get_StreetType", x, PACKAGE = packageName())
}
get_oZTC <- function() {
  .Call("C_get_oZTC", 0L, PACKAGE = packageName())
}

get_StreetCode <- function(x) {
  .Call("C_get_StreetCode", x, PACKAGE = packageName())
}

static_assert <- function() {
  .Call("C_StaticAssert", 0L, PACKAGE = "healthyAddress")
}

do_oZTC <- function() {
  DT <- data.table(a = get_StreetType(0:273),
                   m = get_StreetCode(0:273))
  DT[, cat(strwrap(toString(order(m) - 1)), sep = "\n")]
}
