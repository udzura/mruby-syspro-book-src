##
## SampleDebug Test
##

assert("SampleDebug#hello") do
  t = SampleDebug.new "hello"
  assert_equal("hello", t.hello)
end

assert("SampleDebug#bye") do
  t = SampleDebug.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("SampleDebug.hi") do
  assert_equal("hi!!", SampleDebug.hi)
end
