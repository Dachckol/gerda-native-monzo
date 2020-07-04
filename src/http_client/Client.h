#ifndef CLIENT_H
#define CLIENT_H

#include <tao/json.hpp>
#include <curl/curl.h>
#include <string>
#include <tuple>
#include <vector>

using Headers = std::vector<std::tuple<std::string, std::string>>;
using JSONPayload = tao::json::value;

enum class Method {
  GET,
  POST,
  PUT,
};

class HttpClient {
 public:
  JSONPayload get(const std::string& url, const JSONPayload& payload, const Headers& headers);
  JSONPayload get(const std::string& url);

  JSONPayload put(const std::string& url, const JSONPayload& payload, const Headers& headers);
  JSONPayload put(const std::string& url, const JSONPayload& payload);

  JSONPayload post(const std::string& url, const JSONPayload& payload, const Headers& headers);
  JSONPayload post(const std::string& url, const JSONPayload& payload);

 private:
  JSONPayload json_request(Method method, const std::string& url,
                           const JSONPayload& payload, const Headers& headers);
  std::string raw_request(Method method, const std::string& url,
                          const std::string& data, const Headers& headers);

  static CURLoption method_to_curlopt(Method method);
};

#endif  // CLIENT_H
