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
  } else if (exists("AUS_FULL")) {
    FF <- AUS_FULL
  } else {
    FF <-
      lapply(states[match(states, ste_chars, nomatch = 0L)], function(ste) {
        ste_dt <- sys_fst(sprintf("%s_FULL_ADDRESS", ste))
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

  StandardAddress[FF,
                  enc := i.ADDRESS_SITE_PID,
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


