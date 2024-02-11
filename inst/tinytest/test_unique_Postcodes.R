
expect_error(unique_Postcodes(""), "type")
x <- c(800L, 2444L, 3053L, 3053L, 2444L, 7470L)
expect_equal(unique_Postcodes(x),
             sort(unique(x)))

x <- c(x, NA_integer_)
expect_equal(unique_Postcodes(x),
             sort(unique(x)))

expect_equal(unique_Postcodes(c(1L, 800L), strict = TRUE), 800L)
expect_equal(uniqueN_Postcodes(1:9999), healthyAddress:::get_N_POSTCODES())
expect_equal(last(unique_Postcodes(1:9999)), healthyAddress:::get_MAX_POSTCODE())



