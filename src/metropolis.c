#include "metropolis.h"
#include "stdlib.h"
#include "stdio.h"

int metropolis(int *lattice, int n, float T) {
	flip(lattice, n, T);
	return 0;
}

int pick_site(int *lattice, int n) {
	return((int)((float)rand()/RAND_MAX*n));
	//return(rand()%n); //Esto es mas uniforme de lo que parece! pick_site_test.c
}

int flip(int *lattice, int n, float T) {
	int sitio = pick_site(lattice, n*n);
	
	return 0;
}

float delta_energia(int *lattice, int n, int sitio, float T, float *energias){
	int i = (int)sitio/n;
	int j = sitio % n;
	int arriba    = (i > 0 ? sitio-n:n*(n-1)+j);
	int abajo     = (i < n-1 ? sitio+n:j);
	int izquierda = (j > 0 ? sitio-1:n*(i+1)-1);
	int derecha   = (j < n-1 ? sitio+1:n*i);
	return (energias[(int)(0.5*lattice[sitio]*(lattice[arriba]+lattice[abajo]+lattice[izquierda]+lattice[derecha])+2)]);
}
