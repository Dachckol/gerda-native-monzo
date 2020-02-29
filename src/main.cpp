#include <sstream>
#include <string>
#include <memory>

#ifdef __arm__
#include <ifaddrs.h>
#endif

#include <httplib.h>

#include <curl/curl.h>

#include "endpoints/Endpoint.h"
#include "endpoints/Index.h"
#include "log.h"
#include "routes.h"

std::vector<std::unique_ptr<const Endpoint>> get_endpoints(
    std::stringstream& logs) {
  std::vector<std::unique_ptr<const Endpoint>> result;

  result.push_back(std::unique_ptr<const Index>(new Index(logs)));

  return result;
}

#include <iostream>
int main(const int argc, const char** argv) {
  std::cout << "logs created" << std::endl;
  std::stringstream logs;
  int port = atoi(argv[1]);
  auto endpoints = get_endpoints(logs);
  std::cout << "endpoints craeted" << std::endl;

  httplib::Server svr;
  set_routes(svr, endpoints);
  std::cout << "endpoints registered" << std::endl;

  info_log(logs, "Running on port: " + std::to_string(port));
  if (!svr.listen("127.0.0.1", port)) {
    info_log(logs, "Failed to listen to port: " + std::to_string(port));
  }

  info_log(logs, "Shutdown");
  return 0;
}
