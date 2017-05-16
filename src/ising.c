#include "stdlib.h"
#include "stdio.h"
#include "time.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	
	//Configuraciones
	int n = 3;
	float prob = 0.5;
	float T = 2.0;
	int niter = 50;
	
	//Comienza el programa
	int *lattice = malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	
	float energia=0;
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
		//metropolis(lattice, n, T);
			energia += calcular_energia(lattice, n, (i*n+j), T);
		}
	}
	printf("%f\n", energia);
	print_lattice(lattice, n);
	free(lattice);
	return 0;
}
