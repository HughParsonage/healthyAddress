expect_true(healthyAddress:::isPostcode(2000L) & TRUE)
expect_false(healthyAddress:::isPostcode(NA_integer_) & TRUE)
expect_equal(healthyAddress:::isPostcode(4513L), 1L) # new postcode
expect_equal(healthyAddress:::isPostcode(6219L), 1L) # new postcode
