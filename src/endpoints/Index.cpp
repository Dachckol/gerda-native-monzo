#include "Index.h"

#include <fstream>

#include "log.h"

std::string Index::html_content = R"raw(
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="utf-8" />
    <meta
      name="viewport"
      content="width=device-width, initial-scale=1, shrink-to-fit=no"
    />
    <meta name="theme-color" content="rgb(106, 0, 128)" />
    <title>Monzo</title>
  </head>

  <body>
    <div id="root">
      <article>
        @content
      </article>
    </div>
  </body>
</html>
)raw";

Index::Index(std::stringstream& logs) : Endpoint("/", logs) {}

void Index::handle(const httplib::Request& req, httplib::Response& resp) {
  info_log(logs, "Received message");

  std::string body;
  try {
//TODO: Example address
    body = tao::json::to_string(
        client.get("https://www.reddit.com/r/listentothis/new/.json"));
  } catch (const std::exception& e) {
    info_log(logs, e.what());
  }

  std::string content =
      std::string(html_content)
          .replace(html_content.find("@content"), sizeof("@content"), body);

  resp.set_content(content, "text/html");
}
