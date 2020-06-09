##
## BinMps Test
##

assert("BinMps#hello") do
  t = BinMps.new "hello"
  assert_equal("hello", t.hello)
end

assert("BinMps#bye") do
  t = BinMps.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("BinMps.hi") do
  assert_equal("hi!!", BinMps.hi)
end
