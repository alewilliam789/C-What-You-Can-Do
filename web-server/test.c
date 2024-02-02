#include "include/server.h"


int main(void) {
  
  int sockfd = start("3490",10);

  multiplexer(sockfd);

  return 1;
}
