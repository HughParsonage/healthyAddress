.onLoad <- function(libname = find.package("healthyAddress"), pkgname = "healthyAddress") {
  if (is.null(getOption("healthyAddress.data_env"))) {
    options(healthyAddress.data_env = new.env())
  }
  if (startsWith(Sys.getenv("USERNAME"), "hugh")) {
    .Call("C_StaticAssert", 0L, PACKAGE = packageName())
  }

}

.onUnload <- function (libpath) {
  library.dynam.unload(packageName(), libpath)
}
