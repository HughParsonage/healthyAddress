

expect_equal(healthyAddress:::NumberSuffix2Raw("A"),
             charToRaw('A'))

expect_equal(healthyAddress:::get_suffix("2/18B MULGARA LOOP, THROSBY ACT 2914"),
             healthyAddress:::NumberSuffix2Raw('B'))
expect_equal(healthyAddress:::get_suffix(" "), as.raw(0))
expect_equal(NumberSuffixFromRaw(NumberSuffix2Raw("A")))
