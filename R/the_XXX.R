#' Elements of addresses with THE
#' @description Some addresses contain 'THE' which is a string often at the
#' beginning of some street names.
#'
#' @noRd


get_the_XXX <- function(o = TRUE) {
  # if o == 1, the strings are returned;
  # otherwise the indices of localities that are common to those strings
  # are returned.
  .Call("C_getTHEXXX", o, PACKAGE = packageName())
}

get_difficult_postcodes <- function() {
  STREET_NAME <- POSTCODE <- NAME <- m_LOCALITY <- m_STREET <- NULL
  US <- read_ste_fst()
  US[startsWith(STREET_NAME, "THE "),
     .(POSTCODE, STREET_NAME)] |>
    unique() |>
  merge(read_locality_by_postcode(),
        by = "POSTCODE",
        allow.cartesian = TRUE) %>%
    .[startsWith(NAME, "THE ")] %>%
    .[, m_LOCALITY := match(NAME, paste("THE", get_the_XXX()), nomatch = 0L)] %>%
    .[, m_STREET := match(STREET_NAME, paste("THE", get_the_XXX()), nomatch = 0L)] %>%
    .[]
}

# These postcodes are easy -- if they are present, we can simply skip testing
# THE because no street name exists
get_easy_postcodes <- function() {
  NAME <- POSTCODE <- NULL
  problems <- get_difficult_postcodes()
  read_locality_by_postcode()[startsWith(NAME, "THE ")][POSTCODE %notin% problems$POSTCODE]
}



