#ifndef REQUEST_H
#define REQUEST_H

#include "stdlib.h"

typedef struct RequestRoute RequestRoute;

struct RequestRoute {
  char value[100];
  size_t length; 
};

typedef struct RequestHost RequestHost;

struct RequestHost {
  char name[100];
  size_t length;
};


// Will add more later
// Just trying to serve static HTML for now
enum RequestMethod {
  GET
};

typedef enum RequestMethod RequestMethod;


typedef struct HTTPRequest HTTPRequest;

struct HTTPRequest {
  char raw[9000];
  RequestMethod method;
  RequestRoute route;
  RequestHost host;
  int current_position;
};

void process_request(int newfd);

#endif
