library(tinytest)
library(hutilsc)

expect_equal(do_EncodeStreet(c("RD", "ROAD")),
             chmatch(c("ROAD", "ROAD"), .permitted_street_type_ord()))


expect_equal(healthyAddress:::Extract2_("3 TURNER STREET 3025", 1:3, 3023:3025, rep("STREET", 3), rep("TURNER", 3), 1:3),
             3L)

