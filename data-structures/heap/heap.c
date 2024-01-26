#include <string.h>
#include <math.h>
#include <stdio.h>
#include "heap.h"

void swap(float passed_array[], int left_index, int right_index) {
  float temp = passed_array[left_index];
  passed_array[left_index] = passed_array[right_index];
  passed_array[right_index] = temp; 
}

void array_copy(float previous_array[], float new_array[], size_t previous_length) {
  size_t i = 0;
  while(i <= previous_length) {
    new_array[i] = previous_array[i];
    i++;
  }
}


void bubble_up(float passed_array[], unsigned int index, enum heap_property property_flag, size_t length) {
    if(index == 0) {
      return;
    }

    int parent;
    if(index == 1 || index == 2) {
      parent = 0;
    }
    else {
      parent = length%2 != 0 ? ((index/2)-1 > 0 ? (index/2)-1 : 0) : (index/2);
    }
  
    if(passed_array[index] < passed_array[parent] && property_flag == MIN) {
      swap(passed_array,parent,index);
      bubble_up(passed_array,parent,property_flag,length);
    }
    else if(passed_array[index] > passed_array[parent] && property_flag == MAX) {
      swap(passed_array,parent,index);
      bubble_up(passed_array,parent,property_flag,length);
    }
    else {
      return;
    }
}

void bubble_down(float passed_array[], int index, enum heap_property property_flag, int length) {
  if( 2*index+1 <= length) {
    int left_child = 2*index+1;
    int right_child = 2*index+2 > length ? length : 2*index+2;
    if(passed_array[left_child] < passed_array[right_child] && property_flag == MIN) {
      if(passed_array[left_child] < passed_array[index]) {
        swap(passed_array,index,left_child);
        bubble_down(passed_array,left_child,property_flag,length);
      }
    }
    else if(passed_array[right_child] < passed_array[left_child] && property_flag == MIN) {
      if(passed_array[right_child] < passed_array[index]) {
        swap(passed_array,index,right_child);
        bubble_down(passed_array,right_child,property_flag, length);
      }
    }
    else if(passed_array[left_child] > passed_array[right_child] && property_flag == MAX) {
      if(passed_array[left_child] > passed_array[index]) {
        swap(passed_array,index,left_child);
        bubble_down(passed_array,left_child,property_flag, length);
      }
    }
    else if(passed_array[right_child] > passed_array[left_child] && property_flag == MAX) {
      if(passed_array[right_child] > passed_array[index]) {
        swap(passed_array,index,right_child);
        bubble_down(passed_array,right_child,property_flag, length);
      }
    }
    else {
      if(passed_array[left_child] < passed_array[index] && property_flag == MIN) {
        swap(passed_array,index,left_child);
      }
      else if(passed_array[left_child] > passed_array[index] && property_flag == MAX) {
        swap(passed_array,index, left_child);
      }  
    }
  }
  return;
}

void heap_replace(Heap* self, float elt) {
  self->H[0] = elt;
  bubble_down(self->H,0,self->property_flag, self->length-1);
}

float heap_pop(Heap* self) {
    
    float sign = self->property_flag == MIN ? 1.00 : -1.00;
    float down_value = sign*HUGE_VAL;
    float pop_value = self->H[0];
    self->H[0] = down_value;
    bubble_down(self->H,0,self->property_flag ,self->length-1);

    int new_length = self->length-1;

    if(self->H[self->length-1] == down_value) {
      self->H[self->length-1] = 0;
      self->length = new_length;
    }
    else {
      swap(self->H,self->length-2,self->length-1);
      self->H[self->length-1] = 0;
      self->length =new_length;
    }
    
    return pop_value;
}

void heap_insert(Heap* self, float elt) {

  size_t new_length = self->length+1;
  
  if(self->length == 0) {
    self->H[0] = elt;
  }
  else if(new_length <= self->private_size) {
    self->H[new_length-1] = elt;
    bubble_up(self->H, new_length-1,self->property_flag,new_length);
    self->length++;
  }
  else {
    float *new_heap = malloc(sizeof(float)*new_length);
    array_copy(self->H,new_heap, self->length-1);
    new_heap[new_length-1] = elt;
    bubble_up(new_heap, new_length-1, self->property_flag,new_length);
    free(self->H);
    self->H = new_heap;
    self->length = new_length;
    self->private_size = new_length;
  }
}


void heapify(Heap* self, float unheaped_array[], size_t array_length) {
  

  
  if(self->length == 0 && self->private_size >= array_length) {
    size_t i = array_length-1;
    size_t j = array_length-2; 
    bubble_up(unheaped_array,i,self->property_flag,array_length);
    bubble_up(unheaped_array,j,self->property_flag,array_length);
    array_copy(unheaped_array,self->H,array_length);
    self->length = array_length;
  }
  else {
    size_t new_length = self->length + array_length;
    
    float* new_heap = self->arena->alloc(self->arena,sizeof(float)*new_length);
    array_copy(self->H,new_heap,self->length-1);

    size_t i = self->length;
    size_t j = 0;
    while(i <= new_length-1 && j <= array_length-1) {
      new_heap[i] = unheaped_array[j];
      bubble_up(new_heap,i, self->property_flag,i+1);
      i++;
      j++;
    }
    self->H = new_heap;
    self->length =new_length;
    self->private_size = new_length;
  }
}

static const heap_operations heap_methods = {
  .insert = heap_insert,
  .pop = heap_pop,
  .replace = heap_replace,
  .heapify = heapify
};


void heap_init(Heap* self, size_t size, enum heap_property property) {

  assert(self->arena != NULL);

  self->methods = &heap_methods;

  // If property flag is random, force to Max Heap
  if(property == MIN || property == MAX) {
    self->property_flag = property;
  }
  else {
    self->property_flag = MAX;
  }
 
  if(size > 0) {
    self->private_size = size;
    self->H = malloc(sizeof(float) * size);
  }
  else {
    self->private_size = size;
    self->H = malloc(sizeof(float));
  }

  self->length = 0;
}
