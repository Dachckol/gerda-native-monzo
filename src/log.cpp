#include "log.h"

#include <fstream>
#include <iostream>

void info_log(std::stringstream& logs, const std::string&& string) {
  std::ofstream outfile("/data/tmp/output.txt", std::ios::app);
  outfile << string << std::endl;
  std::cout << string << std::endl;
  logs << "<p>" << string << "<//p>";
}
