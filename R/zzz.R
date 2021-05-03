.onUnload <- function (libpath) {
  library.dynam.unload(packageName(), libpath)
}
