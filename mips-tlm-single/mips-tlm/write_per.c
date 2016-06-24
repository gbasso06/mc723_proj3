#include <stdio.h>
#define BASE_ADDRESS (100*1024*1024)

volatile int *lock = (volatile int *) BASE_ADDRESS;

int main(){
  //*lock = 1337;
  //printf("Wrote to the lock! %d\n", *lock);
  //
  int i; int limit = 5;
  for(i = 0; i < limit; i++){
      printf("posicao = %d\tvalor = %d\n", lock, *lock);
      lock++;
  }
  return 0;
}
