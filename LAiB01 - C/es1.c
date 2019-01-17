#include <stdio.h>
#include <stdlib.h>

// Prototipo funzione che rigira un vettore di caratteri lungo n
void rigira(char** v, int n);

int main()
{
	// Variabili
	int n;		// Numero di caratteri da leggere
	int i;		// Variabile di ciclo
	char* vett;	// Vettore per immagazzinare i caratteri

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

	// Rigiro il vettore. Chiamata alla funzione apposita
	printf("Rigiro il vettore\n");
	rigira(&vett, n);

	// Stampo il vettore rigirato
	printf("Stampo il vettore\n");
	for (i = 0; i < n; ++i)
	{
		printf("%c\n", vett[i]);
	}

	// Libero la memoria allocata
	free(vett);

	//Termino il programma con successo
	return 0;
}

// Implementazione del prototipo sopra dichiarato
void rigira(char** v, int n)
{
	// Variabile temporanea per eseguire lo scambio
	char temp;

	// Ciclo che rigira v
	for (int i = 0; i <= (int)(n/2-1); ++i)
	{
		char temp = (*v)[i];
		(*v)[i] = (*v)[n-i-1];
		(*v)[n-i-1] = temp;
		#if VERBOSITY >= 2
		printf("Ho scambiato %c con %c\n", (*v)[i], (*v)[n-i-1]);
		#endif
	}
}