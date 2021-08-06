
x <- c(800L, 2444L, 3053L, 3053L, 2444L)
expect_equal(unique_Postcodes(x),
             sort(unique(x)))

