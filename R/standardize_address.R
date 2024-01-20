#' Standard address
#'
#' @param Address A character vector, either a full address or (if \code{AddressLine2}
#' is not \code{NULL}) the first line of an Australian address.
#' @param AddressLine2 Either \code{NULL} (the default) or a character vector,
#' the same length as \code{Address} giving the second line of the Address.
#'
#' @param Line1,Line2,Postcode For addresses split by line. \code{Line1} is
#' assumed to end with the street type. The second line is only used to determine
#' \code{Postcode}, and then only if it is \code{NULL}, the default.
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
#' @param KeepStreetName Should an additional character vector be included in
#' the result of the street name?
#'
#' @return A \code{data.table} containing columns indicating the components of the standard address,
#' including \code{H0} which is the \code{\link{HashStreetName}} of the street name.
#'
#' @details
#' By convention observed in the PSMA, street names such as 'THE ESPLANADE' have
#' a street name of 'THE ESPLANADE' and an absent street type code.
#'
#'
#' @export

standardize_address <- function(Address,
                                AddressLine2 = NULL,
                                return.type = c("data.table", "integer"),
                                integer_StreetType = FALSE,
                                StreetHash = FALSE) {
  return.type <- match.arg(return.type)
  integer_StreetType <- isTRUE(integer_StreetType)
  StreetHash <- isTRUE(StreetHash)
  Ans <-
    if (is.null(AddressLine2)) {
      standard_address2(Address)
    } else {
      standard_address3(Address,
                        AddressLine2,
                        Postcode = extract_postcode(AddressLine2),
                        KeepStreetName = !StreetHash)
    }

  if (!integer_StreetType) {
    STREET_TYPE_CODE <- NULL
    Ans[, "STREET_TYPE" := .permitted_street_type_ord()[STREET_TYPE_CODE]]
  }
  if (!StreetHash && hasName(Ans, "H0")) {
    H0 <- NULL
    Ans[, "STREET_NAME" := unHashStreetName(H0)]
  }


}

#' @rdname standardize_address
#' @export
standard_address2 <- function(Address) {
  if (!nany_lowercase(Address)) {
    Address <- toupper_basic(Address)
  }
  # 1.8 M addresses / s
  Ans <- .Call("C_do_standard_address", Address)
  setDT(Ans)
  setnames(Ans, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST",
                  "NUMBER_SUFFIX",
                  "H0",
                  "STREET_TYPE_CODE", "POSTCODE"))
  Ans[]
}

#' @rdname standardize_address
#' @export
standard_address3 <- function(Line1, Line2, Postcode = NULL, KeepStreetName = FALSE) {
  stopifnot(is.character(Line1),
            is.character(Line2))
  Line1 <- ensure_uppercase(Line1)
  if (is.null(Postcode)) {
    Postcode <- extract_postcode(Line2)
  }
  Ans <- .Call("C_do_standard_address3", Line1, Line2, Postcode, KeepStreetName, PACKAGE = packageName())
  setDT(Ans)
  setnames(Ans, c("FLAT_NUMBER",
                  "NUMBER_FIRST",
                  "NUMBER_LAST",
                  "NUMBER_SUFFIX",
                  "H0",
                  "STREET_TYPE_CODE",
                  if (isTRUE(KeepStreetName)) "STREET_NAME"))
  set(Ans, j = "POSTCODE", value = Postcode)
  Ans[]
}

standard_address_postcode_trie <- function(x) {
  .Call("C_standard_address_postcode_trie", x, PACKAGE = packageName())
}


test_C_test_ALPHABET_ENC <- function(x) {
  .Call("C_test_ALPHABET_ENC", x, PACKAGE = packageName())
}






