#ifndef ROUTES_H
#define ROUTES_H

#include <httplib.h>
#include <algorithm>
#include <vector>

#include "endpoints/Endpoint.h"

void set_routes(httplib::Server& svr,
                std::vector<std::unique_ptr<Endpoint>>& endpoints) {
  std::for_each(endpoints.begin(), endpoints.end(),
                [&svr](const std::unique_ptr<Endpoint>& endpoint_ptr) {
                  svr.Get(endpoint_ptr->get_path().c_str(),
                          [&endpoint_ptr](const httplib::Request& req,
                                          httplib::Response& resp) {
                            endpoint_ptr->handle(req, resp);
                          });
                });
}

#endif
