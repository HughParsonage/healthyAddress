requireNamespace <- function(package) {
  base::requireNamespace(package, quietly = TRUE)
}

if (!requireNamespace("data.table")) {
  install.packages(c("hutils", "data.table"))
}
if (!requireNamespace("tinytest")) {
  install.packages("tinytest")
}
pkgs <- c("magrittr", "fst", "hutils", "hutilscpp", "fastmatch")
if (any(!sapply(pkgs, requireNamespace))) {
  install.packages(pkgs)
}
print(Sys.getenv())



if (!requireNamespace("PSMA") || packageVersion("PSMA") < "0.6.1") {
  if (!requireNamespace("remotes")) {
    install.packages("remotes")
  }
  remotes::install_github("HughParsonage/PSMA")
}


