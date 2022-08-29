


NumberSuffix2Raw <- function(x) {
  .Call("C_NumberSuffix2Raw", x, PACKAGE = packageName())
}

NumberSuffixFromRaw <- function(x) {
  all_suffixes <-
    c("A", "", "B", "C", "D", "F", "R", "S", "E", "G", "H", "L",
      "M", "U", "P", "V", "K", "J", "N", "I", "T", "O", "Q", "W", "X",
      "Z", "Y", "AA", "J1", "BC", "BA", "GF", "AB", "OA", "SE", "NW",
      "\\A", "GZ", "BB", "M1", "GX", "TT", "CD", "23", "35", "T3",
      "GR", NA, "14")

  all_suffixer <- NumberSuffix2Raw(all_suffixes)
  all_suffixes[match(as.integer(x), as.integer(all_suffixer))]
}

get_suffix <- function(Address) {
  .Call("Cget_suffix", Address, PACKAGE = packageName())
}
