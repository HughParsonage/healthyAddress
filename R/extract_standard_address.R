#' Standardize and compactly index Australian addresses
#' @param address A character vector like \code{10 MALVINA PL CARLTON VIC 3053}
#' @param .check Should internal inputs be checked.
#' @examples
#'
#' extract_standard_address("10 MALVINA PL CARLTON VIC 3053")
#'
#' @export

extract_standard_address <- function(address,
                                     .check = TRUE) {
  tt3()
  xxPostcodes <- extract_postcode(address)
  min_postcode <- min(xxPostcodes, na.rm = TRUE)
  max_postcode <- max(xxPostcodes, na.rm = TRUE)
  PSTO <- .permitted_street_type_ord()
  tt3()
  xxStreetTypeCd2 <- match_StreetType(address, m = 2L)
  xxStreetTypeCd2u <- sort(unique(.digit256(xxStreetTypeCd2, 0L)))

  tt3()
  xxStreetName <- match_StreetName(address)

  DT <-
    list(address = address,
         xxPostcodes = xxPostcodes,
         xxStreetTypeCd0 = .digit256(xxStreetTypeCd2, 0L),
         xxStreetName = xxStreetName,
         orig_order = seq_along(address))
  setDT(DT)
  DT[, xxStreetTypeCd := .digit256(xxStreetTypeCd2, 0L)]
  setkey(DT, xxPostcodes, xxStreetTypeCd0, xxStreetName, NUMBER_FIRST)
  FF <- get_FullNamedAddressData()
  if (!hasName(FF, "StreetTypeCodei")) {
    FF[, StreetTypeCodei := chmatch(STREET_TYPE_CODE, .permitted_street_type_ord())]
  }
  tt3()
  if (length(xxPostcodes) == 1L) {
    if (!anyNA(xxPostcodes)) {
      FF <- FF[.(xxPostcodes, .permitted_street_type_ord()[xxStreetTypeCd2u])]
    }
  } else if (length(xxStreetTypeCd2u) == 1L) {
    uPostcodes <- unique_Postcodes(xxPostcodes)
    FF <- FF[hutilscpp::and3s(POSTCODE %in% uPostcodes, StreetTypeCodei == xxStreetTypeCd2u)]
  } else {
    uPostcodes <- unique_Postcodes(xxPostcodes)
    FF <- FF[hutilscpp::and3s(POSTCODE %in% uPostcodes, StreetTypeCodei %in% xxStreetTypeCd2u)]
  }
  tt3()
  FF <- FF[DT, on = .(POSTCODE = xxPostcodes,
                      StreetTypeCodei = xxStreetTypeCd0,
                      STREET_NAME = xxStreetName,
                      NUMBER_FIRST)]
  FF <- unique(FF, by = "orig_order")
  tt3()
  return(FF)

  FF2 <- unique(FF, by = c("POSTCODE", "STREET_TYPE_CODE"))
  FF2[, seqN := seq_len(.N), by = "POSTCODE"]

  observed_max_stcds_any_postcode <- FF2[, max(seqN)]
  if (observed_max_stcds_any_postcode > .MAX_uN_STCDs()) {
    stop("Internal error: Number of street codes per postcode exceeded.")
  }



  xx <- address
  id <- .subset2(FF, "ADDRESS_DETAIL_INTRNL_ID")
  Postcodes <- .subset2(FF, "POSTCODE")
  StreetTypesCd <- chmatch(.subset2(FF, "STREET_TYPE_CODE"), .permitted_street_type_ord())
  StreetNames <- .subset2(FF, "STREET_NAME")
  Numbers <- .subset2(FF, "NUMBER_FIRST")
  Postcode2 <- .subset2(FF2, "POSTCODE")
  StreetTypes2 <- chmatch(.subset2(FF2, "STREET_TYPE_CODE"), .permitted_street_type_ord())
  # cat(typeof(StreetTypesCd), typeof(Postcode2), typeof(StreetTypes2), "\n")
  Checks <- .check

  .Call("CExtractAddressID",
        xx,
        xxPostcodes,
        id,
        Postcodes,
        StreetTypesCd,
        StreetNames,
        Numbers,
        Postcode2,
        StreetTypes2,
        Checks,
        PACKAGE = packageName())

}


