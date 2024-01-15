fillPostcodeStreets <- function(DT, test = 0L) {
  if (missing(DT)) {
    DT <-
      qs::qread(system.file("extdata", "POSTCODE-STREET_TYPE_CODE-STREET_NAME.qs", package = packageName()))
  }
  setkeyv(DT, "POSTCODE")
  .Call("C_fillPostcodeStreets",
        .subset2(DT, "POSTCODE"),
        .subset2(DT, "STREET_NAME"),
        .subset2(DT, "STREET_TYPE_CODE"),
        test,
        PACKAGE = packageName())
}

freePostcodeStreets <- function() {
  .Call("C_freeALL_POSTCODE_STREETS", NULL, PACKAGE = packageName())
}
