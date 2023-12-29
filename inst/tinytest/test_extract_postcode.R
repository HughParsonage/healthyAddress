library(tinytest)
library(healthyAddress)

expect_equal(extract_postcode("PORT MACQ 2444"), 2444L)
expect_equal(extract_postcode("7000 FLINDERS ST, MELBOURNE VIC 3004"), 3004L)
expect_equal(extract_postcode("3047, BROADMEADOWS"), 3047L)
