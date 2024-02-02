#ifndef RESPONSE_H
#define RESPONSE_H

#include "request.h"
#include "stdlib.h"

// Will add more later
// Just trying to serve static HTML for now
enum RequestStatus {
  OK
};

typedef enum RequestStatus RequestStatus;


enum ContentType {
  TEXT
};

typedef struct ResponseHeader ResponseHeader;

struct ResponseHeader {
  char header[500];
  char* date;
};

typedef struct ResponseBody ResponseBody;

struct ResponseBody {
  char* body;
  size_t length;
  size_t total_sent;
};


typedef struct HTTPResponse HTTPResponse;

struct HTTPResponse {
  ResponseHeader header;
  ResponseBody body;
};


void header_builder(HTTPRequest* http);

#endif