get_FullNamedAddressData <- function(envir = NULL) {
  if (is.null(envir)) {
    if (requireNamespace("PSMA", quietly = TRUE)) {
      envir <- getOption("PSMA_env")
    } else {
      envir <- new.env()
    }
  }
  FullNamedAddressData <-
    if (exists("FullNamedAddressData", envir = envir, inherits = FALSE)) {
      get("FullNamedAddressData", envir = envir, inherits = FALSE)
    } else {
      X <- PSMA::get_fst("STREET_LOCALITY_ID__STREET_NAME_STREET_TYPE_CODE")
      Y <- PSMA::get_fst("STREET_ID_vs_ADDRESS_ID")
      Z <- X[Y,
             .(ADDRESS_DETAIL_INTRNL_ID, POSTCODE, STREET_TYPE_CODE, STREET_NAME, NUMBER_FIRST, FLAT_NUMBER),
             on = .(STREET_LOCALITY_INTRNL_ID)]
      Z[, FLAT_NUMBER := fcoalesce(FLAT_NUMBER, 0L)]
      setkeyv(Z, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST", "FLAT_NUMBER"))
      assign("FullNamedAddressData",
             Z,
             envir = envir)
    }
  setkeyv(FullNamedAddressData, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))[]
}

"%fin%" <- fastmatch::`%fin%`

.MAX_uN_STCDs <- function() {
  .Call("MAX_uN_STCDs", NULL, PACKAGE = packageName())
}

extract_street_code <- function(address, poa) {
  avbl_street_codes <- .Call("Cpoa_has_stcd", as.integer(poa), PACKAGE = packageName())
  head(avbl_street_codes)
}
tt3 <- function() {
  # Only display info during dev
  if (interactive() && file.exists("R/healthyAddress-package.R")) {
    cat(format(Sys.time(), "%H:%M:%OS3"), "\n")
  }
}



extract_postcode <- function(x, m = 0L) {
  if (m) {
    n <- nchar(x, type = "bytes")
    return(as.integer(substr(x, n - 4L, n)))
  }
  .Call("CExtractPostcode", x, PACKAGE = packageName())
}

.set_cols_first <- function(DT, cols) {
  return(setcolorder(DT, c(intersect(cols, names(DT)), setdiff(names(DT), cols))))
}


# Used primarily to populate C arrays
get_uStreetTypes_by_POSTCODE <- function(envir = getOption("PSMA_env", new.env())) {

  if (exists("uStreetTypes_by_POSTCODE", envir = envir, inherits = FALSE)) {
    get("uStreetTypes_by_POSTCODE", envir = envir, inherits = FALSE)
  } else {
    FF <- get_FullNamedAddressData()
  uniqueN_StreetTypes_by_POSTCODE <-
    FF[, .(nSTREET_TYPES = uniqueN(STREET_TYPE_CODE)), keyby = .(POSTCODE)]

  unique__StreetTypes_by_POSTCODE <-
    FF[, .(STREET_TYPES = unique(STREET_TYPE_CODE)), keyby = .(POSTCODE)]

  CJ_POSTCODE_StreetType_Exists <-
    copy(unique__StreetTypes_by_POSTCODE) %>%
    .[, STREET_TYPES := chmatch(STREET_TYPES, .permitted_street_type_ord())] %>%
    dcast(POSTCODE ~ STREET_TYPES,
          fun.aggregate = length,
          value.var = "STREET_TYPES") %>%
    melt(id.vars = "POSTCODE",
         variable.name = "STREET_TYPE",
         value.name = "Exists",
         variable.factor = FALSE)






  }
}


CExtractStdAddress2 <- function(address, street_names) {
  .Call("CExtractStdAddress", address, .permitted_street_type_ord(), PACKAGE = packageName())
}
CwhichStreetName3_ <- function(x) {
  stopifnot(is.character(x))
  .Call("CwhichStreetName3", x, PACKAGE = packageName())
}



FindSentence <- function(x, word1, word2) {
  .Call("CFindSentence", x, word1, word2, PACKAGE = packageName())
}


