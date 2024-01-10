#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"


int main() {
  FILE* current_file;

  char* test_file = "tests/json-test.json";

  current_file = fopen(test_file, "r");

  if(current_file == NULL) {
    return 1;
  }

  assert(json_lexer(current_file) == 0);

  test_file = "tests/not-test.json";

  fclose(current_file);

  current_file = fopen(test_file, "r");

  if(current_file == NULL) {
    return 1;
  }

  assert(json_lexer(current_file) == 1);

  fclose(current_file);

  return 0;

}
