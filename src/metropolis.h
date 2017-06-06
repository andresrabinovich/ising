#ifndef METROPOLIS_H
#define METROPOLIS_H
float metropolis(int *lattice, int n, float *energias, float energia, float J, float J2, float B, int *magnetizacion, int corona);
int pick_site(int *lattice, int n);
float flip(int *lattice, int n, float *energias, float energia, float J, float J2, float B, int *magnetizacion, int corona);
int delta_energia(int *lattice, int n, int sitio, int corona);
float energia_total(int *lattice, int n, float J, float J2, float B, int corona);
int delta_energia_2dos_vecinos(int *lattice, int n, int sitio, int corona);
int magnetizacion_total(int *lattice, int n);
#endif
