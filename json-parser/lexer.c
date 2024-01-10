#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "lexer.h"

struct JSON {
  bool beginning;
  bool end;
} first_json;

int json_lexer(FILE* json_file) {
  
  int char_count = 100;
  char current_line[char_count];

  first_json.beginning = false;
  first_json.end = false;

  while(fgets(current_line,char_count, json_file) != NULL) {
    int i = 0;
    while(current_line[i] != '\n') {
      if(current_line[i] == '{') {
        first_json.beginning = true;
      }

      if(current_line[i] == '}') {
        first_json.end = true;
      }
      i++;
    }
  };

  if(first_json.beginning == true && first_json.end == true) {
    return 0;
  }
  else {
    return 1;
  }
}
