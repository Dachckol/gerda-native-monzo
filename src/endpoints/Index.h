#ifndef INDEX_H
#define INDEX_H

#include "Endpoint.h"

class Index : public Endpoint {
 public:
  Index(std::stringstream& logs);
  void handle(const httplib::Request& req,
              httplib::Response& resp) const override;
};

#endif
