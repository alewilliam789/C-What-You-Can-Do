#ifndef HEAP_H
#define HEAP_H

struct Heap {
  
  // Property is 1 for Min Heap and 2 Max Heap
  void (*init) (struct Heap *self, unsigned int heap_size, int property);
  // Destroys all internally malloced properties.  
  void (*destroy) (struct Heap *self);
  // To determine whether it's a min or max property
  signed int property_flag;
  const struct heap_operations *methods;
  int length;
  int private_size;
  float *H;
};

struct heap_operations {
  void (*insert) (struct Heap *self, float elt);
  float (*pop) (struct Heap *self);
  void (*replace) (struct Heap *self, float elt);
  void (*heapify) (struct Heap *self, float input[], int input_length);
};


void heap_init(struct Heap *self, unsigned int heap_size, int property);
void heap_destroy(struct Heap *self);

#endif
