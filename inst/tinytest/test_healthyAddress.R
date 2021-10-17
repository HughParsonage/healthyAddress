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
expect_true(TRUE)
match_StreetType_Line1 <- healthyAddress:::match_StreetType_Line1
ans1 <- match_StreetType_Line1("UNIT 24 125 TURNER ST", m = 0L)
ans1 <- match_StreetType_Line1("UNIT 24 125 TURNER ST", m = 2L)

ans <- standardize_address("UNIT 24 125 TURNER ST", "ABBOTSFORD VIC 3067")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_false(is.na(ans$POSTCODE))

ans <- standardize_address("UNIT 24 125 TURNER STREET, ABBOTSFORD VIC 3067")
expect_equal(ans$FLAT_NUMBER, 24)
expect_equal(ans$NUMBER_FIRST, 125)
expect_equal(toupper(ans$STREET_NAME), "TURNER")
expect_equal(toupper(ans$STREET_TYPE), "STREET")
expect_false(is.na(ans$POSTCODE))
expect_equal(ans$POSTCODE, 3067)

ans <- standardize_address("10 MALVINA PLACE CARLTON VIC 3053", return.type = "integer")
# expect_equal(ans, 10108234L)

ans <- standardize_address("99 ROBBINS WAY, HAMPTON PARK, VIC, 3976")
expect_equal(ans$NUMBER_FIRST, 99)
expect_equal(ans$STREET_NAME, "ROBBINS")
expect_equal(ans$STREET_TYPE, "WAY")

ans <- standardize_address("41-55 Hamilton Hume Parade, Craigieburn, Vic 3064")
expect_equal(ans$STREET_NAME, "HAMILTON HUME")

ans <- standardize_address("C/-1-5 ANDERSONS CREEK RD",  "DONCASTER EAST VIC 3109")
expect_equal(ans$STREET_NAME, "ANDERSONS CREEK")

# ans <- standardize_address("11 THE ESPLANADE Narre Warren South VIC 3805")
# expect_equal(ans$STREET_NAME, "THE ESPLANADE")

ans <- standardize_address(c("15 CANBERRA AVENUE FORREST ACT 2609",
                             "1 BEALE CRESCENT DEAKIN ACT 2600",
                             "116 MUGGA LANE Symonston ACT 2609",
                             "1 BIDWILL CLOSE YARRALUMLA ACT 2600",
                             "5/1 GEILS COURT DEAKING ACT 2600"))
expect_equal(ans$STREET_TYPE,
             c("AVENUE", "CRESCENT", "LANE", "CLOSE", "COURT"))


ans <- standardize_address("1 PARK ST, ST KILDA WEST VIC 3182")
expect_equal(ans$STREET_NAME, "PARK")
ans <- standardize_address("1 PARK ST ST KILDA WEST VIC 3182")
expect_equal(ans$STREET_NAME, "PARK")
ans <- healthyAddress:::Do_standard_address("99 PRINCE OF WALES AVE, MILL PARK VIC 3005")
ans <- healthyAddress:::Do_standard_address("99 PRINCE OF WALES CT, MILL PARK VIC 3005")
ans <- healthyAddress:::Do_standard_address("77 PARK ST ST KILDA WEST VIC 3184")
expect_equal(ans$H0, HashStreetName("PARK"))
ans <- healthyAddress:::Do_standard_address("1/2 BRAND ST ST LEONARDS 2064")
ans <- healthyAddress:::Do_standard_address("46 ABBOTT RD ST LEONARDS 2064")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))
ans <- healthyAddress:::Do_standard_address("46 ABBOTT ROAD ST LEONARDS 2064")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))

ans <- healthyAddress:::Do_standard_address("UNIT G2 5 OLIVE YORK WAY BRUNSWICK WEST VICTORIA 3055")
expect_equal(ans$FLAT_NUMBER, 2L)
expect_equal(ans$NUMBER_FIRST, 5L)
expect_equal(ans$STREET_TYPE_CODE, 11L)

ans <- healthyAddress:::Do_standard_address(toupper("Hillside Court Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
expect_equal(ans$STREET_TYPE_CODE, match("STREET", .permitted_street_type_ord()))
expect_equal(ans$NUMBER_FIRST, 155L)
# ans <- healthyAddress:::Do_standard_address(toupper("Room 5 Hillside Court Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
ans <- healthyAddress:::Do_standard_address(toupper("Room 5 Hillside Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
expect_equal(ans$STREET_TYPE_CODE, match("STREET", .permitted_street_type_ord()))
expect_equal(ans$NUMBER_FIRST, 155L)
expect_equal(ans$FLAT_NUMBER, 5L)

ans <- healthyAddress:::Do_standard_address(toupper("365-370 High Street Road, Mount Waverley VIC 3149"))
expect_equal(ans$STREET_TYPE_CODE, 1L)
ans <- healthyAddress:::Do_standard_address("47/174 ESPLANADE EAST PORT MELBOURNE 3207")
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, 1418946723L)  # ESPLANADE EAST
ans <- healthyAddress:::Do_standard_address("47/174 ESPLANADE WEST PORT MELBOURNE 3207")
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, HashStreetName("ESPLANADE WEST"))

ans <- healthyAddress:::Do_standard_address("UNIT 47 LEVEL 1 174-175 ESPLANADE WEST PORT MELBOURNE 3207")
expect_equal(ans$NUMBER_FIRST, 174L)  # not 1
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, HashStreetName("ESPLANADE WEST"))

