# mruby-first_c   [![Build Status](https://travis-ci.org/udzura/mruby-first_c.svg?branch=master)](https://travis-ci.org/udzura/mruby-first_c)
FirstC class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-first_c'
end
```
## example
```ruby
p FirstC.hi
#=> "hi!!"
t = FirstC.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
