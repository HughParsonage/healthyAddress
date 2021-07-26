library(healthyAddress)

PST6 <- c("ROAD", "STREET", "COURT", "AVENUE", "PLACE", "LANE", "WEST")
expect_equal(match_word("ABC STREET XYZ ABC", c("XY", "STREET", "ROAD")), 2L)
expect_equal(match_word("UNIT 7812 108 FLINDERS STREET MELBOURNE VIC 3004", PST6), 2L)

# Don't detect WEST here (possibly too difficult)
expect_equal(match_word("UNIT 7812 WEST 108 FLINDERS STREET MELBOURNE VIC 3004", PST6), 2L)

expect_equal(match_StreetType("UNIT 7812 WEST 108 FLINDERS STREET MELBOURNE VIC 3004") %% 256L, 2L)
