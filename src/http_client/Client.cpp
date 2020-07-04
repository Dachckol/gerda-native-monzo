#include "Client.h"

#include <memory>

struct CurlDeleter{
  void operator()(CURL* curl){curl_easy_cleanup(curl);}
};


// GET
JSONPayload HttpClient::get(const std::string& url) {
  return get(url, tao::json::from_string("{}"), Headers());
}

JSONPayload HttpClient::get(const std::string& url, const JSONPayload& payload,
                            const Headers& headers) {
  return json_request(Method::GET, url, payload, headers);
}

// PUT
JSONPayload HttpClient::put(const std::string& url,
                            const JSONPayload& payload) {
  Headers empty_headers;
  return put(url, payload, empty_headers);
}

JSONPayload HttpClient::put(const std::string& url, const JSONPayload& payload,
                            const Headers& headers) {
  return json_request(Method::PUT, url, payload, headers);
}

// POST
JSONPayload HttpClient::post(const std::string& url,
                             const JSONPayload& payload) {
  Headers empty_headers;
  return post(url, payload, empty_headers);
}

JSONPayload HttpClient::post(const std::string& url, const JSONPayload& payload,
                             const Headers& headers) {
  return json_request(Method::POST, url, payload, headers);
}

JSONPayload HttpClient::json_request(Method method, const std::string& url,
                                     const JSONPayload& payload,
                                     const Headers& headers) {
  Headers json_headers(headers);

  json_headers.push_back(
      std::tuple<std::string, std::string>("Accept", "application/json"));
  json_headers.push_back(
      std::tuple<std::string, std::string>("Content-Type", "application/json"));

  std::string response = raw_request(method, url, tao::json::to_string(payload), json_headers);

  return tao::json::from_string(response);
}

static size_t CurlWriteCallback(void *contents, size_t size, size_t nmemb, std::string *buffer) {
  buffer->append(
      (char*)contents,
      size * nmemb
      );
  return size * nmemb;
}

std::string HttpClient::raw_request(Method method, const std::string& url,
                                    const std::string& data,
                                    const Headers& headers) {
  std::string buffer;
  std::unique_ptr<CURL, CurlDeleter> curl(curl_easy_init());
  if(curl.get()) {

    curl_slist *curl_headers;
    for (const auto& header: headers)
      curl_slist_append(curl_headers, (std::get<0>(header) + std::string(": ") + std::get<1>(header)).c_str() );


    curl_easy_setopt(curl.get(), CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl.get(), CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    curl_easy_setopt(curl.get(), CURLOPT_WRITEDATA, &buffer);
    curl_easy_setopt(curl.get(), method_to_curlopt(method), 1);
    curl_easy_setopt(curl.get(), CURLOPT_POSTFIELDS, data.c_str());

    CURLcode res = curl_easy_perform(curl.get());

    curl_slist_free_all(curl_headers);

    if (res != CURLE_OK) {
      throw std::runtime_error(std::to_string(res) + std::string(curl_easy_strerror(res)));
    }
  }
  return buffer;
}

CURLoption HttpClient::method_to_curlopt(Method method) {
  switch(method) {
    case Method::POST:
      return CURLOPT_POST;
    case Method::PUT:
      return CURLOPT_PUT;
    default:
      return CURLOPT_HTTPGET;
  }
}
