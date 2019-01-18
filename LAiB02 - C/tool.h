#ifndef TOOL_H
#define TOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define TOL 1e-10

typedef double Elemento;
typedef Elemento* Vettore;
typedef Vettore* Matrice;

Matrice allocaMatrice(const size_t ndim);
void liberaMatrice(Matrice m, const size_t ndim);
Vettore allocaVettore(const size_t ndim);

int* fattorizzazioneLU(Matrice* m, const size_t ndim);	// Restituisce Pivot
Vettore forwardSubstitution(const Matrice m, const Vettore terminiNoti, const size_t ndim);
Vettore backwardSubstitution(const Matrice m, const Vettore terminiNoti, const size_t ndim);

void print(const Matrice m, const size_t ndim);

#endif
