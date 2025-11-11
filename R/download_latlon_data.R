#' Download latitude longitude data by address
#' @param .ste The jurisdiction to download. Default is to download all.
#' @param data_dir The directory for \code{healthyAddress}. Data will be downloaded into a
#' subdirectory \code{latlon} thereof.
#' @param repo The repository from which data will be downloaded. Currently only the default is supported.
#' @param overwrite \code{logical(1)} Applicable only if the file already exists
#' prior to invoking the function. If \code{FALSE}, an error is raised. If \code{NA},
#' the default, the file is returned, with a message. Set to \code{TRUE} if you wish to
#' overwrite the files (possibly having changed `repo` to reflect updated data).
#'
#' @return
#' Called for its side effect (downloading the files), but returns the files downloaded.
#'
#' @export
download_latlon_data <- function(.ste = c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT"),
                                 data_dir = getOption("healthyAddress.data_dir"),
                                 repo = "https://github.com/HughParsonage/PSMA-202508",
                                 overwrite = NA) {
  if (!is.character(data_dir) || length(data_dir) != 1 || anyNA(data_dir) || !dir.exists(data_dir)) {
    stop("data_dir must be set to an extant directory, preferably via\n\toptions(healthyAddress.data_dir = <>) ")
  }
  provide.dir(file.path(data_dir, "latlon"))
  stopifnot(length(repo) == 1, is.character(repo), !anyNA(repo))
  repo <- trimws(repo)
  stopifnot(startsWith(repo, "https://"))

  if (endsWith(repo, "/")) {
    # don't want to make users worry about trailing slashes
    repo <- sub("/$", "", repo)
  }
  if (length(.ste) == 1) {
    surl <- sprintf("%s/raw/master/%s_latlon.qdata", repo, .ste)
    file.qdata <- file.path(data_dir, "latlon", paste0(.ste, ".qdata"))
    if (file.exists(file.qdata)) {
      if (isFALSE(overwrite)) {
        stop("overwrite = FALSE yet file.qdata = ", file.qdata, " exists.")
      }
      if (!isTRUE(overwrite)) {
        message(file.qdata, " already exists so will not be downloaded. (Set overwrite = TRUE to force the download.)")
        return(file.qdata)
      }
    }
    status <- download.file(surl, destfile = file.qdata, mode = "wb")
    if (status) {
      stop("download failed for ", .ste, " with status code ", status)
    }
    return(file.qdata)
  }
  vapply(.ste, download_latlon_data, "")
}

.load_latlon_data <- function(.ste = c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT"),
                              data_dir = getOption("healthyAddress.data_dir"),
                              data_env = getOption("healthyAddress.data_env"),
                              overwrite = FALSE) {
  stopifnot(dir.exists(data_dir), is.environment(data_env))
  for (..ste in .ste) {
    obj_name <- paste0(..ste, "latlon")
    if (!isTRUE(overwrite) && exists(obj_name, data_env, inherits = FALSE)) {
      next
    }
    dat <- qs2::qd_read(file.path(data_dir, "latlon", paste0(..ste, ".qdata")))
    stopifnot(hasName(dat, "c_latlon"))
    c_latlon <- NULL
    dat[, c("lat", "lon") := decompress_latlon_general(c_latlon)]
    setnames(dat, "STREET_NAME", "hSTREET_NAME")
    assign(obj_name, value = dat, envir = data_env, inherits = FALSE)
  }
}

