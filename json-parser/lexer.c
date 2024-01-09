#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"


int json_lexer(FILE* json_file) {
  
  char current_line[100];

  while(fgets(current_line,100, json_file)) {
    printf("%s",current_line);
  }

  return 0;
}
