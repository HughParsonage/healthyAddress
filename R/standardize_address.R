#' Standard address
#'
#' @description Standardize an address from a free text expression into its
#' components as used in the PSMA (formerly, "Public Sector for Mapping Agencies")
#' database.
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
#' @param hash_StreetName Should \code{STREET_NAME} be returned as an integer hash,
#' as in \code{\link{HashStreetName}}?
#' @param KeepStreetName Should an additional character vector be included in
#' the result of the street name?
#'
#' @param check An integer, whether the inputs should be checked for possibly
#' invalid addresses or addresses that may not be parsed correctly.
#'
#' @return A \code{data.table} containing columns indicating the components of the standard address:
#'
#' \describe{
#' \item{\code{FLAT_NUMBER}}{The flat or unit number. This includes things like SHOP number.}
#' \item{\code{NUMBER_FIRST}}{As used in the PSMA, this identified the first (or only) number
#' in the address range.}
#' \item{\code{NUMBER_LAST}}{As used in the PSMA, if an address is marked as having
#' a range of street numbers, the last of the range.}
#' \item{\code{NUMBER_SUFFIX}}{A \code{raw} vector. The suffix observed after the numbers. The PSMA
#' technically has multiple suffixes for each number component.}
#' \item{\code{H0}}{If \code{hash_StreetName = TRUE}, the DJB2 hash (as used in
#' \code{\link{HashStreetName}} of the street name.). Observed to have performance
#' benefits.}
#' \item{\code{STREET_NAME}}{The (uppercase) of the street name. Streets such
#' as 'THE ESPLANADE' or 'THE AVENUE' are treated as entirely made up of a street
#' name and have a \code{STREET_TYPE_CODE} of zero.}
#' \item{\code{STREET_TYPE_CODE}}{An integer, the street type code marking the type
#' of street such as ROAD, STREET, AVENUE, etc. They code corresponds approximately
#' to the rank of their frequency in addresses.}
#' \item{\code{STREET_TYPE}}{If \code{integer_StreetType = FALSE}, then the (uppercase)
#' standard name of the street type.}
#' \item{\code{POSTCODE}}{An integer vector, the postcode observed.}
#' }
#'
#' @details
#' By convention observed in the PSMA, street names such as 'THE ESPLANADE' have
#' a street name of 'THE ESPLANADE' and an absent street type code.
#'
#' Non-addresses passed have unspecified behaviour, though usually the
#' numbers of the standard address will be 0 or NA. Postcodes may be negative
#' in some circumstances where a postcode is not detected,
#' though this should not be relied on.
#'
#' For maximum performance, consider setting \code{integer_StreetType} and
#' \code{hash_StreetName} to \code{TRUE}. It has been observed that joining
#' two tables together has been faster when using the hash of the standardized
#' street name, rather than the street name, even when taking into account
#' the hashing process.
#'
#' For performance reasons, addresses with more than 32 words are not supported.
#'
#'
#' @export

standardize_address <- function(Address,
                                AddressLine2 = NULL,
                                return.type = c("data.table", "integer"),
                                integer_StreetType = FALSE,
                                hash_StreetName = FALSE,
                                check = 1L) {
  do_check <- !identical(check, 0L)
  if (do_check) {
    Address_check <- check_address_input(Address, 1L)
    AddressLine2_check <- 0L
    if (!is.null(AddressLine2)) {
      AddressLine2_check <- check_address_input(AddressLine2, 1L)
    }
    if (Address_check) {
      stop("`Address` failed check for position ", Address_check)
    }
  }
  return.type <- match.arg(return.type)
  integer_StreetType <- isTRUE(integer_StreetType)
  hash_StreetName <- isTRUE(hash_StreetName)
  Ans <-
    if (is.null(AddressLine2)) {
      if (hash_StreetName) {
        standard_address2(Address)
      } else {
        standard_address_postcode_trie(Address)
      }
    } else {
      standard_address3(Address,
                        AddressLine2,
                        Postcode = extract_postcode(AddressLine2),
                        KeepStreetName = !hash_StreetName)
    }

  if (!integer_StreetType) {
    STREET_TYPE_CODE <- NULL
    Ans[STREET_TYPE_CODE > 0L, "STREET_TYPE" := .permitted_street_type_ord()[STREET_TYPE_CODE]]
  }

  Ans[]



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
  ans <- .Call("C_standard_address_postcode_trie", ensure_uppercase(x), PACKAGE = packageName())
  setDT(ans)
  setnames(ans,
           c("STREET_TYPE_CODE", "STREET_NAME",
             "FLAT_NUMBER",
             "NUMBER_FIRST",
             "NUMBER_LAST",
             "NUMBER_SUFFIX",
             "POSTCODE"))
  setcolorder(ans, c("FLAT_NUMBER", "NUMBER_FIRST", "NUMBER_LAST",
                     "NUMBER_SUFFIX",
                     "STREET_NAME",
                     "STREET_TYPE_CODE", "POSTCODE"))
  ans[]
}


test_C_test_ALPHABET_ENC <- function(x) {
  .Call("C_test_ALPHABET_ENC", x, PACKAGE = packageName())
}






