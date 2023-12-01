#include <stdio.h>
#include <stdlib.h>


void merge( int array[], int start, int mid, int end) {
  
  int i = start;
  int j = mid +1;
  int sortedArray[end-start+1];
  int freePosition = 0;

  while( i <= mid || j <= end){
    if(i <= mid && j <= end){
      if( array[i] >= array[j]){
        sortedArray[freePosition] = array[j];
        freePosition++;
        j++;
      }
      else {
        sortedArray[freePosition] = array[i];
        freePosition++;
        i++;
      }
    }
    else if( i <= mid){
      sortedArray[freePosition] = array[i];
      freePosition++;
      i++;
    }
    else {
      sortedArray[freePosition] = array[j];
      freePosition++;
      j++;
    }
  }

  for(int k = start; k < end+1; k++){
    array[k] = sortedArray[k-start];
  }
}

void mergesorter(int array[], int start, int end) {
  
  if( start >= end){
    return;
  }
  else if( start+1 == end){
    if(array[start] > array[end]){
      int swappedValue = array[start];
      array[start] = array[end];
      array[end] = swappedValue;
    }
  }
  else {
    int mid = (end+start)/2;
    mergesorter(array, start, mid);
    mergesorter(array, mid+1, end);
    merge(array, start, mid, end);
  }
}

void mergesort(int array[], int arrayLength){
  
  if(arrayLength <= 1){
    return;
  }
  else{
    mergesorter(array, 0, arrayLength-1);
  }
}

int main(int argc, char *argv[]){
  int testArray[] = { 5,4,3,2,1};
  int arrayLength = 5;

  mergesort(testArray, arrayLength);
  for(int i = 0; i < 5; i++){
    printf("%i", testArray[i]);
  }
  return 0;
}
