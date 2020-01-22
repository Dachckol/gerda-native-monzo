#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <httplib.h>
#include <sstream>
#include <string>
#include <functional>

class Endpoint {
 public:
  Endpoint(const std::string& path, std::stringstream& logs);
  const std::string& get_path() const;
  virtual void handle(const httplib::Request& req,
                      httplib::Response& resp) const = 0;
  virtual ~Endpoint() = default;
 protected:
  const std::string path;
  std::stringstream& logs;
};

#endif