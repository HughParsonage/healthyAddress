.onLoad <- function(libname = find.package("healthyAddress"), pkgname = "healthyAddress") {
  if (is.null(getOption("healthyAddress.data_env"))) {
    options(healthyAddress.data_env = new.env())
  }
}

.onUnload <- function (libpath) {
  library.dynam.unload(packageName(), libpath)
}
