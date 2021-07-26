#' Extract the n-th digit of a duocentehexaquinquagesimal number
#' @param x \code{integer(n)}
#' @param d \code{integer(1)} One of 0:3.  Other integers silently return \code{x}.
#'
#' @return
#' For \code{b = 256}
#' if \deqn{x = a_0 + a_1b + a_2b^2 + a_3b^3}
#' then \code{.digit(x, d) = a_d}
#' @export

.digit256 <- function(x, d) {
  .Call("Cdigit256", x, d, PACKAGE = packageName())
}
