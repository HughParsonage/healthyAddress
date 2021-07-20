FindSentence <- healthyAddress:::FindSentence

expect_equal(FindSentence("abc def", "abc", "def"), 1)
expect_equal(FindSentence("abc def", "bc", "def"), NA_integer_)
expect_equal(FindSentence("abc def", "abc", "df"), NA_integer_)
expect_equal(FindSentence("abc gdef", "abc", "def"), NA_integer_)
expect_equal(FindSentence("foo abc gdef", "abc", "def"), NA_integer_)
expect_equal(FindSentence("foo abc def", "abc", "def"), 1L)
expect_equal(FindSentence("foo abc def", "abc", "def"), 1L)
expect_equal(FindSentence("foo abc def", c("abc", "def"), c("def", "def")), 1L)
expect_equal(FindSentence("foo abc def", c("abcd", "abc"), c("def", "def")), 2L)


