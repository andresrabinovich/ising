#include "metropolis.h"
#include "stdlib.h"
#include "stdio.h"

float metropolis(int *lattice, int n, float *energias, float energia, float J, float J2, float B, int *magnetizacion, int corona) {
	return (flip(lattice, n, energias, energia, J, J2, B, magnetizacion, corona));
}

int pick_site(int *lattice, int n) {
	int sitio = n;
	do{
		sitio = (int)((float)rand()/RAND_MAX*n);
	}while(sitio == n);
	return(sitio);
	//return(rand()%n); //Esto es mas uniforme de lo que parece! pick_site_test.c
}

float flip(int *lattice, int n, float *energias, float energia, float J, float J2, float B, int *magnetizacion, int corona) {
	int sitio = pick_site(lattice, n*n);
    int variacion_configuracion   = delta_energia(lattice, n, sitio, corona);
    int variacion_configuracion_2 = delta_energia_2dos_vecinos(lattice, n, sitio, corona);
	float delta   = -J*variacion_configuracion+2*B*lattice[sitio]-J2*variacion_configuracion_2; //El + en el campo da vuelta el sitio sin darlo vuelta
	float delta_energia, delta_energia_2;
 	if(delta < 0){
		lattice[sitio] = -1*lattice[sitio];
        (*magnetizacion) += 2*lattice[sitio];
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
        switch(variacion_configuracion_2){
            case -8:
                delta_energia_2 = energias[7];
                break;
            case -4:
                delta_energia_2 = energias[8];                
                break;
            case 0:
                delta_energia_2 = energias[9];                
                break;
            case 4:
                delta_energia_2 = energias[10];                
                break;
            case 8:
                delta_energia_2 = energias[11];                
                break;
        }        
        if(lattice[sitio] == 1){
            delta_energia = delta_energia*delta_energia_2*energias[6];     
			//delta_energia = delta_energia*energias[6];        
        }else{
            delta_energia = delta_energia*delta_energia_2*energias[5];
			//delta_energia = delta_energia*energias[5];                            
        }
		if((float)rand()/RAND_MAX < delta_energia){
			lattice[sitio] = -1*lattice[sitio];
            (*magnetizacion) += 2*lattice[sitio];
			energia += delta;
		}
	}
	return energia;
}

int delta_energia(int *lattice, int n, int sitio, int corona){
	int i = (int)sitio/n;
	int j = sitio % n;
	int arriba;
	int abajo;
	int izquierda;
	int derecha;	
	switch(corona){
		case 0:
			arriba    = lattice[(i > 0 ? sitio-n:n*(n-1)+j)];
			abajo     = lattice[(i < n-1 ? sitio+n:j)];
			izquierda = lattice[(j > 0 ? sitio-1:n*(i+1)-1)];
			derecha   = lattice[(j < n-1 ? sitio+1:n*i)];			
			break;
		default:
			arriba    = (i > 0 ? lattice[sitio-n]:corona);
			abajo     = (i < (n-1) ? lattice[sitio+n]:corona);
			izquierda = (j > 0 ? lattice[sitio-1]:corona);
			derecha   = (j < (n-1) ? lattice[sitio+1]:corona);						
			break;
			
	}
	int delta   = -2*lattice[sitio]*(arriba+abajo+izquierda+derecha); //Calculo el delta. El - al principio da vuelta el spin del lattice[sitio] sin darlo vuelta realmente.
	return (delta); 
}

int delta_energia_2dos_vecinos(int *lattice, int n, int sitio, int corona){
	int i = (int)sitio/n;
	int j = sitio % n;
	int arriba_derecha = 1;
	int arriba_izquierda = 1;
	int abajo_derecha = 1;
	int abajo_izquierda = 1;
	
	switch(corona){
		case 0:
			if(i > 0){
				arriba_derecha   = lattice[(j < n-1 ? n*(i-1)+(j+1):n*(i-1))];
				arriba_izquierda = lattice[(j > 0 ? n*(i-1)+(j-1):n*(i-1)+(n-1))];
			}else{
				arriba_derecha   = lattice[(j < n-1 ? n*(n-1)+(j+1):n*(n-1))];
				arriba_izquierda = lattice[(j > 0 ? n*(n-1)+(j-1):n*n-1)];				
			}
			if(i < n-1){
				abajo_derecha   = lattice[(j < n-1 ? n*(i+1)+(j+1):n*(i+1))];
				abajo_izquierda = lattice[(j > 0 ? n*(i+1)+(j-1):n*(i+1)+(n-1))];
			}else{
				abajo_derecha   = lattice[(j < n-1 ? (j+1):0)];
				abajo_izquierda = lattice[(j > 0 ? (j-1):n-1)];				
			}
			break;
		default:
			if(i > 0){
				arriba_derecha   = (j < n-1 ? lattice[n*(i-1)+(j+1)]:corona);
				arriba_izquierda = (j > 0 ? lattice[n*(i-1)+(j-1)]:corona);
			}else{
				arriba_derecha   = (j < n-1 ? lattice[n*(n-1)+(j+1)]:corona);
				arriba_izquierda = (j > 0 ? lattice[n*(n-1)+(j-1)]:corona);
			}
			if(i < n-1){
				abajo_derecha   = (j < n-1 ? lattice[n*(i+1)+(j+1)]:corona);
				abajo_izquierda = (j > 0 ? lattice[n*(i+1)+(j-1)]:corona);
			}else{
				abajo_derecha   = (j < n-1 ? lattice[(j+1)]:corona);
				abajo_izquierda = (j > 0 ? lattice[(j-1)]:corona);
			}
			break;
			
	}
	int delta = -2*lattice[sitio]*(arriba_derecha+arriba_izquierda+abajo_derecha+abajo_izquierda); //Calculo el delta. El - al principio da vuelta el spin del lattice[sitio] sin darlo vuelta realmente.
	return (delta); 
}

float energia_total(int *lattice, int n, float J, float J2, float B, int corona){
	int sitio;
	float energia = 0;
	for(sitio = 0; sitio < n*n; sitio++){
		energia += 0.5*J*(float)delta_energia(lattice, n, sitio, corona)-B*lattice[sitio]+0.5*J2*(float)delta_energia_2dos_vecinos(lattice, n, sitio, corona);  //delta_energia devuelve dos veces la energía del sitio con el signo correcto. Con 0.5 ajustamos ese factor.
	}
	return(energia);
}

int magnetizacion_total(int *lattice, int n){
    int magnetizacion = 0;
    int sitio;
	for(sitio = 0; sitio < n*n; sitio++){
		magnetizacion += lattice[sitio];
	}
	return(magnetizacion);
}
