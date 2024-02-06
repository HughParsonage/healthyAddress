.onLoad <- function(libname = find.package("healthyAddress"), pkgname = "healthyAddress") {
  if (is.null(getOption("healthyAddress.data_env"))) {
    options(healthyAddress.data_env = new.env())
  }
  if (isTRUE(startsWith(Sys.getenv("USERNAME"), "hugh"))) {
    .Call("C_StaticAssert", 0L, PACKAGE = packageName())
  }
  utils::globalVariables(".")
  fillPostcodeStreets()
  return(invisible(NULL))
}

.onUnload <- function (libpath) {
  freePostcodeStreets()
  library.dynam.unload(packageName(), libpath)
}
