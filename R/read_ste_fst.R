#' Get internal data
#'
#' @param ste The abbreviated state name.
#' @param columns Character vector of columns to select. If \code{NULL}, all columns are selected.
#' @param data_env The environment in which objects are cached. Mainly for
#' internal use.
#' @param data_dir The file directory into which the downloaded files should be
#' stored. Defaults to a temporary directory. It is recommended to set the option
#' `healthyAddress.data_dir` so that subsequent calls to this function do not
#' result in unnecessary downloads.
#' @param rbind Whether or not to bind the list result should multiple states
#' be requested.
#'
#' @return
#' A \code{data.table} containing all the addresses in the given states.
#'
#'
#' @export
read_ste_fst <- function(ste = c("ACT", "NSW", "NT", "OT", "QLD", "SA", "TAS", "VIC", "WA"),
                         columns = NULL,
                         data_env = getOption("healthyAddress.data_env"),
                         data_dir = getOption("healthyAddress.data_dir", tempfile()),
                         rbind = TRUE) {
  ste <- match.arg(ste, several.ok = TRUE)

  if (length(ste) == 1L) {
    if (is.environment(data_env) && exists(var_ste <- paste0(ste, "_FULL_ADDRESS"), envir = data_env)) {
      ans <- get(var_ste, envir = data_env)
      if (is.null(columns)) {
        return(ans)
      }
      return(hutils::selector(ans, cols = columns))
    }

    file.fst <- file.path(data_dir, paste0(ste, "_FULL_ADDRESS.fst"))
    if (!file.exists(file.fst)) {
      if (!nzchar(hutils::provide.file(file.fst))) {
        stop("`data_dir` as specified cannot accommodate a file.")
      }
      url <- sprintf("https://github.com/HughParsonage/healthyAddressData/raw/master/%s_FULL_ADDRESS.fst", ste)

      status <- utils::download.file(url,
                                     mode = "wb",
                                     destfile = file.fst,
                                     quiet = TRUE)
      if (status) {
        stop("Unable to download ", ste, "from URL:\n\t", url)
      }
    }
    columns_avbl <- fst::metadata_fst(file.fst)[["columnNames"]]
    columns <- columns[columns %in% columns_avbl]
    ans <- fst::read_fst(file.fst, columns = columns, as.data.table = TRUE)
    if (is.environment(data_env) && is.null(columns)) {
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
                    data_env = getOption("healthyAddress.data_env"),
                    data_dir = getOption("healthyAddress.data_dir", tempfile())) {

  if (.Exists(NAME, columns, data_env)) {
    return(.Get(NAME, columns, data_env))
  }
  if (.Exists(NAME, NULL, data_env)) {
    full <- .Get(NAME, NULL, envir = data_env)
    if (is.null(columns) || !is.data.table(full)) {
      return(full)
    } else {
      return(hutils::selector(full, cols = columns))
    }
  }
  file.fst <- paste0(data_dir, "/", NAME, ".fst")
  if (!file.exists(file.fst)) {
    file.fst <- system.file("extdata", paste0(NAME, ".fst"), package = packageName())
  }
  if (!file.exists(file.fst)) {
    stop("Expected file at ", normalizePath(file.fst, winslash = "/"))
  }
  columns_avbl <- fst::metadata_fst(file.fst)[["columnNames"]]
  columns <- columns[columns %in% columns_avbl]
  ans <- fst::read_fst(file.fst, columns = columns, as.data.table = TRUE)
  if (is.environment(data_env)) {
    assign(sys_NAME(NAME, columns = columns), value = ans, envir = data_env)
  }
  return(ans)
}

clear_data_env <- function(data_env = getOption("healthyAddress.data_env")) {
  if (is.environment(data_env)) {
    rm(list = ls(envir = data_env), envir = data_env)
  }
}

sys_NAME <- function(NAME, columns = NULL) {
  if (is.null(columns)) {
    return(NAME)
  }
  paste0(NAME, ":columns:", toString(sort(columns)))
}

.Exists <- function(NAME, columns = NULL, envir = getOption("healthyAddress.data_env")) {
  is.environment(envir) &&
  exists(sys_NAME(NAME, columns = columns),
         envir = envir,
         inherits = FALSE)
}

.Get <- function(NAME, columns = NULL, envir = getOption("healthyAddress.data_env")) {
  get0(sys_NAME(NAME, columns = columns),
       envir = envir,
       inherits = FALSE)
}

