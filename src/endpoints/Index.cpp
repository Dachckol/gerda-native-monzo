#include "Index.h"

#include <fstream>

#include "log.h"

Index::Index(std::stringstream& logs) : Endpoint("/", logs) {}

void Index::handle(const httplib::Request& req, httplib::Response& resp) const {
  std::stringstream data;
  {
    std::ifstream index("./index.html");
    info_log(logs, "Reading file: " + std::string("./index.html"));

    if (!index.is_open()) {
      info_log(logs, "ERROR: Failed to open file");
      return;
    }
    std::string line;
    while (!index.eof()) {
      index >> line;
      data << line;
    }
    index.close();
  }
  info_log(logs, "Received message");
  std::string content = data.str();
  resp.set_content(content, "text/html");
}
