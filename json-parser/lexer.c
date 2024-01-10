#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "lexer.h"

typedef struct JSONKey JSONKey;

struct JSONKey {
  bool current;
  char value[250];
  size_t key_length;
};

typedef struct JSONData JSONData;

struct JSONData {
  bool current;
  char value[500];
  size_t value_length;
};

typedef struct JSON JSON;

struct JSON {
  bool current;
  JSONKey key;
  JSONData data;
};

void json_reset(JSON* json) {
  json->key.key_length = 0;
  json->key.current = false;
  json->data.current = false;
  json->data.value_length = 0;
};

int json_lexer(FILE* json_file) {
  
  int char_count = 100;
  char current_line[char_count];

  int json_object_count = 0;

  JSON json; 
  json.key.key_length = 0;
  json.data.value_length = 0;

  
  while(fgets(current_line,char_count, json_file) != NULL) {
    int i = 0;
    while(current_line[i] != '\n') {
      if(current_line[i] == '{') {
        json_reset(&json);
        json.current = true;
      }

      if(current_line[i] == '"') { 
        if(json.key.key_length == 0) {
          json.key.current = true;
        }
        else if(json.key.current) {
          json.key.current = false;
        }
        else if(json.data.value_length == 0) {
          json.data.current = true;
        }
        else {
          json.data.current = false;
        }
        i++;
        continue;
      }

      if(json.key.current) {
        assert(current_line[i] != '{' || current_line[i] != '}' || current_line[i] != ' ');
        if(current_line[i] != '\n' && current_line[i] != '\t' && current_line[i] != '\v' && current_line[i] != '\r' && current_line[i] != '\f') { 
          json.key.value[json.key.key_length] = current_line[i];
          json.key.key_length++;
        }
      }

      if(json.data.current) {
        assert(current_line[i] != '{' || current_line[i] != '}' || current_line[i] != ' ');
        if(current_line[i] != '\n' && current_line[i] != '\t' && current_line[i] != '\v' && current_line[i] != '\r' && current_line[i] != '\f') { 
          json.data.value[json.data.value_length] = current_line[i];
          json.data.value_length++;
        }
      }
      
      if(current_line[i] == '}') {
        json.current = false;
        json_object_count++;
        if(json.key.key_length > 0 && json.data.value_length > 0) {
          printf("{\n  \"%s\" : \"%s\"\n}\n", json.key.value, json.data.value);
        }
      }
      i++;
    }
  };

  if(json_object_count > 0) {
    return 0;
  }
  else {
    return 1;
  }
}
