##
## UnsafeCode Test
##

assert("UnsafeCode#hello") do
  t = UnsafeCode.new "hello"
  assert_equal("hello", t.hello)
end

assert("UnsafeCode#bye") do
  t = UnsafeCode.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("UnsafeCode.hi") do
  assert_equal("hi!!", UnsafeCode.hi)
end
