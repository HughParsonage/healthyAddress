vic_poa <- c(3021L, 3084L, 3013L, 3147L, 3123L, 3070L, 3004L, 3250L, 3630L)

expect_equal(postcode2ste(vic_poa), 2L)
expect_equal(postcode2ste(vic_poa, result = "character"), "VIC")
exoect_equal(sort(postcode2ste(c(vic_poa, 2000L))), 1:2)
expect_equal(sort(postcode2ste(3644L)), 1:2)
expect_equal(postcode2ste(7468), 6L)
