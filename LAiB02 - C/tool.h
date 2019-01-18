#ifndef TOOL_H
#define TOOL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Tolleranza per controlli sui numeri decimali
#define TOL 1e-10

// Typedef per brevità
typedef double Elemento;
typedef Elemento* Vettore;
typedef Vettore* Matrice;

Matrice allocaMatrice(const size_t ndim);           // Alloca una matrice quadrata di tipo Elemento di dimensione ndim x ndim
void liberaMatrice(Matrice m, const size_t ndim);   // Libera la matrice allocata tramite allocaMatrice
Vettore allocaVettore(const size_t ndim);           // Alloca un vettore di Elemento di dimensione ndim

// Esegue la fattorizzazione LU in-place. Alloca e restituisce un vettore per ricostruire il pivoting
int* fattorizzazioneLU(Matrice* m, const size_t ndim);

// Esegue la risoluzione di un sistema lineare con matrice triangolare superiore. Alloca e restituisce la soluzione
Vettore backwardSubstitution(const Matrice a, const Vettore y, const size_t ndim);

// Esegue la risoluzione di un sistema lineare con matrice triangolare superiore. Alloca e restituisce la soluzione
Vettore forwardSubstitution(const Matrice a, const Vettore y, const size_t ndim);

// Esegue il pivoting di un vettore, Alloca e restituisce il vettore permutato
Vettore permVett(const int* const pivot, const Vettore y, const size_t ndim);

// Risolve il sistema lineare dato dalla matrice quadrata A di dimensione ndim x ndim e dal vettore dei termini noti y
Vettore risolviSistemaLineare(const Matrice A, const Vettore y, const size_t ndim);

#endif
