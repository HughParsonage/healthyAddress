library(tinytest)
z <- c(intToUtf8(1:128), NA, "a", "", strrep(letters, 32000))
expect_equal(toupper_basic(z), toupper(z))
expect_warning(toupper_basic(strrep("a", 33e3)))
