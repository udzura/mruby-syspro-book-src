MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.cc.flags << '-fPIC -O0 -g -fno-omit-frame-pointer'
end

