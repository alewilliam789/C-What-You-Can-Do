#include<stdio.h>

void hash_output(int x, int a, int p) {
    float answer = (a*x)%p;
    printf("%f \n",answer);
  };


int main() {
  int a = 8;
  int p = 11;
  int remainder = 7;

  int x = 0;

  
  int answer;

  while(x <= 10) {
      hash_output(x,a,p);
      x++;
  }

  return 0;
}
