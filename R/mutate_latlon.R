#' Add latitude and longitude columns to a standard address
#' @param DT A \code{data.table} from \code{standardize_address}
#' @param data_dir The directory in which the latitude longitude data has been
#' downloaded. (See \code{\link{download_latlon_data}}.)
#'
#' @return
#' \code{DT} with the columns \code{lat} and \code{lon} added, by reference,
#' the latitude and longitude of the address for that row.
#'
#' @export
mutate_latlon <- function(DT, data_dir = getOption("healthyAddress.data_dir")) {
  if (!is.character(data_dir) || !isTRUE(dir.exists(data_dir))) {
    stop("data_dir is not a valid directory.")
  }
  if (!dir.exists(file.path(data_dir, "latlon"))) {
    stop("data_dir does not contain a directory 'latlon'. Run `download_latlon_data` to download the necessary data.")
  }
  if (!is.environment(ENV <- getOption("healthyAddress.data_env"))) {
    stop("option healthyAddress.data_env is not set to an environment, aborting")
  }
  .stes <- c("NSW", "VIC", "QLD", "SA", "WA", "TAS", "NT", "ACT", "OT")[postcode2ste(unique_Postcodes(.subset2(DT, "POSTCODE")))]
  .load_latlon_data(.stes)
  DT[, c("lat", "lon") := list(NA_real_, NA_real_)]
  STREET_NAME <- hSTREET_NAME <- H0 <- NULL
  if (hasName(DT, "H0")) {
    DT[, hSTREET_NAME := H0]
  }
  if (!hasName(DT, "hSTREET_NAME")) {
    if (!hasName(DT, "STREET_NAME")) {
      stop("DT does not have columns 'hSTREET_NAME' or 'STREET_NAME'")
    }
    DT[, "hSTREET_NAME" := HashStreetName(STREET_NAME)]
  }
  for (..ste in .stes) {
    ste_latlon <- get0(paste0(..ste, "latlon"), envir = ENV, inherits = FALSE)
    i.lat <- i.lon <- NULL
    DT[ste_latlon, c("lat", "lon") := list(i.lat, i.lon), on = c("POSTCODE", "NUMBER_FIRST", "hSTREET_NAME", "STREET_TYPE_CODE")]
  }
  DT[]
}
