% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/mutate_latlon.R
\name{mutate_latlon}
\alias{mutate_latlon}
\title{Add latitude and longitude columns to a standard address}
\usage{
mutate_latlon(DT, data_dir = getOption("healthyAddress.data_dir"))
}
\arguments{
\item{DT}{A \code{data.table} from \code{standardize_address}}

\item{data_dir}{The directory in which the latitude longitude data has been
downloaded. (See \code{\link{download_latlon_data}}.)}
}
\value{
\code{DT} with the columns \code{lat} and \code{lon} added, by reference,
the latitude and longitude of the address for that row.
}
\description{
Add latitude and longitude columns to a standard address
}
