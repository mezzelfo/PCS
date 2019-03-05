#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tool.h"

// Definizione della struttura di ogni riga
typedef struct s {
	int n;
	float f;
	char c[6+1]; //Stringa al più di 6 caratteri
} DatiRiga;

int main()
{
	// Variabili
	FILE* fp;			// Puntatore a file. Usato sia per input che output
	int dim;			// Numero di celle allocate del vettore
	int riga;			// Numero di righe lette
	int i;				// Variabile di ciclo
	DatiRiga e;			// Elemento d'appoggio
	DatiRiga* vett;		// Vettore dove immagazzinare i dati
	DatiRiga* vettTMP;		// Vettore dove immagazzinare i dati

	// Inizializzazione Variabili
	dim = 4;			// Numero stimato di righe. Se necessita, raddoppio
	riga = 0;			// All'inizio ho letto 0 righe...

	// Istruzioni
	// Apro il file di input in modalità lettura in modo sicuro
	fp = secFopenRead("data_es2_input");

	// Alloco memoria vettore in modo sicuro
	vett = (DatiRiga*)secAlloc(sizeof(DatiRiga)*dim);
	
	// Ciclo per leggere tutte le righe. Ogni volta leggo la riga memorizzandola sull'elemento di appoggio
	while(fscanf(fp," %d %f %7s\n",&(e.n), &(e.f), e.c) != EOF)
	{
		#if VERBOSITY >= 1
		printf("Riga: %d, Dim: %d, element: %d %f %s, vett: %p\n",riga,dim,e.n,e.f,e.c,(void*)vett);
		#endif
		// Se non ho più spazio nel vettore, raddoppio la dimensione e rialloco
		if(riga==dim)
		{
			dim = dim * 2;
			#if VERBOSITY >= 1
			printf("Raddoppio con nuova dimensione %d\n",dim);
			#endif
			vettTMP = (DatiRiga*)realloc(vett, dim*sizeof(DatiRiga));
			if (vettTMP==NULL)
			{
				fprintf(stderr, "Reallocazione non riuscita\n");
				fclose(fp);
				return -3;
			}
			vett = vettTMP;
		}
		
		// Immagazzino una copia dell'elemento di appoggio nel vettore
		vett[riga] = e;

		// Incremento il numero di righe lette
		riga++;
	}

	#if VERBOSITY >= 1
	printf("Ho letto tutto. Riga: %d, Dim: %d, vett: %p\n",riga,dim,(void*)vett);
	#endif

	// Chiudo il file di input
	fclose(fp);

	// Apro il file di output in modalità scrittura
	fp = secFopenWrite("data_es2_output");

	// Ciclo per visitare il vettore al contrario
	for(i = riga-1; i >= 0; i--)
		fprintf(fp, " %d %f %s\n", vett[i].n, vett[i].f, vett[i].c); // Stampo su file

	// Chiusura del file di output
	fclose(fp);

	// Libero la memoria allocata. vettTMP è sempre uguale a vett
	free(vett);

	//Termino il programma con successo
	return 0;
}
