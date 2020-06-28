la1, la5, la15, _, _ = *File.read("/proc/loadavg").split
if la1.to_f >= 4.0
  Apache.errlogger Apache::APLOG_WARNING, "Detected high loadavg: #{la1}"
  Apache.return Apache::HTTP_SERVICE_UNAVAILABLE
else
  Apache.return Apache::DECLINED
end
