##
## FirstGem Test
##

assert("FirstGem#hello") do
  t = FirstGem.new "hello"
  assert_equal("hello", t.hello)
end

assert("FirstGem#bye") do
  t = FirstGem.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("FirstGem.hi") do
  assert_equal("hi!!", FirstGem.hi)
end
