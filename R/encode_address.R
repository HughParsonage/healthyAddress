#' Encode standard address
#' @description See \code{standardize_address}
#'
#'
#'
#'
#' @export

encode_address <- function(StandardAddress) {
  FF <- get_FullNamedAddressData()
  StandardAddress[, "orig_ordering" := .I]
  FF[StandardAddress,
     on = .(POSTCODE, STREET_TYPE_CODE = STREET_TYPE, STREET_NAME, NUMBER_FIRST, FLAT_NUMBER),
     nomatch = NA_integer_,
     mult = "first"]
}


