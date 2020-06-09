MRuby::Gem::Specification.new('mruby-bin-mps') do |spec|
  spec.bins = ['mps']
  spec.license = 'MIT'
  spec.authors = 'Uchio Kondo'

  spec.add_dependency 'mruby-io'
  spec.add_dependency 'mruby-errno'
end
