
expect_equal(HashStreetName(c("BRUXNER", "AGAR STEPS")),
             c(1788253569L, 2122551793L))
expect_equal(HashStreetName(c("BRUXNER", "AGAR STEPS", NA)),
             c(1788253569L, 2122551793L, NA))
expect_error(HashStreetName(1L), "integer")

# expect_equal(unHashStreetName(HashStreetName("THE PARKWAY")), "THE PARKWAY")
