#include <assert.h>
#include <sys/stat.h>
#include "parser.h"
#include "scanner.h"
#include "arena.h"


int json_scanner(FILE* json_file, char* file_path) {

  Arena arena;

  struct stat st;
  stat(file_path,&st);

  size_t arena_size;

  if(st.st_size <= 500E3) {
    arena_size = 1E6;
  }
  else if(st.st_size <= 1E6) {
    arena_size = 2E6;
  }
  else if(st.st_size <= 500E6) {
    arena_size = 1E9;
  }
  else if(st.st_size <= 1E9) {
    arena_size = 2E9;
  }
  else {
    arena_size = 5E9;
  }

  arena_init(&arena, arena_size);
  
  char buffer[st.st_size];

  JSONBuffer json_buffer;
  json_buffer.current_position = 0;
  json_buffer.file_size = st.st_size;
  json_buffer.error = false;

  size_t test = fread(buffer,st.st_size,1,json_file);
  json_buffer.current_file = buffer;
  JSONObj* json = parse_json(&json_buffer, &arena);

  arena_destroy(&arena);

  if(json_buffer.error) {
    return 1;
  }

  return 0;
};
