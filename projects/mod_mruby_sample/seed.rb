db = SQLite3::Database.new('/var/lib/nginx/dyn-proxy.db')

db.execute_batch <<SQL
  create table servers(
    upstream varchar(255),
    weight integer
  );
SQL

def populate(db, server, weight=1)
  db.execute_batch('insert into servers(upstream, weight) values(?, ?);',
                   server, weight)
end

populate db, "http://127.0.0.1:4567/", 6
populate db, "http://127.0.0.1:4568/", 3
populate db, "http://127.0.0.1:4569/", 1

res = db.execute('select count(*) from servers;')
if res.next[0] == 3
  puts "OK!"
end
