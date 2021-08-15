




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
             .(ADDRESS_DETAIL_INTRNL_ID,
               POSTCODE,
               STREET_TYPE_CODE,
               STREET_NAME,
               NUMBER_FIRST,
               FLAT_NUMBER),
             on = .(STREET_LOCALITY_INTRNL_ID)]
      Z[, FLAT_NUMBER := fcoalesce(FLAT_NUMBER, 0L)]
      setkeyv(Z, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST", "FLAT_NUMBER"))
      assign("FullNamedAddressData",
             Z,
             envir = envir)
    }
  setkeyv(FullNamedAddressData, c("POSTCODE", "STREET_TYPE_CODE", "STREET_NAME", "NUMBER_FIRST"))[]
}


.MAX_uN_STCDs <- function() {
  .Call("MAX_uN_STCDs", NULL, PACKAGE = packageName())
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











PoaHasSt <- function(x, y) {
  .Call("CPoaHasSt", x, y, PACKAGE = packageName())
}


