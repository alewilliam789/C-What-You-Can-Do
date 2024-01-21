#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

typedef struct Node Node;

struct Node {
  int value;
  Node* next;
  Node* previous;
};

typedef struct LinkedList LinkedList;
typedef struct linked_list_operations linked_list_operations;

struct LinkedList {
  
  void (*init) (LinkedList* self, size_t linked_list_size);  
  void (*destroy) (LinkedList* self);
  const linked_list_operations* methods;
  size_t length;
  size_t private_size;
  Node* head;
  Node* tail;
};

struct linked_list_operations {
  void (*insert) (LinkedList* self,int elt);
  void (*insert_at) (LinkedList* self, size_t index, int elt);
  int (*pop) (LinkedList* self);
  int (*remove_at) (LinkedList* self, size_t index);
  int (*get) (LinkedList* self, size_t index);
  void (*from_array) (LinkedList* self, int input_array[], size_t length);
};


void linked_list_init(LinkedList* self, size_t linked_list_size);
void linked_list_destroy(LinkedList* self);

#endif
