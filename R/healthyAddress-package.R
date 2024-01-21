#' Package for address standardization
#' @useDynLib healthyAddress, .registration = TRUE
#'
#' @rawNamespace import(data.table, except = "%notin%")
#' @importFrom fastmatch %fin%
#' @importFrom hutils %notin%
#' @importFrom fastmatch fmatch
#' @importFrom hutilscpp isntConstant
#' @importFrom hutilscpp fmatchp
#' @importFrom hutils coalesce
#' @importFrom magrittr %>%
#' @importFrom tools R_user_dir
#' @importFrom utils packageName
#' @importFrom utils hasName
#' @importFrom utils head
#' @keywords internal
"_PACKAGE"

# The following block is used by usethis to automatically manage
# roxygen namespace tags. Modify with care!
## usethis namespace: start
## usethis namespace: end
NULL
