expect_equal(healthyAddress:::anyComma(c(" ", "", "fff"), 0L), 0)
expect_equal(healthyAddress:::anyComma(c(" ", "", "fff"), 1L), 0)
expect_equal(healthyAddress:::anyComma(c(" ", "", "f,"), 0L), 3)
expect_equal(healthyAddress:::anyComma(c(" ", "", "f,"), 1L), 3)

expect_equal(healthyAddress:::contains_big4(c("BIG4", "A", "SOMEWHERE BIG4 123")),
             c(1L, 0L, 1L))
