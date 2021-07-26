library(healthyAddress)
a <- 7L + 19L * 256L + 23L * 256L * 256L
expect_equal(.digit256(a, 0L), 7L)
expect_equal(.digit256(a, 1L), 19L)
expect_equal(.digit256(a, 2L), 23L)
expect_equal(.digit256(a, 3L), 0L)
