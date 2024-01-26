#include <assert.h>
#include "linkedlist.h"
#include "arena.h"

typedef struct store store;

struct store {
  int value;
};


int main() {

  Arena scratch;
  arena_init(&scratch, sizeof(store)*10+sizeof(Node)*10+sizeof(LinkedList));

  // Instantiate an empty linked list
  LinkedList a;
  linked_list_init(&a, &scratch);

  // Add a series of numbers to it
  store first = {
    .value = 1
  };

  a.methods->insert(&a,&first);
  store* returned = a.methods->get(&a,0);
  assert(returned->value == 1);

  store second = {
    .value = 2
  };

  a.methods->insert(&a,&second);
  returned = a.methods->get(&a,1);
  assert(returned->value == 2);

  store third = {
    .value = 3
  };

  a.methods->insert(&a,&third);
  returned = a.methods->get(&a,2);
  assert(returned->value == 3);

  store fourth = {
    .value = 4
  };
  
  a.methods->insert(&a,&fourth);
  returned = a.methods->get(&a,3);
  assert(returned->value == 4);
  
  store fifth = {
    .value = 5
  };

  a.methods->insert(&a,&fifth);
  returned = a.methods->get(&a,4);
  assert(returned->value == 5);

  // Pop the last value
  returned = a.methods->pop(&a);
  assert(returned->value == 5);
  assert(a.length == 4); 

  // Remove 2
  returned= a.methods->remove_at(&a,1);
  assert(returned->value == 2);
  assert(a.length == 3);


  // Insert 2 at old spot
  a.methods->insert_at(&a,1,&second);
  returned = a.methods->get(&a,1);
  assert(returned->value == 2);

  arena_destroy(&scratch);
}

