

read_locality_by_postcode <- function() {
  qs::qread(system.file("extdata", "LOCALITY_BY_POSTCODE.qs", package = packageName()))
}
