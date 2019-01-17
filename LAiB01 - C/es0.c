#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Variabili
	int n;		// Numero di caratteri da leggere
	int i;		// Variabile di ciclo
	char* p;	// Vettore per immagazzinare i caratteri
	char temp;	// Variabile d'appoggio per lo scambio dei caratteri

	// Istruzioni
	// Acquisisco da standard input il numero di caratteri da immagazzinare
	printf("Inserisci la dimensione del vettore\n");
	scanf(" %d", &n);

	// Alloco memoria richiesta
	p = (char*)malloc(sizeof(char)*n);

	// Controllo che l'allocazione sia andata a buon fine. In caso negativo esco.
	if(p==NULL)
	{
		fprintf(stderr, "Allocazione non riuscita\n");
		return -1;
	}

	// Leggo i caratteri da standard input
	printf("Inserisci i %d caratteri\n", n);
	for (i = 0; i < n; ++i)
	{
		scanf(" %c", &(p[i]));
		#if VERBOSITY >= 1
		printf("Ho letto %c\n", p[i]);
		#endif
	}

	// Rigiro il vettore:
	// Il ciclo scambia per la prima metà del vettore
	// ogni elemento con il suo speculare.
	printf("Rigiro il vettore\n");
	for (i = 0; i <= (int)(n/2-1); ++i)
	{
		temp = p[i];
		p[i] = p[n-i-1];
		p[n-i-1] = temp;
		#if VERBOSITY >= 2
		printf("Ho scambiato %c con %c\n", p[i], p[n-i-1]);
		#endif
	}

	// Stampo il vettore rigirato
	printf("Stampo il vettore\n");
	for (i = 0; i < n; ++i)
	{
		printf("%c\n", p[i]);
	}

	// Libero la memoria allocata
	free(p);

	//Termino il programma
	return 0;
}
