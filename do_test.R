.test <- function (filter = NULL, ...) {
  for (file.R in dir("inst/tinytest",
                     pattern = paste0("^test.*", filter),
                     full.names = TRUE)) {
    tinytest::run_test_file(file.R)
  }
}

.test()

