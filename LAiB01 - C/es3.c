#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Data
{
	int n;
	float f;
	char c[6+1];
};

struct Nodo
{
	struct Data data;
	struct Nodo* prec;
	struct Nodo* succ;
};

struct Lista
{
	struct Nodo* testa;
	struct Nodo* coda;
};

struct Lista inizializzaLista();							// Prepara la lista per essere usata
void aggiungiLista(struct Lista* lst, const struct Data d);	// Costruisce un nodo e lo aggiunge in coda alla lista
void liberaLista(struct Nodo* nodo);						// Libera la memoria di tutta la lista a ritroso partendo da param:nodo

int main(int argc, char** argv)
{
	// Variabili
	FILE* fp;
	struct Lista lst;
	struct Data d;
	struct Nodo* attuale;

	// Istruzioni
	// Imposto i parametri iniziali della lista
	lst = inizializzaLista();

	// Apro il file di input in modalità lettura
	fp = fopen("data_es2_input","r");

	// Controllo se l'apertura sia andata a buon fine. In caso negativo esco
	if (fp==NULL)
	{
		fprintf(stderr, "Apertura file di input non riuscita\n");
		return -1;
	}

	// Ciclo per leggere tutte le righe. Ogni volta leggo la riga e la aggiungo alla lista
	while(fscanf(fp," %d %f %s\n",&(d.n), &(d.f), d.c) != EOF ) aggiungiLista(&lst, d);
	
	// Chiudo il file di input
	fclose(fp);

	// Apro il file di output in modalità scrittura
	fp = fopen("data_es2_output","w");
	if (fp==NULL)
	{
		fprintf(stderr, "Apertura file di output non riuscita\n");
		return -2;
	}
	
	// Ciclo per visitare la lista al contrario
	attuale = lst.coda;
	while(attuale != NULL)
	{
		// Stampo su file
		fprintf(fp, " %d %f %s\n", attuale->data.n, attuale->data.f, attuale->data.c);
		attuale = attuale->prec;
	}

	// Chiusura del file di output
	fclose(fp);

	// Libero la memoria allocata
	liberaLista(lst.coda);

	//Termino il programma con successo
	return 0;
}

struct Lista inizializzaLista()
{
	struct  List lst;
	lst.testa = NULL;
	lst.coda = NULL;
	return lst;
}

void aggiungiLista(struct Lista* lst, const struct Data d)
{
	// Alloco la memoria del nodo
	struct Nodo* nodo = (struct Nodo*)malloc(sizeof(struct Nodo));

	// Copio i dati
	nodo->data = d;

	#if VERBOSITY >= 1
	printf("Aggiungo riga: %d, vett: %p\n",nodo->data.n,(void*)nodo);
	#endif

	// Aggiungo il nodo alla lista
	if (lst->testa == NULL)			// Se la lista è vuota
	{
		lst->testa = nodo;			// Il primo elemento è il nodo appena creato
		nodo->prec = NULL;			// quindi non ha alcun precedente
	}
	else							// Se la lista non è vuota
	{
		lst->coda->succ = nodo;		// Aggiungo come successore dell'ultimo elemento il nodo appena creato
		nodo->prec = lst->coda;		// Il precedente del nodo appena creato è l'ultimo elemento della lista
	}
	nodo->succ = NULL;				// In ogni caso non c'è un successore (per ora) del nodo appena creato
	lst->coda = nodo;				// Aggiorno il puntatore all'ultimo elemento della lista
}

void liberaLista(struct Nodo* nodo)
{
	#if VERBOSITY >= 1
	printf("Libero riga: %d, vett: %p\n",nodo->data.n,(void*)nodo);
	#endif

	// Chiamata ricorsiva per distruggere l'elemento precedente se esistente
	if(nodo->prec != NULL) liberaLista(nodo->prec);

	// Libero la memoria allocata dal nodo
	free(nodo);
}
