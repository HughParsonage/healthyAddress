test_wd <- healthyAddress:::test_WordData

my_lhs <- function(x) {
  z
}

expect_equal(test_wd("one two three"), 3L)
expect_equal(test_wd("one two three", r = 1L), c(0L, 4L, 8L, integer(13)))
expect_equal(test_wd("one two three", r = 2L), c(3L, 7L, 13L, integer(13)))

