requireNamespace <- function(package) {
  base::requireNamespace(package, quietly = TRUE)
}

if (!requireNamespace("data.table")) {
  install.packages(c("hutils", "data.table"))
}
if (!requireNamespace("tinytest")) {
  install.packages("tinytest")
}
if (!requireNamespace("PSMA")) {
  if (!requireNamespace("remotes")) {
    install.packages("remotes", quiet = TRUE)
  }
  remotes::install_github("HughParsonage/PSMA")
}


