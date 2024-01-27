expect_equal(healthyAddress:::anyComma(c(" ", "", "fff"), 0L), 0)
expect_equal(healthyAddress:::anyComma(c(" ", "", "fff"), 1L), 0)
expect_equal(healthyAddress:::anyComma(c(" ", "", "f,"), 0L), 3)
expect_equal(healthyAddress:::anyComma(c(" ", "", "f,"), 1L), 3)
