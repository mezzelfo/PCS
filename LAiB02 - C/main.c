#include <stdio.h>
#include "tool.h"

int main(int argc, char **argv)
{
	// Variabili
	unsigned ndim;
	unsigned i, j;
	Matrice matrice;
	Vettore terminiNoti;
	Vettore soluzione;

	// Istruzioni
	// Acquisisco da standard input la dimensione della matrice
#ifdef MATLAB_MODE
	sscanf(argv[1], "%d", &ndim);
#else
	printf("Inserisci la dimensione della matrice\n");
	scanf(" %u", &ndim);
#endif

	// Alloco la matrice e il vettore dei termini noti
	matrice = allocaMatrice(ndim);
	terminiNoti = allocaVettore(ndim);

	// Acquisisco il vettore dei termini noti
#ifdef MATLAB_MODE
	for (i = 0; i < ndim; i++)
		terminiNoti[i] = 1;
#else
	printf("Inserisci il vettore dei termini noti\n");
	for (i = 0; i < ndim; i++)
		scanf(" %Lf", &(terminiNoti[i]));
#endif

		// Riempio la matrice con i coeff
#ifdef MATLAB_MODE
	for (i = 0; i < ndim; i++)
		for (j = 0; j < ndim; j++)
			sscanf(argv[2 + i * ndim + j], "%Lf", &(matrice[i][j]));
#else
	for (i = 0; i < ndim; i++)
		for (j = 0; j < ndim; j++)
			matrice[i][j] = 1.0 / (i + j + 1.0);
#endif

	// Risolvi il sistema lineare tramite PA=LU=Py
	soluzione = risolviSistemaLineare(matrice, terminiNoti, ndim);

	// Stampo le soluzioni
	for (i = 0; i < ndim; i++)
		printf("%.20Lf\t", soluzione[i]);

	// Libero la memoria allocata
	liberaMatrice(matrice, ndim);
	free(terminiNoti);
	free(soluzione);

	//Termino il programma
	return 0;
}
