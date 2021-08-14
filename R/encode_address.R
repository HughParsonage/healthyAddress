#' Encode standard address
#' @description See \code{standardize_address}
#'
#' @param StandardAddress A \code{data.table} returned by
#' \code{standardize_address}.
#'
#'
#'
#'
#' @export

encode_address <- function(StandardAddress) {
  stopifnot(is.data.table(StandardAddress))
  StandardAddress[, "orig_ordering" := .I]
  states <- postcode2ste(.subset2(StandardAddress, "POSTCODE"), result = "character")
  if (length(states) == 1) {
    FF <- sys_fst(sprintf("%s_FULL_ADDRESS", states))
    setnames(FF,
             paste0(states, "_GA_INTRNL_ADDRESS_ID"),
             "STE_GA_INTRNL_ADDRESS_ID",
             skip_absent = TRUE)
    setnames(FF, names(FF), gsub(states, "STE", names(FF)))
  } else if (exists("AUS_FULL")) {
    FF <- AUS_FULL
  } else {
    FF <-
      lapply(states[match(states, ste_chars, nomatch = 0L)], function(ste) {
        ste_dt <- sys_fst(sprintf("%s_FULL_ADDRESS", ste))
        setnames(ste_dt,
                 paste0(ste, "_GA_INTRNL_ADDRESS_ID"),
                 "STE_GA_INTRNL_ADDRESS_ID",
                 skip_absent = TRUE)
      })
    FF <- rbindlist(FF, use.names = TRUE)
  }

  StandardAddress[, "STREET_TYPE_CODE" := ensure_street_type_encode(STREET_TYPE)]
  StandardAddress[, NUMBER_FIRST_SUFFIX := as.integer(NUMBER_SUFFIX)]
  FF[, NUMBER_FIRST_SUFFIX := as.integer(NUMBER_FIRST_SUFFIX)]
  FF[, FLAT_NUMBER := fcoalesce(FLAT_NUMBER, 0L)]
  if (!hasName(StandardAddress, "hSTREET_NAME")) {
    StandardAddress[, hSTREET_NAME := HashStreetName(STREET_NAME)]
  }


  # FF[StandardAddress,
  #    .(POSTCODE, STE_GA_INTRNL_ADDRESS_ID),
  #    on = .(POSTCODE,
  #           STREET_TYPE_CODE,
  #           hSTREET_NAME,
  #           NUMBER_FIRST,
  #           NUMBER_FIRST_SUFFIX,
  #           FLAT_NUMBER),
  #    nomatch = NA_integer_,
  #    mult = "first"]

  StandardAddress[FF,
                  enc := i.STE_GA_INTRNL_ADDRESS_ID,
                  on = .(POSTCODE,
                         STREET_TYPE_CODE,
                         hSTREET_NAME,
                         NUMBER_FIRST,
                         NUMBER_FIRST_SUFFIX,
                         FLAT_NUMBER)]
}

.encode_address_per_state <- function(StandardAddress, ste = NULL) {
  if (is.null(Postcodek)) {

  }
}


