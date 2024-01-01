#' Elements of addresses with THE
#' @description Some addresses contain 'THE' which is a string often at the
#' beginning of some street names.
#'

get_the_XXX <- function(o = TRUE) {
  # if o == 1, the string are returned;
  # otherwise the indices of localities that are common to those strings
  # are returned.
  .Call("C_getTHEXXX", o, PACKAGE = packageName())
}

get_difficult_postcodes <- function() {
  US <- read_ste_fst()
  merge(read_locality_by_postcode(),
        US[startsWith(STREET_NAME, "THE "),
           .(POSTCODE, STREET_NAME)] |>
          unique(),
        by = "POSTCODE",
        allow.cartesian = TRUE) %>%
    .[startsWith(NAME, "THE ")] %>%
    .[, m_LOCALITY := match(NAME, paste("THE", get_the_XXX()), nomatch = 0L)] %>%
    .[, m_STREET := match(STREET_NAME, paste("THE", get_the_XXX()), nomatch = 0L)] %>%
    .[]
}



