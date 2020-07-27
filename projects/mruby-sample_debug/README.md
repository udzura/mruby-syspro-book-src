# mruby-sample_debug   [![Build Status](https://travis-ci.org/udzura/mruby-sample_debug.svg?branch=master)](https://travis-ci.org/udzura/mruby-sample_debug)
SampleDebug class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'udzura/mruby-sample_debug'
end
```
## example
```ruby
p SampleDebug.hi
#=> "hi!!"
t = SampleDebug.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
