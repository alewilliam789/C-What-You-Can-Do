#ifndef HANDLER_H
#define HANDLER_H

#include "http.h"

typedef struct RequestHandler RequestHandler;

struct RequestHandler {
  char* request_path;
  char* alias;
  void (*builder)(HTTP* http);
  size_t file_size;
  ContentType file_type; 
};

typedef struct RequestWrangler RequestWrangler;

struct RequestWrangler {
  RequestHandler* handlers;
  size_t length;
} wrangler;



void request_handler(HTTP* http, RequestWrangler* request_wrangler);

void header_builder(HTTP* http, RequestHandler handler);

#endif 
