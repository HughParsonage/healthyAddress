requireNamespace <- function(package) {
  base::requireNamespace(package, quietly = TRUE)
}

if (!requireNamespace("data.table")) {
  install.packages(c("hutils", "data.table"), quiet=TRUE)
}
if (!requireNamespace("tinytest")) {
  install.packages("tinytest", quiet=TRUE)
}
pkgs <- c("magrittr", "fst", "qs", "hutils", "hutilscpp", "fastmatch")
if (any(!sapply(pkgs, requireNamespace))) {
  install.packages(pkgs, quiet = TRUE)
}
print(Sys.getenv())



# if (!requireNamespace("PSMA") || packageVersion("PSMA") < "0.6.1") {
#   if (!requireNamespace("remotes")) {
#     install.packages("remotes")
#   }
#   remotes::install_github("HughParsonage/PSMA")
# }


