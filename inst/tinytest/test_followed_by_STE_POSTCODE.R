
fbsp <- healthyAddress:::followed_by_STE_POSTCODE
expect_true(fbsp(0L, "MELBOURNE VIC 3000"))
expect_true(fbsp(1L, "A DARWIN NT 0800"))
expect_true(fbsp(1L, "A SYDNEY NSW 2000"))
expect_true(fbsp(1L, "A BRISBANE, QLD 4000"))
expect_true(fbsp(1L, "A ADELAIDE, SA 5000"))
expect_true(fbsp(1L, "A PERTH, WA 6000"))
expect_true(fbsp(1L, "A HOBART, TAS 7000"))
expect_false(fbsp(1L, "MELBOURNE VIC 3000"))
