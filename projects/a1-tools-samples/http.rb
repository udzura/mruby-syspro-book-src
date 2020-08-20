require "net/http"
require "uri"

target = URI.parse "http://udzura.jp/"
contents = Net::HTTP.get target
puts contents.size
