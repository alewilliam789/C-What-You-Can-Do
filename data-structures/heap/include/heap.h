#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include "arena.h"

typedef struct Heap Heap;
typedef struct heap_operations heap_operations;

enum heap_property {MIN, MAX};

struct Heap {
  
  // Property is 1 for Min Heap and 2 Max Heap
  void (*init) (Heap* self, size_t heap_size, enum heap_property property);
  // Destroys all internally malloced properties.  
  void (*destroy) (Heap* self);
  // To determine whether it's a min or max property
  enum heap_property property_flag;
  const heap_operations* methods;
  Arena* arena;
  size_t length;
  size_t private_size;
  float* H;
};

struct heap_operations {
  void (*insert) (Heap* self, float elt);
  float (*pop) (Heap* self);
  void (*replace) (Heap* self, float elt);
  void (*heapify) (Heap* self, float input[], size_t input_length);
};


void heap_init(Heap* self, size_t heap_size, enum heap_property property);
void heap_destroy(Heap* self);

#endif
