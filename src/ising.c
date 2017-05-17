#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"



int main(int argc, char **argv) {
	
	//Configuraciones
	int n = 256;
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
	int i;
	FILE *f = fopen("energias.txt", "w");
	int *lattice = malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	float energia = energia_total(lattice, n);
	//printf("%f\n", energia);
	//print_lattice(lattice, n);
	for(i = 0; i < 100000; i++){
		energia = metropolis(lattice, n, energias, energia);	
		//printf("%f\n", energia);
		//print_lattice(lattice, n);
		fprintf(f, "%f\n", energia);
	}
	fclose(f);
	free(lattice);
	return 0;
}