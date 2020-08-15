node    = `uname -n`.chomp
os      = `uname -s`.chomp
version = `uname -r`.chomp
puts "Hello, #{node}!\nYou are on #{os}\nversion #{version}"

