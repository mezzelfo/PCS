#include <stdio.h>
#include <stdlib.h>
#include "tool.h"

// Prototipo funzione che rigira un vettore di caratteri lungo n
void rigira(char* v, const int n);

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

	// Rigiro il vettore. Chiamata alla funzione apposita
	printf("Rigiro il vettore\n");
	rigira(vett, n);

	// Stampo il vettore rigirato
	printf("Stampo il vettore\n");
	for (i = 0; i < n; ++i)
		printf("%c\n", vett[i]);

	// Libero la memoria allocata
	free(vett);

	//Termino il programma con successo
	return 0;
}

// Implementazione del prototipo sopra dichiarato
void rigira(char* v, const int n)
{
	// Variabile di ciclo	
	int i;

	// Ciclo che rigira v
	for (i = 0; i <= (int)(n/2-1); ++i)
	{
		char temp;	// Variabile d'appoggio per lo scambio dei caratteri
		temp = v[i];
		v[i] = v[n-i-1];
		v[n-i-1] = temp;
		#if VERBOSITY >= 2
		printf("Ho scambiato %c con %c\n", v[i], v[n-i-1]);
		#endif
	}
}