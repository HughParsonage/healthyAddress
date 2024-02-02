library(tinytest)
# Placeholder with simple test
expect_equal(1 + 1, 2)

expect_null(healthyAddress:::static_assert())

library(healthyAddress)
NumberSuffix2Raw <- healthyAddress:::NumberSuffix2Raw


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
expect_equal(ans$NUMBER_LAST, 5)

# ans <- standardize_address("11 THE ESPLANADE Narre Warren South VIC 3805")
# expect_equal(ans$STREET_NAME, "THE ESPLANADE")

ans <- standardize_address(c("15 CANBERRA AVENUE FORREST ACT 2609",
                             "1 BEALE CRESCENT DEAKIN ACT 2600",
                             "116 MUGGA LANE Symonston ACT 2609",
                             "1 BIDWILL CLOSE YARRALUMLA ACT 2600",
                             "5/1 GEILS COURT DEAKING ACT 2600",
                             "1/3 OUTLOOK RISE QLD 4553"))
expect_equal(ans$STREET_TYPE,
             c("AVENUE", "CRESCENT", "LANE", "CLOSE", "COURT", "RISE"))

ans <- standardize_address(c("15 CANBERRA AVENUE FORREST ACT 2609",
                             "1 BEALE CRESCENT DEAKIN ACT 2600",
                             "116 MUGGA LANE Symonston ACT 2609",
                             "1 BIDWILL CLOSE YARRALUMLA ACT 2600",
                             "5/1 GEILS COURT DEAKING ACT 2600",
                             "BIG4 SHEPPARTON PARKLANDS 7835 GOULBURN VALLEY HIGHWAY KIALLA VIC 3631",
                             "1/3 OUTLOOK RISE QLD 4553"),
                           integer_StreetType = TRUE,
                           hash_StreetName = TRUE)
expect_equal(ans$STREET_TYPE,
             match(c("AVENUE", "CRESCENT", "LANE", "CLOSE", "COURT", "HIGHWAY", "RISE"),
                   .permitted_street_type_ord()))


ans <- standardize_address("1 PARK ST, ST KILDA WEST VIC 3182")
expect_equal(ans$STREET_NAME, "PARK")
ans <- standardize_address("1 PARK ST ST KILDA WEST VIC 3182")
expect_equal(ans$STREET_NAME, "PARK")
ans <- standard_address2("99 PRINCE OF WALES AVE, MILL PARK VIC 3005")
ans <- standard_address2("99 PRINCE OF WALES CT, MILL PARK VIC 3005")
ans <- standard_address2("77 PARK ST ST KILDA WEST VIC 3184")
expect_equal(ans$H0, HashStreetName("PARK"))
ans <- standard_address2("1/2 BRAND ST ST LEONARDS 2064")
ans <- standard_address2("46 ABBOTT RD ST LEONARDS 2064")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))
ans <- standard_address2("46 ABBOTT ROAD ST LEONARDS 2064")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))

ans <- standard_address2("UNIT G2 5 OLIVE YORK WAY BRUNSWICK WEST VICTORIA 3055")
expect_equal(ans$FLAT_NUMBER, 2L)
expect_equal(ans$NUMBER_FIRST, 5L)
expect_equal(ans$STREET_TYPE_CODE, 11L)

ans <- standard_address2(toupper("Hillside Court Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
expect_equal(ans$STREET_TYPE_CODE, match("STREET", .permitted_street_type_ord()))
expect_equal(ans$NUMBER_FIRST, 155L)
# ans <- standard_address2(toupper("Room 5 Hillside Court Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
ans <- standard_address2(toupper("Room 5 Hillside Rooming House 155-159 Hoddle St, Richmond VIC 3121"))
expect_equal(ans$STREET_TYPE_CODE, match("STREET", .permitted_street_type_ord()))
expect_equal(ans$NUMBER_FIRST, 155L)
expect_equal(ans$FLAT_NUMBER, 5L)

ans <- standard_address2(toupper("365-370 High Street Road, Mount Waverley VIC 3149"))
expect_equal(ans$STREET_TYPE_CODE, 1L)
ans <- standard_address2("47/174 ESPLANADE EAST PORT MELBOURNE 3207")
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, 1418946723L)  # ESPLANADE EAST
ans <- standard_address2("47/174 ESPLANADE WEST PORT MELBOURNE 3207")
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, HashStreetName("ESPLANADE WEST"))

