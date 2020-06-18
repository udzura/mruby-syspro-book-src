##
## FileStat Test
##

assert("FileStat#hello") do
  t = FileStat.new "hello"
  assert_equal("hello", t.hello)
end

assert("FileStat#bye") do
  t = FileStat.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("FileStat.hi") do
  assert_equal("hi!!", FileStat.hi)
end
