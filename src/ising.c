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
	float T = 100000;
	float J = 0;
	float B = 1;
	int pasos = 100000;
    
    //Calculamos las energías
    float energias[7];
    energias[0] = exp(-8*J);
    energias[1] = exp(-4*J);
    energias[2] = 1;
    energias[3] = exp(4*J);
    energias[4] = exp(8*J);
    energias[5] = exp(B/T);
	energias[6] = exp(-B/T);
	
	//Comienza el programa
	int i, j, k;
	FILE *f = fopen("../corridas/energias.txt", "w");
	FILE *f2 = fopen("../corridas/configuracion.txt", "w");
	int *lattice = malloc(n * n * sizeof(int));
	srand(time(NULL));
	fill_lattice(lattice, n, prob);
	float energia = energia_total(lattice, n, J, B);
    int magnetizacion = magnetizacion_total(lattice, n);
	//printf("%d\n", magnetizacion);
	//print_lattice(lattice, n);
	for(k = 0; k < pasos; k++){
		energia = metropolis(lattice, n, energias, energia, J, B, &magnetizacion);	
		//printf("%f\n", energia);
		//print_lattice(lattice, n);
		fprintf(f, "%d\n", magnetizacion);
		/*
        if(k%1000 == 0){
			for(i = 0; i < n; i++){
				fprintf(f2, "%d", lattice[i*n]);
				for(j = 1; j < n; j++){
					fprintf(f2, ",%d", lattice[i*n+j]);
				}
				fprintf(f2, "\n");
			}
		}
		*/
	}
    //printf("%d\n", magnetizacion);
	//print_lattice(lattice, n);    
	fclose(f);
	fclose(f2);	
	free(lattice);
	return 0;
}
