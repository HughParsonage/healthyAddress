library(tinytest)
# Placeholder with simple test
expect_equal(1 + 1, 2)

library(healthyAddress)

ans <- standardize_address("4/110-120 Rupert St, Victoria 3012")
names(ans) <- toupper(names(ans))
expect_equal(ans$FLAT_NUMBER, 4)
expect_equal(ans$NUMBER_FIRST, 110)
expect_equal(ans$NUMBER_LAST, 120)
expect_equal(toupper(ans$STREET_NAME), "RUPERT")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_equal(ans$POSTCODE, 3012)

ans <- standardize_address("UNIT 24 125 TURNER ST", "ABBOTSFORD VIC 3067")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_true(is.na(ans$POSTCODE))

ans <- standardize_address("UNIT 24 125 TURNER STREET, ABBOTSFORD VIC 3067")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_false(is.na(ans$POSTCODE))
expect_equal(ans$POSTCODE, 3067)

ans <- standardize_address("10 MALVINA PLACE CARLTON VIC 3053", return.type = "integer")
expect_equal(ans, 10108234L)

ans <- standardize_address("99 ROBBINS WAY, HAMPTON PARK, VIC, 3976")
expect_equal(ans$NUMBER_FIRST, 99)
expect_equal(ans$STREET_NAME, "ROBBINS")
expect_equal(ans$STREET_TYPE, "WAY")







