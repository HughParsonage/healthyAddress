
expect_error(unique_Postcodes(""), "type")
x <- c(800L, 2444L, 3053L, 3053L, 2444L, 7470L)
expect_equal(unique_Postcodes(x),
             sort(unique(x)))

x <- c(x, NA_integer_)
expect_equal(unique_Postcodes(x),
             sort(unique(x)))




