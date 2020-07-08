# mruby-unsafe_code   [![Build Status](https://travis-ci.org/udzura/mruby-unsafe_code.svg?branch=master)](https://travis-ci.org/udzura/mruby-unsafe_code)
UnsafeCode class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-unsafe_code'
end
```
## example
```ruby
p UnsafeCode.hi
#=> "hi!!"
t = UnsafeCode.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
