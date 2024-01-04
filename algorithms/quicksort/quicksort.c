#include <stdio.h>
#include <assert.h>


void swap(int input_array[], int left_index, int right_index) {
  int temp = input_array[right_index];
  input_array[right_index] = input_array[left_index];
  input_array[left_index] = temp;
}


int partition(int input_array[], int beginning, int end) {

  int i = beginning - 1;
  int j = beginning;
  int pivot_value = input_array[end];

  while(i <= end-1 && j <= end-1){
    if(input_array[j] <= pivot_value){
      i++;
      if(i != j) {
        swap(input_array,i,j);
      }
    }
    j++;
  }
  swap(input_array,i+1,end);
  return i+1;
}

void quicksort(int input_array[], int beginning, int end) {
  
  if(beginning < end){
    int q = partition(input_array,beginning,end);
    quicksort(input_array,beginning,q-1);
    quicksort(input_array,q+1,end);
  }
}




int main(){
  int sample_array[] = {3,9,4,7,9,5,6};
  int length = sizeof(sample_array)/sizeof(int);

  quicksort(sample_array,0,length-1);

  assert(sample_array[0] == 3);
  assert(sample_array[1] == 4);
  assert(sample_array[2] == 5);
  assert(sample_array[3] == 6);
  assert(sample_array[4] == 7);
  assert(sample_array[5] == 9);
  assert(sample_array[6] == 9);
  
  return 0;
}