ans <- standard_address2("UNIT 47 LEVEL 1 174-175 ESPLANADE WEST PORT MELBOURNE 3207")
expect_equal(ans$NUMBER_FIRST, 174L)  # not 1
expect_equal(ans$STREET_TYPE_CODE, 0L)
expect_equal(ans$H0, HashStreetName("ESPLANADE WEST"))

ans <- standard_address2("George Street, MAFFRA VIC 3860")
expect_equal(ans$NUMBER_FIRST, 0L)
expect_equal(ans$STREET_TYPE_CODE, 2L)
expect_equal(ans$H0, HashStreetName("GEORGE"))

ans <- standard_address2("FLINDERS ST MELBOURNE VIC 3000")
expect_equal(ans$STREET_TYPE_CODE, 2L)
expect_equal(ans$H0, HashStreetName("FLINDERS"))

ans <- standard_address2("U 711 L 7 108 FLINDERS ST MELBOURNE VIC 3004")
expect_equal(ans$FLAT_NUMBER, 711)
expect_equal(ans$NUMBER_FIRST, 108)

ans <- standard_address3("U 711 L 7 108 FLINDERS ST", "MELBOURNE VIC 3004")
expect_equal(ans$FLAT_NUMBER, 711)
expect_equal(ans$NUMBER_FIRST, 108)
expect_equal(ans$POSTCODE, 3004)

# additional coverage
ans <- standard_address3("U 7011 L 70 108 FLINDERS ST", "MELBOURNE VIC 3004")
expect_equal(ans$FLAT_NUMBER, 7011)
expect_equal(ans$NUMBER_FIRST, 108)
expect_equal(ans$POSTCODE, 3004)

ans <- standard_address3("2/6 THE ESPLANADE", "PERTH WA 6000")
expect_equal(ans$FLAT_NUMBER, 2)
expect_equal(ans$NUMBER_FIRST, 6)
expect_equal(ans$H0, HashStreetName("THE ESPLANADE"))

ans <- standard_address3("1A THE ESPLANADE", "BOTANY NSW 2019")
expect_equal(ans$FLAT_NUMBER, 0)
expect_equal(ans$NUMBER_FIRST, 1)
expect_equal(ans$NUMBER_SUFFIX, healthyAddress:::NumberSuffix2Raw("A"))
expect_equal(ans$H0, HashStreetName("THE ESPLANADE"))
expect_equal(ans$POSTCODE, 2019)

ans <- standard_address3(" ", "BOTANY NSW 2019")
expect_equal(is.na(ans$NUMBER_FIRST), TRUE)
expect_equal(ans$H0, 0L)
expect_equal(ans$POSTCODE, 2019)

ans <- standard_address2("1/59 THE RIGHI, SOUTH YARRA, VIC, 3141")
expect_equal(ans$FLAT_NUMBER, 1L)
expect_equal(ans$NUMBER_FIRST, 59L)
expect_equal(ans$H0, HashStreetName("THE RIGHI"))
expect_equal(ans$STREET_TYPE_CODE, 0L)

ans <- standard_address2("19 THE PARKS, HILLSIDE, VIC, 3037")
expect_equal(ans$FLAT_NUMBER, 0L)
expect_equal(ans$NUMBER_FIRST, 19L)
expect_equal(ans$H0, HashStreetName("THE PARKS"))
expect_equal(ans$STREET_TYPE_CODE, 0L)

ans <- standard_address2("14 DAINTREE RISE, ST HELENA, VIC, 3088")
expect_equal(ans$H0, HashStreetName("DAINTREE"))
expect_equal(ans$STREET_TYPE_CODE, 22L)

ans <- standard_address2("51 BASS MEADOWS BOULEVARD, ST ANDREWS BEACH, VIC, 3941")
expect_equal(ans$H0, HashStreetName("BASS MEADOWS"))
expect_equal(ans$STREET_TYPE_CODE, 20L)

# UNITS should not trigger
ans <- standard_address2("NANGATTA UNITS KALKEE 206 HIGH STREET BELMONT VIC 3216")
expect_equal(ans$FLAT_NUMBER, 0L)
expect_equal(ans$NUMBER_FIRST, 206L)

