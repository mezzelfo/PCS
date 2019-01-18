#include <stdio.h>
#include "tool.h"

int main()
{
	// Variabili
	size_t ndim;
	size_t i,j;
	Matrice m;
	int* pivot;
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

	// Acquisisco da standard input il vettore dei termini noti
	printf("Inserisci il vettore dei termini noti\n");
	for(i=0;i<ndim;i++) scanf(" %lf", &(terminiNoti[i]));
	
	// Riempio la matrice con i coeff di Hilbert
	for(i=0;i<ndim;i++) for(j=0;j<ndim;j++) m[i][j] = 1.0/(i+j+1.0);
	
	print(m,ndim);
	// Fattorizzo la matrice
	pivot = fattorizzazioneLU(&m, ndim);	// Fattorizzo la matrice eseguendo il pivoting.
											// Nel vettore pivot scrivo le informazioni per ricostruire gli scambi
	printf("Vettore pivot:\n");
	for(i=0;i<ndim;i++) printf("%d\t", pivot[i]);
	printf("Fine\n");
	print(m,ndim);
	// Risolvo il sistema lineare
	soluzione = forwardSubstitution(m, terminiNoti, ndim);

	printf("sono qui fine\n");
	// Libero la memoria allocata
	liberaMatrice(m, ndim);
	free(pivot);
	free(terminiNoti);
	free(soluzione);

	//Termino il programma
	return 0;
}
