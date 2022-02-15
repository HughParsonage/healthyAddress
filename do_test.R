.test <- function (filter = NULL, ...) {
  for (file.R in dir("inst/tinytest",
                     pattern = paste0("^test.*", filter),
                     full.names = TRUE)) {
    tinytest::run_test_file(file.R)
  }
}

# .test()
library(data.table)
racf_lookup <- fread("~/../Downloads/racf_lookup.csv")
setnames(racf_lookup, gsub("Physical Address ", "", names(racf_lookup)))
setnames(racf_lookup, gsub(" +", "_", names(racf_lookup)))
racf_lookup[, "Address" := paste0(Line_1, ", ", Suburb, " VIC ", Post_Code)]
cat("now:\n")
print(bench::system_time(rr <- healthyAddress::standardize_address(racf_lookup$Address)))
bench::system_time(dr <- healthyAddress:::Do_standard_address(toupper(racf_lookup$Address)))

