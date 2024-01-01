library(tinytest)
the__ <- healthyAddress:::the__
get_the_XXX <- healthyAddress:::get_the_XXX
expect_equal(the__("ABC"), 0)
expect_equal(the__("THE"), 0)
expect_equal(healthyAddress:::the__("THE GAP"), match("GAP", get_the_XXX(), nomatch = 0L))
