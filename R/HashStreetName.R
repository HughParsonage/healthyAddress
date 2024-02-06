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
#'
#'
#' @export

HashStreetName <- function(x) {
  .Call("C_HashStreetName", x, PACKAGE = packageName())
}

#' @rdname HashStreetName
#' @export
unHashStreetName <- function(x) {
  noms <- all_STREET_NAME()
  homs <- HashStreetName(noms)
  noms[fmatchp(x, homs)]
}

hash_env <- new.env()

all_STREET_NAME <- function() {
  if (is.environment(hash_env) && exists("noms", hash_env, inherits = FALSE)) {
    get0("noms", hash_env, inherits = FALSE)
  } else {
    file.qs <-
      system.file("extdata", "POSTCODE-STREET_TYPE_CODE-STREET_NAME.qs", package = packageName())

    if (!file.exists(file.qs) || file.access(file.qs, mode = 4L)) {
      stop("file.qs below not found or readable\n\t", file.qs)
    }

    DT <- qs::qread(file.qs)
    assign("noms",
           envir = hash_env,
           value = unique(.subset2(DT, "STREET_NAME")))
  }
}
