#' Get internal data
#'
#' @param ste The abbreviated state name.
#' @param columns Character vector of columns to select. If \code{NULL}, all columns are selected.
#'
#'
#' @export
read_ste_fst <- function(ste = c("ACT", "NSW", "NT", "OT", "QLD", "SA", "TAS", "VIC", "WA"),
                         columns = NULL,
                         data_env = getOption("healthyAddress.data_env"),
                         rbind = TRUE) {
  ste <- match.arg(ste, several.ok = TRUE)

  if (length(ste) == 1L) {
    if (is.environment(data_env) && exists(var_ste <- paste0(ste, "_FULL_ADDRESS"), envir = data_env)) {
      return(get(var_ste, envir = data_env))
    }

    file.fst <- paste0("inst/extdata/", ste, "_FULL_ADDRESS.fst")
    if (!file.exists(file.fst)) {
      file.fst <- system.file("extdata", paste0(ste, "_FULL_ADDRESS.fst"), PACKAGE = packageName())
    }
    columns_avbl <- fst::metadata_fst(file.fst)[["columnNames"]]
    columns <- columns[columns %in% columns_avbl]
    ans <- fst::read_fst(file.fst, columns = columns, as.data.table = TRUE)
    if (is.environment(data_env)) {
      assign(var_ste, value = ans, envir = data_env)
    }
    return(ans)
  }
  L <- lapply(ste, read_ste_fst, columns = columns, data_env = data_env)
  if (isTRUE(rbind)) {
    rbindlist(L, use.names = TRUE, fill = TRUE)
  } else {
    L
  }
}

sys_fst <- function(NAME,
                    columns = NULL,
                    data_env = getOption("healthyAddress.data_env")) {
  if (is.environment(data_env) && exists(NAME, envir = data_env, inherits = FALSE)) {
    full <- get(NAME, envir = data_env, inherits = FALSE)
    if (is.null(columns) || !is.data.table(full)) {
      return(full)
    } else {
      return(hutils::selector(full, cols = columns))
    }
  }
  file.fst <- paste0("inst/extdata/", NAME, ".fst")
  if (!file.exists(file.fst)) {
    file.fst <- system.file("extdata", paste0(NAME, ".fst"), PACKAGE = packageName())
  }
  if (!file.exists(file.fst)) {
    stop("Expected file at ", normalizePath(file.fst, winslash = "/"))
  }
  columns_avbl <- fst::metadata_fst(file.fst)[["columnNames"]]
  columns <- columns[columns %in% columns_avbl]
  ans <- fst::read_fst(file.fst, columns = columns, as.data.table = TRUE)
  if (is.environment(data_env)) {
    assign(NAME, value = ans, envir = data_env)
  }
  return(ans)
}




