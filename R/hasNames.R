
# Returns TRUE or FALSE (only) and accepts either strings or
# character vectors in nom1 and ...
hasNames <- function(x, nom1, ...) {
  if (is.null(names(x))) {
    return(FALSE)
  }
  if (missing(..1)) {
    return(all(hasName(x, nom1)))
  }
  hasNames(x, nom1) && hasNames(x, ...)
}

