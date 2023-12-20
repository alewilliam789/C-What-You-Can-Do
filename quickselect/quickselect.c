#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void swap(int input_array[], int left_index, int right_index) {
  int temp = input_array[right_index];
  input_array[right_index] = input_array[left_index];
  input_array[left_index] = temp;
}

int random_at_most(int max) {
  unsigned int num_bins = (unsigned int) max + 1;
  unsigned int num_rand = (unsigned int) RAND_MAX + 1;
  unsigned int bin_size = num_rand/num_bins;
  unsigned int defect = num_rand % num_bins;

  int x;
  do {
    x = rand();
  } while( num_rand - defect <= (unsigned int) x);

  return x/bin_size;
}


int partition(int input_array[],int beginning, int end) {
  int i = beginning -1;
  int j =  beginning;
  int random_index = beginning + random_at_most(end-beginning);
  assert(random_index <= end);
  assert(random_index >= beginning);
  swap(input_array,random_index,end);
  int pivot_value = input_array[end];

  while(i+1 <= end && j+1 <= end) {
    if(input_array[j] <= pivot_value) {
      i++;
      if( i != j) {
        swap(input_array,i,j);
      }
    }
    j++;
  }

  swap(input_array,i+1,end);

  if(i+1 > end) {
    return end;
  }

  return i+1;
}


int quickselect(int input_array[],int beginning, int end, int n_largest) {

  int start = beginning;
  int butt = end;
 
  int q = partition(input_array,start,butt);

  while(q != (n_largest-1)) {
    if(q > n_largest-1) {
      butt = q-1;
      q = partition(input_array,start,butt);
    }
    else if(q < n_largest-1) {
      start = q+1;
      q = partition(input_array,start, butt);
    }
  }

  return input_array[q];
}

int main() {
  int sample_array[] = {1,9,2,8,3,7,4,6,5};

  int seventh_largest = quickselect(sample_array,0,8,7);

  assert(seventh_largest == 7);
  
  int second_largest = quickselect(sample_array,0,8,2);
  
  assert(second_largest == 2);


  int median = quickselect(sample_array,0,8,5);

  assert(median == 5);


  int another_array[] = {6,62,20,33,2};

  int fourth_largest = quickselect(another_array,0,4,4);

  assert(fourth_largest == 33);

  return 0;
}
