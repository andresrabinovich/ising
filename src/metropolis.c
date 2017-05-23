#include "metropolis.h"
#include "stdlib.h"
#include "stdio.h"

float metropolis(int *lattice, int n, float *energias, float energia, float J, float B) {
	return (flip(lattice, n, energias, energia, J, B));
}

int pick_site(int *lattice, int n) {
	return((int)((float)rand()/RAND_MAX*n));
	//return(rand()%n); //Esto es mas uniforme de lo que parece! pick_site_test.c
}

float flip(int *lattice, int n, float *energias, float energia, float J, float B) {
	int sitio = pick_site(lattice, n*n);
	float delta = -J*delta_energia(lattice, n, sitio)+B*lattice[sitio]; //El + en el campo da vuelta el sitio sin darlo vuelta
	if(delta < 0){
		lattice[sitio] = -1*lattice[sitio];
		energia += delta;
	}else{
		if((float)rand()/RAND_MAX < (energias[(int)(0.25*delta)+2]*energias[(int)(0.5*(lattice[sitio]+1))+5])/energia){
			lattice[sitio] = -1*lattice[sitio];
			energia += delta;
		}
	};
	return energia;
}

float delta_energia(int *lattice, int n, int sitio){
	int i = (int)sitio/n;
	int j = sitio % n;
	int arriba    = (i > 0 ? sitio-n:n*(n-1)+j);
	int abajo     = (i < n-1 ? sitio+n:j);
	int izquierda = (j > 0 ? sitio-1:n*(i+1)-1);
	int derecha   = (j < n-1 ? sitio+1:n*i);
	float delta   = -2*lattice[sitio]*(lattice[arriba]+lattice[abajo]+lattice[izquierda]+lattice[derecha]); //Calculo el delta. El - al principio da vuelta el spin del lattice[sitio] sin darlo vuelta realmente.
	return (delta); 
}

float energia_total(int *lattice, int n, float J, float B){
	int sitio;
	float energia = 0;
	for(sitio = 0; sitio < n*n; sitio++){
		energia += 0.5*J*delta_energia(lattice, n, sitio)-B*lattice[sitio];  //delta_energia devuelve dos veces la energía del sitio con el signo correcto. Con 0.5 ajustamos ese factor.
	}
	return(energia);
}