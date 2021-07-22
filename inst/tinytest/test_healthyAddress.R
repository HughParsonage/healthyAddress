library(tinytest)
# Placeholder with simple test
expect_equal(1 + 1, 2)

library(healthyAddress)
if (FALSE) {
ans <- extract_standard_address("4/110-120 Rupert St")
names(ans) <- toupper(names(ans))
expect_equal(ans$FLAT_NUMBER, 4)
expect_equal(ans$NUMBER_FIRST, 110)
expect_equal(ans$NUMBER_LAST, 120)
expect_equal(toupper(ans$STREET_NAME), "RUPERT")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_true(is.na(ans$POSTCODE))

ans <- extract_standard_address("UNIT 24 125 TURNER ST")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_true(is.na(ans$POSTCODE))

ans <- extract_standard_address("UNIT 24 125 TURNER STREET, ABBOTSFORD VIC 3067")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_false(is.na(ans$POSTCODE))
expect_equal(ans$POSTCODE, 3067)

}






