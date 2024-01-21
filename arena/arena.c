#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "arena.h"


void arena_init(Arena *self) {
  self->private_size = 500000;
  self->beginning = malloc(self->private_size);
  assert(self->beginning != NULL);
}

void* arena_alloc(Arena* self, size_t object_size) { 
  if(object_size > self->private_size || self->current+1+object_size > self->private_size) {
    return NULL;
  }
  else {
    self->current += object_size;
    return self->beginning + self->current - object_size;
  }
}

void arena_destroy(Arena *self) {
  free(self->beginning);
}
