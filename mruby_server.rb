PORT = 8000

app = -> (env) {
  [200,
   { 'Content-Type' => 'text/plain',
     'X-Powered-By' => 'mruby' },
   ["Hello, mruby customization!\n"]]
}

server = SimpleHttpServer.new(
  host: 'localhost',
  port: PORT,
  app: app
)

puts "Server start on port #{PORT}"
server.run
