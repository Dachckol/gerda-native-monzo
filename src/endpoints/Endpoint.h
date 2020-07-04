#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <httplib.h>
#include <sstream>
#include <string>
#include <functional>

#include <curl/curl.h>

class Endpoint {
 public:
  Endpoint(const std::string& path, std::stringstream& logs);
  const std::string& get_path() const;
  virtual void handle(const httplib::Request& req,
                      httplib::Response& resp) = 0;
  virtual ~Endpoint() = default;
 protected:
  const std::string path;
  std::stringstream& logs;
};

#endif
