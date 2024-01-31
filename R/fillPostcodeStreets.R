fillPostcodeStreets <- function(DT, test = 0L) {
  if (missing(DT)) {
    file.qs <-
      system.file("extdata", "POSTCODE-STREET_TYPE_CODE-STREET_NAME.qs", package = packageName())

    if (!file.exists(file.qs) || file.access(file.qs, mode = 4L)) {
      message("file.qs below not found or readable\n\t", file.qs)
      return(invisible(NULL))
    }

    DT <- qs::qread(file.qs)
  }
  if (!haskey(DT) || identical(key(DT)[1], "POSTCODE")) {
    setkeyv(DT, "POSTCODE")
  }
  .Call("C_fillPostcodeStreets",
        .subset2(DT, "POSTCODE"),
        .subset2(DT, "STREET_NAME"),
        coalesce0(.subset2(DT, "STREET_TYPE_CODE")),
        test,
        PACKAGE = packageName())
}

freePostcodeStreets <- function() {
  .Call("C_freeALL_POSTCODE_STREETS", NULL, PACKAGE = packageName())
}
