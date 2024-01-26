#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "arena.h"


void arena_init(Arena *self, size_t private_size) {
  self->alloc = arena_alloc;
  self->current = 0;
  self->private_size = private_size;
  self->beginning = malloc(self->private_size);
  assert(self->beginning != NULL);
}

void* arena_alloc(Arena* self, size_t object_size) { 
  assert(object_size <= self->private_size || self->current+1+object_size <= self->private_size);
  
  self->current += object_size;
  return self->beginning + self->current - object_size;
}

void arena_destroy(Arena *self) {
  free(self->beginning);
}