ans <- standard_address2("63 THE PARKWAY PATTERSON LAKES VIC 3197")
expect_equal(ans$H0, HashStreetName("THE PARKWAY"))

ans <- standard_address2("63 THE PKWY PATTERSON LAKES VIC 3197")
expect_equal(ans$H0, HashStreetName("THE PARKWAY"))

ans <- standard_address2("63 THE PKWY, PAKENHAM VIC 3810")
expect_equal(ans$H0, HashStreetName("THE PARKWAY"))

# THE SPRINGS != THE SPRINGS CLOSE
ans <- standard_address2("1 THE SPRINGS CLOSE, NARRE WARREN SOUTH, VIC, 3805")
expect_equal(ans$H0, HashStreetName("THE SPRINGS CLOSE"))

ans <- standard_address2("3 LOWER TERRACE CRESCENT, NOBLE PARK NORTH, VIC 3174")
expect_equal(ans$H0, HashStreetName("LOWER TERRACE"))

ans <- standard_address2("1D/66-68 ALLARA STREET CANBERRA CITY ACT 2601")
expect_equal(ans$NUMBER_FIRST, 66L)

# Not reasonable to detect
# ans <- standard_address2("1d 66/68 ALLARA STREET CANBERRA CITY ACT 2601")
# expect_equal(ans$NUMBER_FIRST, 66L)

ans <- standard_address2("1a/18 Abbott St, Abbotsford Vic 3067")
# expect_equal(ans$NUMBER_SUFFIX, NumberSuffix2Raw("A"))  # nope! it's the number_first_suffix,
expect_equal(ans$NUMBER_FIRST, 18)

ans <- standard_address2("1 KINGS DOM, CAROLINE SPRINGS VIC 3023")
expect_equal(ans$H0, HashStreetName("KINGS"))
expect_equal(ans$STREET_TYPE_CODE, match("DOMAIN", .permitted_street_type_ord()))

ans <- standard_address2("1 Dom Ct, Narangba QLD 4504")
expect_equal(ans$H0, HashStreetName("DOM"))

ans <- standard_address2("1 ATLANTIC BR, WANDINA, WA, 6530")
expect_equal(ans$STREET_TYPE_CODE, match("BRACE", .permitted_street_type_ord()))

ans <- standard_address2("108A/441 LONSDALE STREET, MELBOURNE, VIC 3000")
expect_equal(ans$FLAT_NUMBER, 108L)

ans <- standard_address2("6 CORYMBIA PROM, PAKENHAM VIC 3810")
expect_equal(ans$STREET_TYPE_CODE, match("PROMENADE", .permitted_street_type_ord()))

# UNIT trips ST KILDA ROAD logic
ans <- standard_address2("UNIT 3053 368 ST KILDA ROAD MELBOURNE VIC 3004")
expect_equal(ans$H0, HashStreetName("ST KILDA"))

ans <- standard_address2("45 EVERGREEN CCT, OCEAN GROVE, VIC, 3226")
expect_equal(ans$H0, HashStreetName("EVERGREEN"))

ans <- standard_address2("UNIT 2 125 PASCOE VALE ROAD MOONEE PONDS VIC 3039")
expect_equal(ans$H0, HashStreetName("PASCOE VALE"))

# FLOOR numbers must not form part of the address
ans <- standard_address2("APARTMENT 3 FLOOR 99 31 ROSANNA ROAD HEIDELBERG VIC 3084")
expect_equal(ans$NUMBER_FIRST, 31L)

ans <- standard_address2("LEVEL 1 197-199 KING STREET MELBOURNE VIC 3000")
expect_equal(ans$NUMBER_FIRST, 197L)

# If G or U are found before a digit, previously it was determined not to be
# a flat if the next character was not a digit, whereas the correct logic is
# that if G or U are followed by a digit then it is a flat.
ans <- standard_address2("FLOWERY GARDENS UNIT 1 23 KING STREET MELBOURNE VIC 3000")
expect_equal(ans$FLAT_NUMBER, 1L)

# SHOP is a valid FLAT NUMBER designation
ans <- standard_address2("SHOP 101 850 WHITEHORSE ROAD BOX HILL VIC 3128")
expect_equal(ans$FLAT_NUMBER, 101L)