# Returns the
LocalityGivenPostcode <- function(address, poa) {

  # We want to load the namespace
  if (!requireNamespace("PSMA", quietly = TRUE)) {
    stop("Package PSMA is required. See library(PSMA.foyer) for installation details.")
  }

  stopifnot(is.character(address), is.integer(poa), length(address) == length(poa))
  stopifnot(isNamespaceLoaded("PSMA"))
  if (is.null(cache_env)) {
    cache_env <- getOption("PSMA_env", new.env())
  }

  # LOCALITY_vs_LOCALITY_PID <- PSMA::get_fst("LOCALITY_vs_LOCALITY_PID",
  #                                           cache_env = cache_env)
  # LOCALITY_VS_POSTCODE <- PSMA::get_fst("LOCALITY_VS_POSTCODE")
  # STREET_BY_POSTCODE <- PSMA::get_fst("STREET_BY_POSTCODE")

  FullNamedAddressData <-
    if (exists("FullNamedAddressData", envir = cache_env, inherits = FALSE)) {
      get("FullNamedAddressData", envir = cache_env, inherits = FALSE)
    } else {
      X <- PSMA::get_fst("STREET_LOCALITY_ID__STREET_NAME_STREET_TYPE_CODE")
      Y <- PSMA::get_fst("STREET_ID_vs_ADDRESS_ID")
      Z <- X[Y,
             .(ADDRESS_DETAIL_INTRNL_ID, POSTCODE, STREET_TYPE_CODE, STREET_NAME, NUMBER_FIRST),
             on = .(STREET_LOCALITY_INTRNL_ID)]
      setkeyv(Z, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))
      assign("FullNamedAddressData",
             Z,
             envir = cache_env)
    }
  setkeyv(FullNamedAddressData, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))

  i <- min_i <- max_i <- NULL
  STREET_BY_POSTCODE[, i := 0:(.N - 1L)]
  minmax_i <- STREET_BY_POSTCODE[, .(min_i = min(i), max_i = max(i)), keyby = "POSTCODE"]

  # Create a table such that poa_by_r[p] = postcode
  poa_by_r <- data.table(POSTCODE = 0:(STREET_BY_POSTCODE[, max(POSTCODE)]))
  setkeyv(poa_by_r, "POSTCODE")
  minmax_i[poa_by_r, on = "POSTCODE"]

  FullNamedAddressData



}

EnsureUC <- function(x) {
  .Call("CEnsureUC", x, PACKAGE = packageName())
}

do_EncodeStreet <- function(x) {
  x <- EnsureUC(x)
  m <- chmatch(x, .permitted_street_type_ord(), nomatch = 0L)
  Abbrev <- PSMA::street_type_decoder$street_abbrev
  Abbrevi <- chmatch(PSMA::street_type_decoder$street_type, .permitted_street_type_ord(), nomatch = 0L)
  .Call("CEncodeStCd", x, m, Abbrev, Abbrevi, PACKAGE = packageName())
}



Extract2_ <- function(xx, id, Postcodes, StreetTypes, StreetNames, Numbers) {
  .Call("Extract2", xx, id, Postcodes, StreetTypes, StreetNames, Numbers,
        chmatch(StreetTypes, .permitted_street_type_ord(), nomatch = 0L),
        PACKAGE = packageName())
}

test_touppers <- function(x) {
  .Call("Ctest_touppers", x, PACKAGE = packageName())
}

PoaHasSt <- function(x, y) {
  .Call("CPoaHasSt", x, y, PACKAGE = packageName())
}


NamePresent <- function(j, x, Names = NULL, from = 0L, to = length(Names) - 1L) {
  if (is.null(Names)) {
    Names <- get_FullNamedAddressData()[["STREET_NAME"]]
    i <- seq_along(Names)
    nd <- !duplicated(Names)
    Nnd <- Names[nd]
    ind <- i[nd]
    o <- .Call("CNamePresent", j, x, Nnd, from, to, PACKAGE = packageName())
  }
  .Call("CNamePresent", j, x, Names, from, to, PACKAGE = packageName())
}
