MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'
  conf.enable_test
  conf.cc.flags << '-fPIC' # + ' -g3 -Wall -Werror-implicit-function-declaration'
  #conf.linker.flags << '-fPIC -g3 -Wall -Werror-implicit-function-declaration'
  # conf.gem ...

  if ENV['DEBUG'] == 'true'
    conf.enable_debug
    conf.cc.defines = %w(MRB_ENABLE_DEBUG_HOOK)
    conf.gem core: 'mruby-bin-debugger'
  end
end
