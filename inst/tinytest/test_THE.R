library(tinytest)
the__ <- healthyAddress:::the__
get_the_XXX <- healthyAddress:::get_the_XXX
expect_equal(the__("ABC"), 0)
expect_equal(the__("THE"), 0)
expect_equal(healthyAddress:::the__("THE GAP"), match("GAP", get_the_XXX(), nomatch = 0L))

expect_equal(the__(c("1/1 THE RIGHI SOUTH YARRA VIC 3000",
                     "2/2 THE OAKS THE GAP")))

expect_equal(the__("90 THE OLD STOCK RUN, SUNBURY, VIC, 3429"),
             match("OLD STOCK RUN", get_the_XXX(), nomatch = 0L))
