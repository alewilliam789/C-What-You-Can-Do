#include <assert.h>
#include "linkedlist.h"





int main() {


  // Object creation
  LinkedList *a = malloc(sizeof(LinkedList));
  a->init = &linked_list_init;
  a->destroy = &linked_list_destroy;

  // Instantiate an empty linked list of size 5
  a->init(a,5);
  assert(a->private_size == 5);

  // Add a series of numbers to it
  a->methods->insert(a,1);
  assert(a->methods->get(a,0) == 1);

  a->methods->insert(a,2);
  assert(a->methods->get(a,1) == 2);

  a->methods->insert(a,3);
  assert(a->methods->get(a,2) == 3);
  
  a->methods->insert(a,4);
  assert(a->methods->get(a,3) == 4);
  
  a->methods->insert(a,5);
  assert(a->methods->get(a,4) == 5);


  // Pop the last number
  int fifth_value = a->methods->pop(a);
  assert(fifth_value == 5);
  assert(a->length == 4); 

  // Remove 2
  int removed_at_value = a->methods->removeAt(a,1);
  assert(removed_at_value == 2);
  assert(a->length == 3);


  // Insert 2 at old spot
  a->methods->insertAt(a,1,2);
  assert(a->methods->get(a,1) == 2);

  a->destroy(a);
  free(a);

  LinkedList *b = malloc(sizeof(LinkedList));
  b->init = &linked_list_init;
  b->destroy = &linked_list_destroy;

  b->init(b,5);
  assert(b->private_size == 5);

  int sample_array[] = {1,2,3,4,5};
  b->methods->fromArray(b,sample_array,5);
  assert(b->methods->get(b,0) == 1);
  assert(b->methods->get(b,1) == 2);
  assert(b->methods->get(b,2) == 3);
  assert(b->methods->get(b,3) == 4);
  assert(b->methods->get(b,4) == 5);

  b->destroy(b);
  free(b);
}

