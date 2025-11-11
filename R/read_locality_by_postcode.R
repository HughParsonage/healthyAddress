

read_locality_by_postcode <- function() {
  qs2::qd_read(system.file("extdata", "LOCALITY_BY_POSTCODE.qdata", package = packageName()))
}
