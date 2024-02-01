library(tinytest)
xnumbers <- healthyAddress:::xnumbers
xnumber128 <- healthyAddress:::xnumber128
if (healthyAddress:::uint128_not_supported()) {
  exit_file("uint128_not_supported")
}

expect_equal(xnumber128("123/456 789 2000"), list(123, 456, 789, 2000))
expect_equal(xnumbers("123/456 789 2000")[[1]], 4)

