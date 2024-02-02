#ifndef SERVER_H
#define SERVER_H


int start(char* port, int backlog);

void multiplexer(int sockfd);


#endif
