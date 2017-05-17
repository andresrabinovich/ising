#ifndef METROPOLIS_H
#define METROPOLIS_H
float metropolis(int *lattice, int n, float *energias, float energia);
int pick_site(int *lattice, int n);
float flip(int *lattice, int n, float *energias, float energia);
float delta_energia(int *lattice, int n, int sitio);
float energia_total(int *lattice, int n);
#endif
