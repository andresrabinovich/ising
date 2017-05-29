#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#include "math.h"

#include "metropolis.h"
#include "lattice.h"



int main(int argc, char **argv) {
	
	//Configuraciones
	int n = 32;
	float prob = 0.5;
	float T = 1;
	float J = 1/T;
	float B = 1;
	int pasos = 1000000;
    int pasos_termalizacion = 0;
    int promedios = 1;
    
    //Abrimos archivos de corrida
   	FILE *f = fopen("../corridas/energia.txt", "w");
    fprintf(f, "T,energia\n");
   	FILE *f2 = fopen("../corridas/magnetizacion.txt", "w");    
    fprintf(f2, "T,magnetizacion\n");
	FILE *f3 = fopen("../corridas/configuraciones.txt", "w");

    //Declaramos las variables que vamos a usar
    int i, j, k, paso, promedio;
    int *lattice = malloc(n * n * sizeof(int));
    float energia;
    float energias[7];
    int magnetizacion;    
    float energia_promedio;
    int magnetizacion_promedio;    

    
    //Semilla aleatoria
    srand(time(NULL));
    
    //Comienza el programa
    for(T = 0.1; T <= 5; T = T + 0.1){
    
        //Mostramos T actual
        printf("Ising a T = %.2f\n", T);
        
        //Calculamos las energías
        J = 0;
        energias[0] = exp(-8*J/T);
        energias[1] = exp(-4*J/T);
        energias[2] = 1;
        energias[3] = exp(4*J/T);
        energias[4] = exp(8*J/T);
        energias[5] = exp(2*B/T);
        energias[6] = exp(-2*B/T);
        //printf("%f %f %f %f %f %f %f\n", energias[0], energias[1], energias[2], energias[3], energias[4], energias[5], energias[6]);
        //return(1);
        energia_promedio = 0;
        magnetizacion_promedio = 0;
        
        //Calculamos los promedios
        for(promedio = 0; i < promedios; promedio++){
            //Llenamos la red y calculamos las propiedades iniciales
            fill_lattice(lattice, n, prob);
            energia = energia_total(lattice, n, J, B);
            magnetizacion = magnetizacion_total(lattice, n);
            
            //Termalizamos
            for(paso = 0; paso < pasos_termalizacion; paso++){
                energia = metropolis(lattice, n, energias, energia, J, B, &magnetizacion);	
            }
            //printf("%d\n", magnetizacion);
            //print_lattice(lattice, n);
            for(paso = 0; paso < pasos; paso++){
                energia = metropolis(lattice, n, energias, energia, J, B, &magnetizacion);	
                //printf("%f\n", energia);
                //printf("%d\n", magnetizacion);
                //fprintf(f, "%d\n", magnetizacion);
                //print_lattice(lattice, n);                
                /*
                if(paso%100000 == 0){
                    for(i = 0; i < n; i++){
                        fprintf(f3, "%d", lattice[i*n]);
                        for(j = 1; j < n; j++){
                            fprintf(f3, ",%d", lattice[i*n+j]);
                        }
                        fprintf(f3, "\n");
                    }
                }
                */
                if(paso%1000 == 0){
                    //magnetizacion_promedio += magnetizacion;  
                    fprintf(f, "%f,%f\n", T, energia/promedios);
                    //fprintf(f2, "%f,%f\n", T, (float)magnetizacion_promedio/(n*n)/promedios/(pasos/200));                    
                    fprintf(f2, "%f,%f\n", T, (float)magnetizacion/(n*n));                    
                }
            }
            energia_promedio += energia;
            //magnetizacion_promedio += magnetizacion;            
        }

    }

    //Cerramos los archivos
    fclose(f);
	fclose(f2);
	fclose(f3);	    
    
    //Devolvemos la memoria
	free(lattice);
	return 0;
}
