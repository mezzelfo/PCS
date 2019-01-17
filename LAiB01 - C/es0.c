#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Variabili
	int n;		// Numero di caratteri da leggere
	int i;		// Variabile di ciclo
	char* vett;	// Vettore per immagazzinare i caratteri
	char temp;	// Variabile d'appoggio per lo scambio dei caratteri

	// Istruzioni
	// Acquisisco da standard input il numero di caratteri da immagazzinare
	printf("Inserisci la dimensione del vettore\n");
	scanf(" %d", &n);

	// Alloco memoria richiesta
	vett = (char*)malloc(sizeof(char)*n);

	// Controllo che l'allocazione sia andata a buon fine. In caso negativo esco
	if(vett==NULL)
	{
		fprintf(stderr, "Allocazione non riuscita\n");
		return -1;
	}

	// Leggo i caratteri da standard input
	printf("Inserisci i %d caratteri\n", n);
	for (i = 0; i < n; ++i)
	{
		scanf(" %c", &(vett[i]));
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
	{
		printf("%c\n", vett[i]);
	}

	// Libero la memoria allocata
	free(vett);

	//Termino il programma
	return 0;
}
