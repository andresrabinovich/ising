#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	
	//Configuraciones
	int ns[4] = {32, 64, 128, 256};
	float prob = 0.5;
	float T_inicial = 5;
	float T_final = 0.5;
	float B = 0.0;
	float J = 1;
	float J2 = -1;
	float delta_T = -0.1; 
	int iteraciones = 2000000;
    int iteraciones_termalizacion = 1000000;
    int corona = 1;
	
    //Abrimos archivos de corrida
   	FILE *f = fopen("../corridas/segundos_vecinos/energia.txt", "w");
    fprintf(f, "iteracion,T,energia,n\n");
   	FILE *f2 = fopen("../corridas/segundos_vecinos/magnetizacion.txt", "w");    
    fprintf(f2, "iteracion,T,magnetizacion,n\n");

    //Declaramos las variables que vamos a usar
    int i, j, k, iteracion;
    float energia, energia_anterior;
	float T;
    float energias[12];
    int magnetizacion, magnetizacion_anterior;    
    
    //Semilla aleatoria
    srand(123456);
    
	for(i=1;i < 2;i++){ //Solo veo 64x64
		
		//Vamos variando el tamaño de red
		int n = ns[i];
		int *lattice = malloc(n * n * sizeof(int));
		printf("Usando red de n=%d\n", n);
		
		//Generamos una red inicial y la termalizamos.
		//Mostramos T actual
		T = T_inicial;
		printf("Termalizando a T=%f\n", T);
		
		//Calculamos las energías
		energias[0] = exp(-8*J/T);
		energias[1] = exp(-4*J/T);
		energias[2] = 1;
		energias[3] = exp(4*J/T);
		energias[4] = exp(8*J/T);
		energias[5] = exp(2*B/T);
		energias[6] = exp(-2*B/T);
		energias[7] = exp(-8*J2/T);
		energias[8] = exp(-4*J2/T);
		energias[9] = 1;
		energias[10] = exp(4*J2/T);
		energias[11] = exp(8*J2/T);

		//Llenamos la red y calculamos las propiedades iniciales
		fill_lattice(lattice, n, prob);
		energia = energia_total(lattice, n, J, J2, B, corona);
		magnetizacion = magnetizacion_total(lattice, n);
		
		//Termalizamos
		for(iteracion = 0; iteracion < iteraciones_termalizacion; iteracion++){
			energia = metropolis(lattice, n, energias, energia, J, J2, B, &magnetizacion, corona);	
		}

		//Guardamos la energía y la magnetizacion al finalizar la termalizacion
		energia_anterior = energia;
		magnetizacion_anterior = magnetizacion;
		
		//Comienza el programa
		for(T = T_inicial; T >= T_final; T += delta_T){
			
			//Mostramos T actual
			printf("Ising a T = %.2f\n", T);
			
			//Calculamos las energías
			energias[0] = exp(-8*J/T);
			energias[1] = exp(-4*J/T);
			energias[2] = 1;
			energias[3] = exp(4*J/T);
			energias[4] = exp(8*J/T);
			energias[5] = exp(2*B/T);
			energias[6] = exp(-2*B/T);
			energias[7] = exp(-8*J2/T);
			energias[8] = exp(-4*J2/T);
			energias[9] = 1;
			energias[10] = exp(4*J2/T);
			energias[11] = exp(8*J2/T);			
			
			//Iteramos
			for(iteracion = 0; iteracion < iteraciones; iteracion++){
				energia = metropolis(lattice, n, energias, energia, J, J2, B, &magnetizacion, corona);	
				//if((energia_anterior != energia || magnetizacion_anterior != magnetizacion) && iteracion%10000 == 0){
				if(iteracion%5000 == 0){			
					fprintf(f, "%d,%f,%f,%d\n", iteracion, T, (float)energia/(n*n), n);
					fprintf(f2, "%d,%f,%f,%d\n", iteracion, T, (float)magnetizacion/(n*n), n);                    
					energia_anterior = energia;
					magnetizacion_anterior = magnetizacion;
				}
			}
		}
		
		//Devolvemos la memoria
		free(lattice);		
	}

    //Cerramos los archivos
    fclose(f);
	fclose(f2);
    
	return 0;
}
