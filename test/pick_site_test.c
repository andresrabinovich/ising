/*
VERIFICA UNIFORMIDAD PARA LA SELECCION DEL SITIO (pick_site)
*/

#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "../src/metropolis.h"
#include "../src/metropolis.c"

int main(int argc, char **argv){
	int n = 256;
	int n_muestras = 100000000;
	int i;
	int *lattice = malloc(n*n*sizeof(int));
	int *muestras = malloc(n*n*sizeof(int));
	for(i = 0; i < n_muestras; i++){
		muestras[pick_site(lattice, n)]++;
	}
	for(i = 0; i < n; i++){
		printf("%d: %3.5f%%\n", i, (float)muestras[i]/(float)n_muestras);
	}
	free(lattice);
	free(muestras);
	
	return 0;
}