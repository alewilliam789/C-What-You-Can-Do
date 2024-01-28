#ifndef SCANNER_H
#define SCANNER_H

#include <stdio.h>
#include <stdbool.h>
#include "arena.h"

int json_scanner(FILE* json_file, char* file_path);

typedef struct JSONBuffer JSONBuffer;

struct JSONBuffer {
  char* current_file;
  size_t current_position;
  size_t file_size;
  bool error;
};

#endif
