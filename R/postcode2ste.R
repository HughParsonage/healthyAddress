#' In what states do postcodes lie?
#' @description While for most postcodes, the state enclosing it
#' is easy to evaluate (e.g. most postcodes in 2000-2999 are in NSW),
#' the general case is non-trivial. In particular, some postcodes
#' straddle state borders.
#'
#' @param Postcodes An integer vector of postcodes.
#' @param result One of \code{"integer"} or \code{"character"}.
#' If \code{"character"} the abbreviated state names(s) are returned.
#'
#' @return
#' A vector, the minimal states that cover all postcodes given. For example,
#' if all postcodes lie within a single state a scalar integer/string of that
#' state is returned.
#'
#' @examples
#' vic_poa <- c(3021L, 3084L, 3013L, 3147L, 3030L,
#'              3123L, 3070L, 3004L, 3250L, 3630L)
#'
#' postcode2ste(vic_poa)
#' postcode2ste(vic_poa, result = "character")
#' postcode2ste(c(vic_poa, 2000L))
#' postcode2ste(3644L)
#'
#' @export


postcode2ste <- function(Postcodes, result = c("integer", "character")) {
  result <- match.arg(result)
  if (!is.integer(Postcodes)) {
    Postcodes <- as.integer(Postcodes)
  }
  Postcodes <- unique_Postcodes(Postcodes)
  Postcode2ste <- sys_fst("Postcode2ste")
  stopifnot(hasNames(Postcode2ste, c("POSTCODE", "ste_int")))
  ste_int <- NULL
  int_result <- Postcode2ste[.(Postcodes), ste_int]
  if (isntConstant(int_result)) {
    int_result <- unique(int_result)
  } else {
    int_result <- int_result[1]
  }
  switch(result,
         "integer" = int_result,
         "character" = ste_chars[int_result])
}


