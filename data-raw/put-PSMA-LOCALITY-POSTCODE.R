library(data.table)
library(magrittr)
library(hutils)
library(hutilscpp)

all_psma <-
  dir(path = "~/Data/PSMA-Geocoded-Address-202105/G-NAF/", pattern = "\\.psv$", full.names = TRUE, recursive = TRUE)

all_LOCALITY_ALIAS <-
  grep("(?<!(STREET))_LOCALITY_ALIAS", all_psma, value = TRUE, perl = TRUE) %>%
  grep("Standard/", x = ., value = TRUE)

all_ADDRESS_DETAIL <-
  grep("ADDRESS_DETAIL", all_psma, value = TRUE, perl = TRUE)

stopifnot(length(all_LOCALITY_ALIAS) == length(all_ADDRESS_DETAIL))

LOCALITY_BY_POSTCODE <-
  lapply(seq_along(all_ADDRESS_DETAIL), function(i) {
    loc <- fread(all_LOCALITY_ALIAS[i], sep = "|", select = c("LOCALITY_PID", "NAME"), key = "LOCALITY_PID")
    add <- fread(all_ADDRESS_DETAIL[i], sep = "|", select = c("LOCALITY_PID", "POSTCODE"), key = "LOCALITY_PID")
    uloc <- unique(loc)
    uadd <- unique(add)
    uloc[uadd, POSTCODE := i.POSTCODE]
  }) |>
  rbindlist(use.names = TRUE, fill = TRUE)

if (file.exists("./healthyAddress.Rproj") && dir.exists("./inst/extdata/") &&
    !file.exists("./inst/extdata/LOCALITY_BY_POSTCODE.fst")) {
  qs::qsave(LOCALITY_BY_POSTCODE, "./inst/extdata/LOCALITY_BY_POSTCODE.qs")
}

