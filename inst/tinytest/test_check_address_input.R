library(tinytest)
cai <- healthyAddress:::check_address_input

expect_warning(cai("foo", 2L), "thin")
expect_warning(cai(toString(c(LETTERS, 2000:1999)), 2L), "valid postcode")
expect_error(cai(strrep("A0 ", 34), 2L), "34")
