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
#' @param integer_StreetType Should the street type be returned as an integer
#' vector?
#'
#' @param StreetHash Should \code{STREET_NAME} be returned as an integer hash.
#'
#' @export

standardize_address <- function(Address,
                                AddressLine2 = NULL,
                                return.type = c("data.table", "integer"),
                                integer_StreetType = FALSE,
                                StreetHash = FALSE) {
  return.type <- match.arg(return.type)
  integer_StreetType <- isTRUE(integer_StreetType)
  if (nany_lowercase(Address)) {

  } else {
    Address <- toupper_basic(Address)
  }

  switch(return.type,
         "data.table" = {
           if (is.null(AddressLine2)) {
             POSTCODE_ <- extract_postcode(Address)
             Numbers <- extract_flatNumberFirstLast(Address)
             StreetType <- match_StreetType(Address, m = 2L)
             StreetName <- match_StreetName(Address,
                                            StreetType,
                                            Numbers = Numbers,
                                            hash = StreetHash)
             out <- setDT(Numbers)
             out[, "POSTCODE" := POSTCODE_]
             if (is.integer(StreetName)) {
               # hash
               out[, "hSTREET_NAME" := StreetName]
             } else {
               out[, "STREET_NAME" := StreetName]
             }
             if (integer_StreetType) {
               out[, "STREET_TYPE" := .digit256(StreetType, 0L)]
             } else {
               out[, "STREET_TYPE" := .permitted_street_type_ord()[bitwAnd(StreetType, 255L)]]
             }
           } else {
             if (nany_lowercase(AddressLine2)) {
               AddressLine2 <- toupper_basic(AddressLine2)
             }
             POSTCODE_ <- extract_postcode(AddressLine2)
             Numbers <- extract_flatNumberFirstLast(Address)
             StreetType <- match_StreetType_Line1(Address, m = 2L)
             StreetName <- match_StreetName(Address, StreetType)
             out <- setDT(Numbers)

             out[, "POSTCODE" := POSTCODE_]
             out[, "STREET_NAME" := StreetName]
             out[, "STREET_TYPE" := .permitted_street_type_ord()[bitwAnd(StreetType, 255L)]]

           }
           return(out[])
         })

  # .Call("CStandardAddress", )


}


Do_standard_address <- function(x) {
  # 1.8 M addresses / s
  Ans <- .Call("C_do_standard_address", x)
  setDT(Ans)
  setnames(Ans, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST", "H0", "H1", "H2", "H3",
                  "STREET_TYPE_CODE", "POSTCODE"))
  Ans[]
}








