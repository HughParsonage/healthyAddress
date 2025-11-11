
# functions to be executed on on load and unload

# nocov start
fillPostcodeStreets <- function(DT, test = 0L) {
  if (missing(DT)) {
    file.qdata <-
      system.file("extdata", "POSTCODE-STREET_TYPE_CODE-STREET_NAME.qdata", package = packageName())

    if (!file.exists(file.qdata) || file.access(file.qdata, mode = 4L)) {
      message("file.qdata below not found or readable\n\t", file.qdata)
      return(invisible(NULL))
    }

    DT <- qs2::qd_read(file.qdata)
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
# nocov end
