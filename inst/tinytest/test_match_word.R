library(healthyAddress)
expect_equal(match_word("ABC STREET XYZ ABC", c("XY", "STREET", "ROAD")), 2L)
