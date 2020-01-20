#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef __arm__
#include "ifaddrs.h"
#endif

#include "httplib.h"

void log(std::stringstream& logs, const std::string && string){
  std::ofstream outfile("/data/tmp/output.txt", std::ios::app);
  outfile << string << std::endl;
  std::cout << string << std::endl;
  logs << "<p>" << string << "<//p>";
}


int main(const int argc, const char ** argv) {
  int port = atoi(argv[2]);
  std::stringstream data, logs;
  {
    std::ifstream index(argv[1]);
    log(logs, "Reading file: " + std::string(argv[1]));

    if (!index.is_open()) {
      log(logs, "ERROR: Failed to open file");
      return 0;
    }
    std::string line;
    while(!index.eof()) {
      index >> line;
      data << line;
    }
    index.close();
  }

  httplib::Server svr;

  svr.Get("/", [&data, &logs](const httplib::Request& req, httplib::Response& resp) {
      log(logs, "Received message");
      std::string content = data.str();
      content.replace(content.find("@content"), 8, logs.str());
      resp.set_content(content, "text/html");
      });
  svr.Get("/die", [&svr](const httplib::Request& req, httplib::Response& resp) {
      svr.stop();
      });


  log(logs, "Running on port: " + std::to_string(port));
  if(!svr.listen("127.0.0.1", port)) {
    log(logs, "Failed to listen to port: " + std::to_string(port));
  }

  log(logs, "Shutdown");
  return 0;
}
