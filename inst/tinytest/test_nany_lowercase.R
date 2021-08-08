
expect_true(nany_lowercase("ABC"))
expect_true(nany_lowercase("712/109 FLINDERS STREET, MELBOURNE VIC 3044"))
expect_false(nany_lowercase("712/109 flinders STREET, MELBOURNE VIC 3044"))
expect_error(nany_lowercase(integer(1)))
