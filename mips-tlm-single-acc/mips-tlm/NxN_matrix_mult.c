#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//definições
#define N 4
#define BASE_ADRESS (100*1024*1024)
#define MAXPROCESSORS 2
// variáveis compartilhadas entre os processadores
volatile int *lock = (volatile int *) BASE_ADRESS;
volatile int n_processors = 0;

volatile int result[N][N];

int matriz1[N][N] = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}};
int matriz2[N][N] = {{1,1,1,1}, {1,1,1,1}, {1,1,1,1}, {1,1,1,1}};

void AcquireLock(){   while(*lock); *lock=1;  }
void ReleaseLock(){   *lock = 0;      }


void print_matrix(volatile int matrix[N][N]){
  int i, j = 0;
  for (i = 0; i < N; i++) {
    for (j = 0; j < N; j++)
        printf("%d ", matrix[i][j]);
    printf("\n");
  }
}

int main(){
	int i, j, l = 0;
	int start, end, aux, mult;
	int index_processor;
	
	AcquireLock();
	index_processor = n_processors++;
	ReleaseLock();
	
	start = (N/MAXPROCESSORS)*index_processor;
	end 	= start + N/MAXPROCESSORS;
    
	for(i = start; i < end; i++){
		for(j = 0; j < N; j++){
			aux = 0;
			for(l = 0; l < N; l++){
				aux += matriz1[i][l] * matriz2[l][j];
			}
			AcquireLock();
			result[i][j] = aux;
			ReleaseLock();
		}
	}
	if (index_processor == 1){
		AcquireLock();
		print_matrix(result);
		ReleaseLock();
	}
}
