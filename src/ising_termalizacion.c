//#######################################################
//PARA UN CAMPO B Y J=0 CALCULA LA CANTIDA DE ITERACIONES
//PARA TERMALIZAR EL SISTEMA
//#######################################################

#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"

int main(int argc, char **argv) {
	
	//Configuraciones
	int n = 64;
	float prob = 0.5;
	float T_inicial = 0.5;
	float T_final = 4;
	float B = 1;
	float J = 0;
	float delta_T = 0.5; 
	int iteraciones = 100000;
    
    //Abrimos archivos de corrida
   	FILE *f = fopen("../corridas/termalizacion/magnetizacion.txt", "w");    
    fprintf(f, "iteracion,T,magnetizacion\n");

    //Declaramos las variables que vamos a usar
    int i, j, k, iteracion;
    int *lattice = malloc(n * n * sizeof(int));
    float T;
	float energia;
    float energias[7];
    int magnetizacion;    
    
    //Semilla aleatoria
    srand(time(NULL));
    
    //Comienza el programa
    for(T = T_inicial; T <= T_final; T += delta_T){
    
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
        
		//Llenamos la red y calculamos las propiedades iniciales
		fill_lattice(lattice, n, prob);
		energia = energia_total(lattice, n, J, B);
		magnetizacion = magnetizacion_total(lattice, n);
		
		//Comenzamos a iterar el sistema
		for(iteracion = 0; iteracion < iteraciones; iteracion++){
			energia = metropolis(lattice, n, energias, energia, J, B, &magnetizacion);	
			fprintf(f, "%d,%f,%f\n", iteracion, T, (float)magnetizacion/(n*n));                    
        }
    }

    //Cerramos los archivos
	fclose(f);
    
    //Devolvemos la memoria
	free(lattice);
	return 0;
}
