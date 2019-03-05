#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

int main()
{
	// Variabili
	int n;		// Numero di caratteri da leggere
	int i;		// Variabile di ciclo
	char* vett;	// Vettore per immagazzinare i caratteri

	// Istruzioni
	// Acquisisco da standard input il numero di caratteri da immagazzinare
	printf("Inserisci la dimensione del vettore\n");
	if(scanf(" %d", &n) != 1)
		runtimeError("Non ho capito la dimensione");

	// Alloco memoria richiesta in modo sicuro
	vett = (char*) secAlloc(sizeof(char)*n);

	// Leggo i caratteri da standard input
	printf("Inserisci i %d caratteri\n", n);
	for (i = 0; i < n; ++i)
	{
		if(scanf(" %c", &(vett[i]))!=1)
			runtimeError("Non ho capito il carattere appena inserito");
		#if VERBOSITY >= 1
		printf("Ho letto %c\n", vett[i]);
		#endif
	}

	// Rigiro il vettore:
	// Il ciclo scambia per la prima metà del vettore
	// ogni elemento con il suo speculare
	printf("Rigiro il vettore\n");
	for (i = 0; i <= (int)(n/2-1); ++i)
	{
		char temp;	// Variabile d'appoggio per lo scambio dei caratteri
		temp = vett[i];
		vett[i] = vett[n-i-1];
		vett[n-i-1] = temp;
		#if VERBOSITY >= 2
		printf("Ho scambiato %c con %c\n", vett[i], vett[n-i-1]);
		#endif
	}

	// Stampo il vettore rigirato
	printf("Stampo il vettore\n");
	for (i = 0; i < n; ++i)
		printf("%c\n", vett[i]);

	// Libero la memoria allocata
	free(vett);

	//Termino il programma
	return 0;
}
