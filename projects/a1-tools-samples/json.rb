require "json"

ha = {}
10000.times do |i|
  ha["column-#{i}"] = {}
  100.times do |j|
    ha["column-#{i}"]["child-#{j}"] = rand(65536)
  end
end

str = JSON.dump ha
puts str.size
