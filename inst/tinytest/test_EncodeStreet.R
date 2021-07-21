library(tinytest)
library(hutilsc)
do_EncodeStreet <- hutilsc:::do_EncodeStreet

expect_equal(do_EncodeStreet(c("RD", "ROAD")),
             chmatch(c("ROAD", "ROAD"), .permitted_street_type_ord()))

