library(healthyAddress)

expect_equal(healthyAddress:::max_nchar(c("a", "bc")), 2L)
expect_equal(healthyAddress:::max_nchar(c("", "")), 0L)
