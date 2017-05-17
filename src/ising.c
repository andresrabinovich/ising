#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"



int main(int argc, char **argv) {
	
	//Configuraciones
	int n = 4;
	float prob = 0.5;
	float T = 2.0;
	int niter = 50;
	
    //Calculamos las energías
    float energias[5];
    energias[0] = exp(-8/T);
    energias[1] = exp(-4/T);
    energias[2] = 1;
    energias[3] = exp(4/T);
    energias[4] = exp(8/T);
    
	//Comienza el programa
	int *lattice = malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	printf("%f\n", delta_energia(lattice, n, 5, T, energias));
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++){
		//metropolis(lattice, n, T);
		//energia += delta_energia(lattice, n, (i*n+j), T);
		}
	}
	print_lattice(lattice, n);
	free(lattice);
	return 0;
}
