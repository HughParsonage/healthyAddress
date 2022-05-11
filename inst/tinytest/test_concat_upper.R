library(tinytest)

up0 <- function(...) toupper(paste(..., sep = ", "))
expect_equal(concat_upper("foo", "a"), up0("foo", "a"))
expect_equal(concat_upper(LETTERS, "a"), up0(LETTERS, "a"))
expect_equal(concat_upper(letters, "a"), up0(letters, "a"))
expect_equal(concat_upper(letters, "foo", "ab"), up0(letters, "foo", "ab"))
expect_equal(concat_upper(letters, letters, "ab"), up0(letters, letters, "ab"))
expect_equal(concat_upper(letters, letters, letters), up0(letters, letters, letters))
