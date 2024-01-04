#include <string.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

void swap(float passed_array[], int left_index, int right_index) {
  float temp = passed_array[left_index];
  passed_array[left_index] = passed_array[right_index];
  passed_array[right_index] = temp; 
}

void array_copy(float previous_array[], float new_array[], int previous_length) {
  int i = 0;
  while(i <= previous_length) {
    new_array[i] = previous_array[i];
    i++;
  }
}


void bubble_up(float passed_array[], int index, int property_flag, int length) {
  if(index >= 0 && (index/2) >= 0) {
    int parent;
    if(index == 1 || index == 2) {
      parent = 0;
    }
    else {
      parent = length%2 != 0 ? ((index/2)-1 > 0 ? (index/2)-1 : 0) : (index/2);

    }
  
    if(passed_array[index] < passed_array[parent] && property_flag == 1) {
      swap(passed_array,parent,index);
      bubble_up(passed_array,parent,property_flag,length);
    }
    else if(passed_array[index] > passed_array[parent] && property_flag == 2) {
      swap(passed_array,parent,index);
      bubble_up(passed_array,parent,property_flag,length);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
}

void bubble_down(float passed_array[], int index, int property_flag, int length) {
  if( 2*index+1 <= length) {
    int left_child = 2*index+1;
    int right_child = 2*index+2 > length ? length : 2*index+2;
    if(passed_array[left_child] < passed_array[right_child] && property_flag == 1) {
      if(passed_array[left_child] < passed_array[index]) {
        swap(passed_array,index,left_child);
        bubble_down(passed_array,left_child,property_flag,length);
      }
      else {
        return;
      }
    }
    else if(passed_array[right_child] < passed_array[left_child] && property_flag == 1) {
      if(passed_array[right_child] < passed_array[index]) {
        swap(passed_array,index,right_child);
        bubble_down(passed_array,right_child,property_flag, length);
      }
      else {
        return;
      }
    }
    else if(passed_array[left_child] > passed_array[right_child] && property_flag == 2) {
      if(passed_array[left_child] > passed_array[index]) {
        swap(passed_array,index,left_child);
        bubble_down(passed_array,left_child,property_flag, length);
      }
      else {
        return;
      }
    }
    else if(passed_array[right_child] > passed_array[left_child] && property_flag == 2) {
      if(passed_array[right_child] > passed_array[index]) {
        swap(passed_array,index,right_child);
        bubble_down(passed_array,right_child,property_flag, length);
      }
      else {
        return;
      }
    }
    else {
      if(passed_array[left_child] < passed_array[index] && property_flag == 1) {
        swap(passed_array,index,left_child);
      }
      else if(passed_array[left_child] > passed_array[index] && property_flag == 2) {
        swap(passed_array,index, left_child);
      }  
      else {
        return;
      }
    }
  }
  else {
    return;
  }
}

void heap_replace(struct Heap *self, float elt) {
  self->H[0] = elt;
  bubble_down(self->H,0,self->property_flag, self->length-1);
}

float heap_pop(struct Heap *self) {
    
    float sign = self->property_flag == 1 ? 1.00 : -1.00;
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

void heap_insert(struct Heap *self, float elt) {

  int new_length = self->length+1;
  float *new_heap = malloc(sizeof(float)*new_length);

  if(self->length == 0) {
    new_heap[0] = elt;
    self->H = new_heap;
  }
  else if(new_length <= self->private_size) {
    self->H[new_length-1] = elt;
    bubble_up(self->H, new_length-1,self->property_flag,new_length);
    self->length++;
    free(new_heap);
  }
  else {
    array_copy(self->H,new_heap, self->length-1);
    new_heap[new_length-1] = elt;
    bubble_up(new_heap, new_length-1, self->property_flag,new_length);
    free(self->H);
    self->H = new_heap;
    self->length = new_length;
    self->private_size = new_length;
  }
}


void heapify(struct Heap *self, float unheaped_array[], int array_length) {
  

  
  if(self->length == 0 && self->private_size >= array_length) {
    int i = array_length-1;
    int j = array_length-2; 
    bubble_up(unheaped_array,i,self->property_flag,array_length);
    bubble_up(unheaped_array,j,self->property_flag,array_length);
    array_copy(unheaped_array,self->H,array_length);
    self->length = array_length;
  }
  else {
    int new_length = self->length + array_length;
    
    float *new_heap = malloc(sizeof(float)*new_length);
    array_copy(self->H,new_heap,self->length-1);

    int i = self->length;
    int j = 0;
    while(i <= new_length-1 && j <= array_length-1) {
      new_heap[i] = unheaped_array[j];
      bubble_up(new_heap,i, self->property_flag,i+1);
      i++;
      j++;
    }
    free(self->H);
    self->H = new_heap;
    self->length =new_length;
    self->private_size = new_length;
  }
}


void heap_init(struct Heap *self, unsigned int size, int property) {

  struct heap_operations *heap_methods = malloc(sizeof(struct heap_operations));
  heap_methods->insert = &heap_insert;
  heap_methods->pop = &heap_pop;
  heap_methods->replace = &heap_replace;
  heap_methods->heapify = &heapify;

  self->methods = heap_methods;

  // If property flag is random, force to Max Heap
  if(property == 1 || property == 2) {
    self->property_flag = property;
  }
  else {
    self->property_flag = 2;
  }
 
  if(size > 0) {
    self->private_size = size;
    self->H = malloc(sizeof(float) * size);
  }
  else {
    self->private_size = size;
  }

  self->length = 0;
}

void heap_destroy(struct Heap *self) {
  free(self->H);
  free((struct heap_operations*) self->methods);
}
