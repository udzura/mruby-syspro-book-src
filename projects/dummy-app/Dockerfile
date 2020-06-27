FROM ruby:2.7

RUN gem install sinatra
RUN echo 'require "sinatra" \n\
get "/" do \n\
  "Hello, application! Number: #{ENV["APP_NUMBER"]}\n" \n\
end' > /app.rb

EXPOSE 4567
CMD ["ruby", "/app.rb", "-o", "0.0.0.0"]
