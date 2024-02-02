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
  AUS_FULL <- NULL
  stopifnot(is.data.table(StandardAddress))
  StandardAddress[, "orig_ordering" := .I]
  states <- postcode2ste(.subset2(StandardAddress, "POSTCODE"), result = "character")
  if (length(states) == 1) {
    FF <- read_ste_fst(states)
  } else if (exists("AUS_FULL")) {
    FF <- AUS_FULL
  } else {
    FF <-
      lapply(states[match(states, ste_chars, nomatch = 0L)], function(ste) {
        ste_dt <- sys_fst(sprintf("%s_FULL_ADDRESS", ste))
      })
    FF <- rbindlist(FF, use.names = TRUE)
  }

  NUMBER_FIRST_SUFFIX <- STREET_TYPE_CODE <- STREET_TYPE <- NUMBER_SUFFIX <-
    FLAT_NUMBER <- NULL
  StandardAddress[, "STREET_TYPE_CODE" := ensure_street_type_encode(STREET_TYPE)]
  StandardAddress[, "NUMBER_FIRST_SUFFIX" := as.integer(NUMBER_SUFFIX)]
  FF[, NUMBER_FIRST_SUFFIX := as.integer(NUMBER_FIRST_SUFFIX)]
  FF[, FLAT_NUMBER := fcoalesce(FLAT_NUMBER, 0L)]
  if (!hasName(StandardAddress, "hSTREET_NAME") &&
      hasName(StandardAddress, "STREET_NAME")) {
    set(StandardAddress,
        j = "hSTREET_NAME",
        value = HashStreetName(.subset2(StandardAddress, "STREET_NAME")))
  }

  i.ADDRESS_SITE_PID <- NULL
  StandardAddress[FF,
                  "enc" := i.ADDRESS_SITE_PID,
                  on = c("POSTCODE",
                         "STREET_TYPE_CODE",
                         "hSTREET_NAME",
                         "NUMBER_FIRST",
                         "NUMBER_FIRST_SUFFIX",
                         "FLAT_NUMBER")]
}

