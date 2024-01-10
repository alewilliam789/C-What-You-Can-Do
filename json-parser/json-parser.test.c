#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "lexer.h"

void file_test(char* file_path, int assert_value) {
  FILE* current_file;

  current_file = fopen(file_path, "r");

  assert(current_file != NULL);

  assert(json_lexer(current_file) == assert_value);
  fclose(current_file);
};

int main() {

  char* test_file= "tests/json-test.json";

  file_test(test_file,0);
  
  test_file = "tests/not-test.json";

  file_test(test_file,1);

  test_file = "tests/data-test.json";

  file_test(test_file,0);

  return 0;

}
