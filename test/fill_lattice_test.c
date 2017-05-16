/*
VERIFICA PROBABILIDAD DE OCUPACION EN LA RED
*/

#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "../src/lattice.h"
#include "../src/lattice.c"

int main(int argc, char **argv){
	int n = 256;
	float prob = 0.1;
	int muestras = 10000;
	int i, m, total;
	int *lattice = malloc(n*n*sizeof(int));
	srand(12345);
	//print_lattice(lattice, n);
	for(prob = 0; prob <= 1; prob += 0.1){
		fill_lattice(lattice, n, prob);
		total = 0;		
		for(m = 0; m < muestras; m++){
			for(i = 0; i < n*n; i++){
				if(lattice[i] == 1) total++;
			}
		}
		printf("%f: %f\n", prob, (float)total/(muestras*n*n));
	}
	free(lattice);
	
	return 0;
}