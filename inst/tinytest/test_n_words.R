n_words <- healthyAddress:::n_words

expect_identical(n_words(character(0)), integer(0))
expect_equal(n_words(""), 0)
expect_equal(n_words(c(" ", "a", "ab cd", "DF/AB X Y Z")), c(0, 1, 2, 4))
