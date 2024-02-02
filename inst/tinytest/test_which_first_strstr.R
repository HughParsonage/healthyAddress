library(tinytest)
expect_equal(healthyAddress:::which_first_strstr(c(NA, "", "AA", "A,A"), ",A"), 4L)
expect_equal(healthyAddress:::which_first_strstr(c(NA, "", "AA", "A,A"), ",AA"), 0L)
