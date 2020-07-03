MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.cc.flags << '-fPIC'
end

