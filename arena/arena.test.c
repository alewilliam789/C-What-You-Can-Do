#include <stdio.h>
#include <assert.h>
#include "arena.h"

typedef struct Store Store;

struct Store {
  int value;
};

int main() {
  
  Arena a;

  arena_init(&a, 4E9);

  Store* b = a.alloc(&a, sizeof(Store));

  b->value = 1;

  printf("%i \n", b->value);


  arena_destroy(&a);

  return 1;
}
