##
## FirstC Test
##

assert("FirstC#hello") do
  t = FirstC.new "hello"
  assert_equal("hello", t.hello)
end

assert("FirstC#bye") do
  t = FirstC.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("FirstC.hi") do
  assert_equal("hi!!", FirstC.hi)
end
