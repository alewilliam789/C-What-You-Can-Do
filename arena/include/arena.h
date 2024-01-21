#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Arena Arena;

struct Arena {
  char* beginning;
  size_t current;
  size_t private_size;
  void (*init)(Arena* self);
  void* (*alloc)(Arena* self, size_t object_size);
  void (*destroy)(Arena* self);
};

void arena_init(Arena* self);
void* arena_alloc(Arena* self, size_t object_size);
void arena_destroy(Arena* self);  

#endif
