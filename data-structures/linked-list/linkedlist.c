#include "linkedlist.h"
#include <assert.h>

Node* node_walk(Node* head, size_t index) {
  size_t i = 0;
  
   Node* next_node = head;
  while(i < index) {
    next_node = next_node->next;
    i++;
  }

  return next_node;
}


void linked_list_insert(LinkedList* self, void* elt) {

  size_t new_length = self->length+1;
  Node* new_node = self->arena->alloc(self->arena, sizeof(Node));
  assert(new_node != NULL);
  new_node->value = elt;


  if(self->length == 0) {
    self->head = new_node;
    self->head->next = NULL;
    self->head->previous = NULL;
    self->length = new_length;
  }
  else if(self->length == 1) {
    self->head->next = new_node;
    self->head->previous = new_node;
    new_node->previous = self->head;
    new_node->next = self->head;
    self->tail = new_node;
    self->length = new_length;
  }
  else {
    self->tail->next = new_node;
    new_node->previous = self->tail;
    new_node->next = self->head;
    self->tail = new_node;
    self->length = new_length;
  }
}

void linked_list_insert_at(LinkedList* self, size_t index, void* elt) {
  size_t new_length = self->length+1;
  Node* new_node = self->arena->alloc(self->arena, sizeof(Node));
  new_node->value = elt;

  if(self->length == 0) {
    self->head = new_node;
    self->length = new_length;
  }
  else if(self->length == 1 && index == 0) {
    Node* old_head = self->head;
    self->head = new_node;
    self->tail = old_head;
    self->tail->previous = self->head;
    self->head->next = self->tail;
  }
  else if(self->length-1 >= index) {
    Node* index_node = node_walk(self->head,index);
    new_node->previous = index_node->previous;
    index_node->previous->next =new_node;
    index_node->previous = new_node;
    new_node->next = index_node;
    self->length++;
  }
}


void* linked_list_remove_at(LinkedList* self, size_t index) {

  if(self->length-1 >= index) {
    Node* index_node = node_walk(self->head,index);
    void* removed_value = index_node->value;
    Node* next_node = index_node->next;
    next_node->previous = index_node->previous;
    index_node->previous->next = next_node;
    self->length--;
    return removed_value;
  }
  else if(self->length-1 == index) {
    Node* removed_node = self->tail;
    void* removed_value = removed_node->value;
    self->tail = removed_node->previous;
    self->tail->next = self->head;
    self->length--;
    return removed_value;
  }
  
  return NULL;
}

void* linked_list_pop(LinkedList* self) {
  if(self->length > 1) {
    void* popped_value = self->tail->value;
    Node* previous_node = self->tail->previous;
    previous_node->next = self->head;
    self->tail = previous_node;
    self->head->previous = self->tail;
    self->length--;
    return popped_value;
  }
  else if(self->length == 1) {
    void* popped_value = self->head->value;
    self->length--;
    return popped_value;
  }
  return NULL;
}

void* linked_list_get(LinkedList* self, size_t index) {
  if(self->length-1 < index) {
    return NULL;
  }

  Node* index_node = node_walk(self->head, index);
  return index_node->value;
}

static const linked_list_operations linked_list_methods = {
  .get = linked_list_get,
  .insert = linked_list_insert,
  .insert_at = linked_list_insert_at,
  .pop = linked_list_pop,
  .remove_at = linked_list_remove_at,
};

void linked_list_init(LinkedList* self, Arena* arena) {

  self->methods = &linked_list_methods;

  self->arena = arena;

  self->head = NULL;
  self->tail = NULL;

  self->length = 0;
}

