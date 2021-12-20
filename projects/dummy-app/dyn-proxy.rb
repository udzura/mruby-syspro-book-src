db = SQLite3::Database.new('/var/lib/apache2/dyn-proxy.db')

backends = []
db.execute('select upstream, weight from servers;') do |row, _|
  serv, weight = *row
  weight.times do
    backends << serv
  end
end

r = Apache::Request.new
r.handler  = "proxy-server"
r.proxyreq = Apache::PROXYREQ_REVERSE
upstream = backends.sample

r.filename = "proxy:" + File.join(upstream, r.uri)
Apache.errlogger Apache::APLOG_NOTICE, "upstream: #{r.filename}"

Apache::return Apache::OK
