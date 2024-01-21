#include <assert.h>
#include "arena.h"



int main() {
  
  Arena a = {
    .init = arena_init,
    .destroy = arena_destroy,
    .alloc = arena_alloc
  };

  a.init(&a);

  Arena* b = a.alloc(&a, sizeof(Arena));

  b->init = arena_init;
  b->destroy = arena_destroy;

  a.destroy(&a);

  return 1;
}
