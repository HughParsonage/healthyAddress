#' Standard address
#'
#' @param Address A character vector, either a full address or (if \code{AddressLine2}
#' is not \code{NULL}) the first line of an Australian address.
#' @param AddressLine2 Either \code{NULL} (the default) or a character vector,
#' the same length as \code{Address} giving the second line of the Address.
#'
#' @param return.type Either \code{"data.table"} or \code{"integer"}.
#' \code{"data.table"} implies a table of columns separating the address components.
#' \code{"integer"} means an integer vector creating a bijection between the
#' address and the \code{PSMA} internal id.
#'
#' @export

standardize_address <- function(Address, AddressLine2 = NULL, return.type = c("data.table", "integer")) {
  return.type <- match.arg(return.type)
  if (nany_lowercase(Address)) {

  } else {
    Address <- toupper_basic(Address)
  }

  switch(return.type,
         "data.table" = {
           if (is.null(AddressLine2)) {
             POSTCODE <- extract_postcode(Address)
             Numbers <- extract_flatNumberFirstLast(Address)
             StreetType <- match_StreetType(Address, m = 2L)
             StreetName <- match_StreetName(Address, StreetType)
             out <- data.table(POSTCODE)
             out[, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST") := as.list(Numbers)]
             out[, "STREET_NAME" := StreetName]
             out[, "STREET_TYPE" := .permitted_street_type_ord()[bitwAnd(StreetType, 255L)]]
           } else {
             AddressLine2 <- toupper_basic(AddressLine2)
             POSTCODE <- extract_postcode(AddressLine2)
             Numbers <- extract_flatNumberFirstLast(Address)
             StreetType <- match_StreetType_Line1(Address, m = 2L)
             StreetName <- match_StreetName(Address, StreetType)
             out <- data.table(POSTCODE)
             out[, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST") := as.list(Numbers)]
             out[, "STREET_NAME" := StreetName]
             out[, "STREET_TYPE" := .permitted_street_type_ord()[bitwAnd(StreetType, 255L)]]

           }
           return(out[])
         })

  # .Call("CStandardAddress", )


}



