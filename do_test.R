library(tinytest)
library(healthyAddress)
.test <- function (filter = NULL, ...) {
  for (file.R in dir("inst/tinytest",
                     pattern = paste0("^test.*", filter),
                     full.names = TRUE)) {
    if (grepl("Hash", file.R)) next # unHashname requires download
    tinytest::run_test_file(file.R)
  }
}
healthyAddress:::standard_address2("47/174 ESPLANADE WEST PORT MELBOURNE 3207")
healthyAddress:::standard_address2("47/174 ESPLANADE WEST PORT MELBOURNE 3207")
.test()




