#include "Endpoint.h"

Endpoint::Endpoint(const std::string& path, std::stringstream& logs)
    : path(path), logs(logs) {
}

const std::string& Endpoint::get_path() const { return path; }
