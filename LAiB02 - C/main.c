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
void fattorizzazioneLU(Matrice* m, Vettore* pivot, const size_t ndim);
Vettore forwardSubstitution(const Matrice m, const Vettore pivot, const Vettore terminiNoti);
Vettore backwardSubstitution(const Matrice m, const Vettore pivot, const Vettore terminiNoti);

int main()
{
	// Variabili
	size_t ndim;
	size_t i,j;
	Matrice m;
	Vettore pivot;
	Vettore terminiNoti;
	Vettore soluzione;

	// Istruzioni

	// Acquisisco da standard input la dimensione della matrice
	printf("Inserisci la dimensione della matrice\n");
	scanf(" %lu", &ndim);

	// Alloco la matrice
	m = allocaMatrice(ndim);

	// Alloco vettori per risoluzione sistema lineare
	terminiNoti = allocaVettore(ndim);
	soluzione = allocaVettore(ndim);
	pivot = allocaVettore(ndim);

	// Acquisisco da standard input il vettore dei termini noti
	printf("Inserisci il vettore dei termini noti\n");
	for(i=0;i<ndim;i++) scanf(" %lf", &(terminiNoti[i]));
	
	// Riempio la matrice con i coeff di Hilbert
	for(i=0;i<ndim;i++) for(j=0;j<ndim;j++) m[i][j] = 1.0/(i+j+1.0);
		
	// Fattorizzo la matrice
	fattorizzazioneLU(&m, &pivot, ndim);	// Fattorizzo la matrice eseguendo il pivoting.
											// Nel vettore pivot scrivo le informazioni per ricostruire gli scambi

	
	// Libero la memoria allocata
	liberaMatrice(m, ndim);
	free(pivot);
	free(terminiNoti);
	free(soluzione);

	//Termino il programma
	return 0;
}

Matrice allocaMatrice(const size_t ndim)
{
	size_t i;
	Matrice m;

	m = (Matrice)malloc(ndim * sizeof(Vettore));
	
	if (m == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
	}
	
	for (i = 0; i < ndim; i++) m[i] = allocaVettore(ndim);

	return m;
}

void liberaMatrice(Matrice m, const size_t ndim)
{
	size_t i;

	for (i = 0; i < ndim; i++) free(m[i]);
	free(m);
}

Vettore allocaVettore(const size_t ndim)
{
	Vettore v;

	v = (Vettore)malloc(ndim * sizeof(Elemento));
	
	if (v == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
	}

	return v;
}

void fattorizzazioneLU(Matrice* m, Vettore* pivot, const size_t ndim)
{
	/*size_t k, i, j;

	for(k=0; k<ndim-1; k++)
	{
		// ricerca elemento pivot e scambio delle righe
		for(i=k+1; i<ndim; i++)
			if(abs(*(m[k][k])-0.0)>TOL)
			{
				*(m[i][k]) = (*m[i][k]) / (*m[k][k]);
				for(j=k+1; j<ndim; j++)
					*(m[i][j]) -= (*m[i][k]) * (*m[k][j]);
			}
		//else // messaggio di errore
	}
	*/
}

Vettore forwardSubstitution(const Matrice m, const Vettore pivot, const Vettore terminiNoti)
{
	return terminiNoti;
}

Vettore backwardSubstitution(const Matrice m, const Vettore pivot, const Vettore terminiNoti)
{
	return terminiNoti;
}
