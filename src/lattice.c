#include "lattice.h"
#include "stdlib.h"
#include "stdio.h"

int fill_lattice(int *lattice, int n, float p) {
	float probabilidad = p*(float)RAND_MAX;
	int i;
	for(i = 0; i < n*n; i++){
		if(rand() < probabilidad){
			lattice[i] = 1;
		}else{
			lattice[i] = -1;
		}
	}
	return 0;
}

int print_lattice(int *lattice, int n) {
	int i, j;
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			printf("%2d", lattice[i*n+j]);
		}
		printf("\n");
	}
	return 0;
}
