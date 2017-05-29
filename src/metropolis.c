#include "metropolis.h"
#include "stdlib.h"
#include "stdio.h"

float metropolis(int *lattice, int n, float *energias, float energia, float J, float B, int *magnetizacion) {
	return (flip(lattice, n, energias, energia, J, B, magnetizacion));
}

int pick_site(int *lattice, int n) {
	return((int)((float)rand()/RAND_MAX*n));
	//return(rand()%n); //Esto es mas uniforme de lo que parece! pick_site_test.c
}

float flip(int *lattice, int n, float *energias, float energia, float J, float B, int *magnetizacion) {
	int sitio = pick_site(lattice, n*n);
    int variacion_configuracion = delta_energia(lattice, n, sitio);
	float delta = -J*variacion_configuracion+2*B*lattice[sitio]; //El + en el campo da vuelta el sitio sin darlo vuelta
	float delta_energia;
    //printf("%f\n", delta);
	if(delta < 0){
		lattice[sitio] = -1*lattice[sitio];
        (*magnetizacion) += lattice[sitio];
		energia += delta;
	}else{
        switch(variacion_configuracion){
            case -8:
                delta_energia = energias[0];
                break;
            case -4:
                delta_energia = energias[1];                
                break;
            case 0:
                delta_energia = energias[2];                
                break;
            case 4:
                delta_energia = energias[3];                
                break;
            case 8:
                delta_energia = energias[4];                
                break;
        }
        if(lattice[sitio] == 1){
            delta_energia = delta_energia*energias[6];                
        }else{
            delta_energia = delta_energia*energias[5];                            
        }
        //delta_energia = delta_energia/energia;
        //printf("%f\n", delta_energia);
		if((float)rand()/RAND_MAX < delta_energia){
            //printf("ACEPTADO\n");
			lattice[sitio] = -1*lattice[sitio];
            (*magnetizacion) += lattice[sitio];
			energia += delta;
		}
	}
	return energia;
}

int delta_energia(int *lattice, int n, int sitio){
	int i = (int)sitio/n;
	int j = sitio % n;
	int arriba    = (i > 0 ? sitio-n:n*(n-1)+j);
	int abajo     = (i < n-1 ? sitio+n:j);
	int izquierda = (j > 0 ? sitio-1:n*(i+1)-1);
	int derecha   = (j < n-1 ? sitio+1:n*i);
	int delta   = -2*lattice[sitio]*(lattice[arriba]+lattice[abajo]+lattice[izquierda]+lattice[derecha]); //Calculo el delta. El - al principio da vuelta el spin del lattice[sitio] sin darlo vuelta realmente.
	return (delta); 
}

float energia_total(int *lattice, int n, float J, float B){
	int sitio;
	float energia = 0;
	for(sitio = 0; sitio < n*n; sitio++){
		energia += 0.5*J*(float)delta_energia(lattice, n, sitio)-B*lattice[sitio];  //delta_energia devuelve dos veces la energía del sitio con el signo correcto. Con 0.5 ajustamos ese factor.
	}
	return(energia);
}

int magnetizacion_total(int *lattice, int n){
    int magnetizacion = 0;
    int sitio;
	for(sitio = 0; sitio < n*n; sitio++){
		if(lattice[sitio] == 1) magnetizacion++;
	}
	return(magnetizacion);
}
