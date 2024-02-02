expect_true(healthyAddress:::isPostcode(2000L) & TRUE)
expect_false(healthyAddress:::isPostcode(NA_integer_) & TRUE)
