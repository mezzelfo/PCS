#include <stdio.h>
#include "tool.h"

int main()
{
	// Variabili
	size_t ndim;
	size_t i,j;
	Matrice matrice;
	Vettore terminiNoti;
	Vettore soluzione;

	// Istruzioni
	// Acquisisco da standard input la dimensione della matrice
	printf("Inserisci la dimensione della matrice\n");
	scanf(" %lu", &ndim);

	// Alloco la matrice e il vettore dei termini noti
	matrice = allocaMatrice(ndim);
	terminiNoti = allocaVettore(ndim);

	// Acquisisco da standard input il vettore dei termini noti
	printf("Inserisci il vettore dei termini noti\n");
	for(i=0;i<ndim;i++) scanf(" %lf", &(terminiNoti[i]));
	
	// Riempio la matrice con i coeff di Hilbert
	for(i=0;i<ndim;i++) for(j=0;j<ndim;j++) matrice[i][j] = 1.0/(i+j+1.0);
	
	// Risolvi il sistema lineare tramite PA=LU=Py
	soluzione = risolviSistemaLineare(matrice, terminiNoti, ndim);

	// Stampo le soluzioni
	printf("Soluzione:\n");
	for(i=0;i<ndim;i++) printf("%f\n",soluzione[i]);

	// Libero la memoria allocata
	liberaMatrice(matrice, ndim);
	free(terminiNoti);
	free(soluzione);

	//Termino il programma
	return 0;
}
