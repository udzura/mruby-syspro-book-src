# mruby-first_gem   [![Build Status](https://travis-ci.org/udzura/mruby-first_gem.svg?branch=master)](https://travis-ci.org/udzura/mruby-first_gem)
FirstGem class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-first_gem'
end
```
## example
```ruby
p FirstGem.hi
#=> "hi!!"
t = FirstGem.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
