
ans <- extract_flatNumberFirstLast("712/108-110 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans[[1]], 712)
expect_equal(ans[[2]], 108)
expect_equal(ans[[3]], 110)

ans <- extract_flatNumberFirstLast("UNIT 712 108-110 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans[[1]], 712)
expect_equal(ans[[2]], 108)
expect_equal(ans[[3]], 110)

ans <- extract_flatNumberFirstLast("UNIT 712 108 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans[[1]], 712)
expect_equal(ans[[2]], 108)

ans <- extract_flatNumberFirstLast("G712 108 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans[[1]], 712)
expect_equal(ans[[2]], 108)

ans <- extract_flatNumberFirstLast("G 712 108 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans[[1]], 712)
expect_equal(ans[[2]], 108)

ans <- extract_flatNumberFirstLast("2/18A MULGARA LOOP, THROSBY ACT 2914")