ans <- standard_address2("CARSPACE 3 4 GRANT STREET OAKLEIGH VIC 3166")
expect_equal(ans$FLAT_NUMBER, 3L)
expect_equal(ans$NUMBER_FIRST, 4L)

# Saints with multiple nchar
ans <- standard_address2("ST VINCENTS VILLAGE UNIT 1 250 ST AIDANS ROAD KENNINGTON VIC 3550")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))

# Street type not The Strand
ans <- standard_address2("THE STRAND MELBOURNE 222-260 ELIZABETH STREET MELBOURNE VIC 3000")
expect_equal(ans$STREET_TYPE_CODE, match("STREET", .permitted_street_type_ord()))

ans <- standard_address2('9 GARDEN GROVE DRIVE MILL PARK VIC 3082')
expect_equal(ans$STREET_TYPE_CODE, match("DRIVE", .permitted_street_type_ord()))

ans <- standard_address2("50 PRINCE OF WALES AVENUE, MILL PARK VIC 3082")
expect_equal(ans$H0, HashStreetName("PRINCE OF WALES"))

# preceding space
ans <- standard_address2("  50 PRINCE OF WALES AVENUE, MILL PARK VIC 3082")
expect_equal(ans$NUMBER_FIRST, 50)
expect_equal(ans$H0, HashStreetName("PRINCE OF WALES"))

# Many words but valid
ans <- standard_address2("BRANDON PARK CORPORATE CENTRE SUITE 4 LEVEL 1 2 BRANDON PARK DRIVE WHEELERS HILL VIC 3150")
expect_equal(ans$FLAT_NUMBER, 4L)
expect_equal(ans$NUMBER_FIRST, 2L)
expect_equal(ans$NUMBER_LAST, 0L)
expect_equal(ans$POSTCODE, 3150L)
expect_equal(ans$H0, HashStreetName("BRANDON PARK"))

ans <- standard_address2("Director, Governance Section, Department of Infrastructure, Transport, Regional Development, Communications and the Arts 111 Alinga St Canberra Australian Capital Territory 2601 Australia")
expect_equal(ans$POSTCODE, 2601)
expect_equal(ans$H0, HashStreetName("ALINGA"))
expect_equal(ans$NUMBER_FIRST, 111)



# No address parsable
na_or_zero <- function(x) is.na(x) | x == 0L
ans <- standard_address2(NA_character_)
expect_true(na_or_zero(ans$NUMBER_FIRST))

ans <- standard_address2("SYDNEY NSW 2000")
expect_true(is.na(ans$NUMBER_FIRST) || ans$NUMBER_FIRST == 0)

ans <- standard_address2("Latitude: -35.5, Longitude = 150")
expect_true(na_or_zero(ans$NUMBER_FIRST))
expect_true(na_or_zero(ans$FLAT_NUMBER))
expect_true(na_or_zero(ans$NUMBER_LAST))

ans <- standard_address2("Flat 0412 345 678")
expect_true(na_or_zero(ans$NUMBER_FIRST))
expect_true(na_or_zero(ans$FLAT_NUMBER))
expect_true(na_or_zero(ans$NUMBER_LAST))

## trie
standard_address_postcode_trie <- healthyAddress:::standard_address_postcode_trie
ans <- standard_address_postcode_trie("UNIT 2 125 PASCOE VALE ROAD MOONEE PONDS VIC 3039")
expect_equal(ans$STREET_TYPE_CODE, match("ROAD", .permitted_street_type_ord()))
expect_equal(ans$STREET_NAME, "PASCOE VALE")

ans <- standard_address_postcode_trie("Director, Governance Section, Department of Infrastructure, Transport, Regional Development, Communications and the Arts 111 Alinga St Canberra Australian Capital Territory 2601 Australia")
expect_equal(ans$POSTCODE, 2601)
expect_equal(ans$STREET_NAME, "ALINGA")
expect_equal(ans$NUMBER_FIRST, 111)

ans <- standard_address_postcode_trie("")
expect_true(na_or_zero(ans$NUMBER_FIRST))

