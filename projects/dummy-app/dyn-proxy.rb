backends = [
  "http://127.0.0.1:4567/",
  "http://127.0.0.1:4568/",
  "http://127.0.0.1:4569/"
]

r = Apache::Request.new
r.handler  = "proxy-server"
r.proxyreq = Apache::PROXYREQ_REVERSE
upstream = backends.sample

r.filename = "proxy:" + File.join(upstream, r.uri)
Apache.errlogger Apache::APLOG_NOTICE, "upstream: #{r.filename}"

Apache::return Apache::OK
