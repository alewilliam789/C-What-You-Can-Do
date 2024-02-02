#include "include/request.h"
#include "include/handler.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <sys/socket.h>



void parse_route(HTTPRequest* http) {
  char current_character;

  int j = 0;
  while(true) {
    current_character = http->raw[http->current_position];
    
    if(isalnum(current_character) || ispunct(current_character)) {
      http->route.value[j] = current_character;
      http->route.length++;
      j++;
    }
    else {
      return;
    }
    
    http->current_position++;
  }
}

void parse_method(HTTPRequest* http) {
  char current_character;

  while(true) {
    current_character = http->raw[http->current_position];

    if(!isspace(current_character) && current_character == 'G') {
      http->method = GET;
      return;
    }
    else {
      perror("Sorry this method is not ready yet");
    }
  } 
}

void parse_http_request(HTTPRequest* http) {
  char current_character = ' ';
  http->current_position = 0;
  http->route.length = 0;

  while(current_character != '\0') {
    current_character = http->raw[http->current_position];

    if(http->current_position == 0) {
      parse_method(http); 
    }
    else if(current_character == '/' && http->route.length == 0) {
      parse_route(http);
    }

    http->current_position++;
  }
  http->route.value[http->route.length] = '\0';
  strcat(http->route.value, "\r\n");
  http->route.length += 2;
}

void process_request(int newfd) {
  HTTPRequest http;
  char header_message[] = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\n";
  char request_response[200];
 
  while(true) {
    
    int recv_length = recv(newfd,http.raw,9000,0);
    if(recv_length == 0 ) {
      break;
    }
    else if( recv_length == -1) {
      perror("recv");
      break;
    }

    parse_http_request(&http);

    strcat(request_response, "Requested route: ");
    strcat(request_response, http.route.value);

    int len = http.route.length + 17;

    int send_length = send(newfd,header_message,45, 0);
    send_length = send(newfd,request_response,len,0);
    if(send_length == -1) {
      perror("send");
      break;
    }
    break;
  }
}
