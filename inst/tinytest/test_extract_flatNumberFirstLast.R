
ans1 <- extract_flatNumberFirstLast("712/108-110 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans1[[1]], 712)
expect_equal(ans1[[2]], 108)
expect_equal(ans1[[3]], 110)


ans2 <- extract_flatNumberFirstLast("UNIT 712 108-110 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans2[[1]], 712)
expect_equal(ans2[[2]], 108)
expect_equal(ans2[[3]], 110)

ans3 <- extract_flatNumberFirstLast("UNIT 712 108 FLINDERS STREET MELBOURNE VIC 3004")
expect_equal(ans3[[1]], 712)
expect_equal(ans3[[2]], 108)