ans <- standardize_address(c("4/13 CRESCENT STREET, NOBLE PARK, VIC, 3174",
                             "35 OLD FOREST ROAD, THE BASIN, VIC, 3154",
                             "16/21-31 ST PHILLIP STREET, BRUNSWICK EAST, VIC, 3057",
                             "23 LOOKOUT RISE, MACLEOD, VIC, 3085",
                             "38 ST VINCENT STREET, ALBERT PARK, VIC, 3206",
                             "9 SANDSTONE ISLAND CIRCLE, BITTERN, VIC, 3918",
                             "28 ST MITCHELL CIRCUIT, MORNINGTON, VIC, 3931",
                             "23 MERIDIAN ACCESS ROAD, WALPEUP, VIC, 3507",
                             "1/17 ST LEONARDS ROAD, HEALESVILLE, VIC, 3777",
                             "18 ST NINIANS ROAD, BRIGHTON, VIC, 3186"))

expect_equal(ans$STREET_NAME,
             c("CRESCENT",
               "OLD FOREST",
               "ST PHILLIP",
               "LOOKOUT",
               "ST VINCENT",
               "SANDSTONE ISLAND",
               "ST MITCHELL",
               "MERIDIAN ACCESS",
               "ST LEONARDS",
               "ST NINIANS"))

ans <- standardize_address(c("4/13 CRESCENT STREET, NOBLE PARK, VIC, 3174",
                             "35 OLD FOREST ROAD, THE BASIN, VIC, 3154",
                             "16/21-31 ST PHILLIP STREET, BRUNSWICK EAST, VIC, 3057",
                             "23 LOOKOUT RISE, MACLEOD, VIC, 3085",
                             "38 ST VINCENT STREET, ALBERT PARK, VIC, 3206",
                             "9 SANDSTONE ISLAND CIRCLE, BITTERN, VIC, 3918",
                             "28 ST MITCHELL CIRCUIT, MORNINGTON, VIC, 3931",
                             "23 MERIDIAN ACCESS ROAD, WALPEUP, VIC, 3507",
                             "1/17 ST LEONARDS ROAD, HEALESVILLE, VIC, 3777",
                             "18 ST NINIANS ROAD, BRIGHTON, VIC, 3186"),
                           hash_StreetName = TRUE)

expect_equal(ans$H0,
             HashStreetName(c("CRESCENT",
                              "OLD FOREST",
                              "ST PHILLIP",
                              "LOOKOUT",
                              "ST VINCENT",
                              "SANDSTONE ISLAND",
                              "ST MITCHELL",
                              "MERIDIAN ACCESS",
                              "ST LEONARDS",
                              "ST NINIANS")))

ans <- standardize_address('1408/170 The Esplanade St Kilda VIC 3182')
expect_equal(ans$STREET_NAME, "THE ESPLANADE")
expect_equal(ans$FLAT_NUMBER, 1408L)
expect_equal(ans$NUMBER_FIRST, 170)

ans <- standardize_address("13 APOLLONIAN VALE, GYMPIE, QLD 4570")
expect_equal(ans$STREET_NAME, "APOLLONIAN")
expect_equal(ans$STREET_TYPE, "VALE")
ans <- standard_address2("13 APOLLONIAN VALE, GYMPIE, QLD 4570")
expect_equal(ans$H0, HashStreetName("APOLLONIAN"))
expect_equal(ans$STREET_TYPE_CODE, match("VALE", .permitted_street_type_ord()))

ans <- standardize_address("3/18 Bungan St Mona Vale NSW 2103")
expect_equal(ans$STREET_NAME, "BUNGAN")
ans <- standard_address2("3/18 Bungan St Mona Vale NSW 2103")
expect_equal(ans$H0, HashStreetName("BUNGAN"))

ans <- standardize_address("L5 500/120 FLINDERS ST MELB VIC 3004")
expect_equal(ans$STREET_NAME, "FLINDERS")
expect_equal(ans$FLAT_NUMBER, 500L)
expect_equal(ans$NUMBER_FIRST, 120L)

ans <- standardize_address("L5 500/120 FLINDERS ST MELB VIC 3004", hash_StreetName = TRUE)
expect_equal(ans$H0, HashStreetName("FLINDERS"))
expect_equal(ans$FLAT_NUMBER, 500L)
expect_equal(ans$NUMBER_FIRST, 120L)

ans <- standardize_address("50 UNIT STREET FICTION 1999")
expect_equal(ans$POSTCODE, -1)

