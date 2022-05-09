ans <- standard_address2("UNIT 47 LEVEL 1 174-175 ESPLANADE WEST PORT MELBOURNE 3207")
expect_equal(ans$NUMBER_FIRST, 174L)  # not 1
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, HashStreetName("ESPLANADE WEST"))
