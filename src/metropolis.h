#ifndef METROPOLIS_H
#define METROPOLIS_H
float metropolis(int *lattice, int n, float *energias, float energia, float J, float B, int *magnetizacion);
int pick_site(int *lattice, int n);
float flip(int *lattice, int n, float *energias, float energia, float J, float B, int *magnetizacion);
float delta_energia(int *lattice, int n, int sitio);
float energia_total(int *lattice, int n, float J, float B);
int magnetizacion_total(int *lattice, int n);
#endif
