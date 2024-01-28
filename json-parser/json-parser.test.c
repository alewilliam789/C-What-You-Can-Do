#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "parser.h"
#include "scanner.h"


void file_test(char* file_path, int assert_value) {
  FILE* current_file;

  current_file = fopen(file_path, "r");

  assert(current_file != NULL);

  assert(json_scanner(current_file, file_path) == assert_value);
  fclose(current_file);
}

int main() {
    
  // Can handle empty JSON
  char* test_file= "tests/empty-test.json";

  file_test(test_file,0);
  
  // Can parse strings, boolean, and numbers
  test_file = "tests/base-test.json";

  file_test(test_file,0);

  // Can parse nested json
  test_file = "tests/nested-test.json";

  file_test(test_file,0);

  // Can parse array
  test_file = "tests/array-test.json";

  file_test(test_file,0);

  // Can handle non-json text without false positive
  test_file = "tests/not-test.json";

  file_test(test_file,1);

  // Can detect faulty boolean data
  test_file = "tests/not-boolean-test.json";

  file_test(test_file,1);

  // Can detect faulty null data
  test_file = "tests/not-null-test.json";

  file_test(test_file,1);

  // Can handle incorrect nested json
  test_file = "tests/not-nested-test.json";

  file_test(test_file, 1);

  // Can handle incorrect array in json
  test_file = "tests/not-array-test.json";

  file_test(test_file, 1);

  return 0;
}
