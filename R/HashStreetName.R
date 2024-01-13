#' Hash a street name quickly and accurately
#' @param x A character vector of uppercase street names (without the street type).
#'
#' @return
#' For \code{HashStreetName}, an integer vector the same length as \code{x},
#' a hash of the input; for \code{unHashStreetName} the inverse operation.
#'
#' If the original \code{x} does not contain a recognized street name, the
#' result of \code{unHashStreetName} will be \code{NA}.
#'
#' @examples
#' HashStreetName("FLINDERS")
#' # HashStreetName("FLINDERS") |> unHashStreetName()
#'
#'
#' @export

HashStreetName <- function(x) {
  .Call("C_HashStreetName", x, PACKAGE = packageName())
}

#' @rdname HashStreetName
#' @export
unHashStreetName <- function(x) {
  noms <-
    if (is.environment(hash_env) && exists("noms", hash_env, inherits = FALSE)) {
      get0("noms", hash_env, inherits = FALSE)
    } else {
      assign("noms",
             envir = hash_env,
             value = unique(.subset2(read_ste_fst(columns = "STREET_NAME"), 1L)))
    }
  homs <- HashStreetName(noms)
  noms[fmatch(x, homs)]
}

hash_env <- new.env()
