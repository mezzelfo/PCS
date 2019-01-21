#include "tool.h"

Matrice allocaMatrice(const unsigned ndim)
{
	// Variabili
	unsigned i;
	Matrice m;

	// Alloco memoria
	m = (Matrice)malloc(ndim * sizeof(Vettore));

	// Controllo che l'allocazione sia andata a buon fine
	if (m == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
		exit(EXIT_FAILURE);
	}

	// Alloco i vettori riga
	for (i = 0; i < ndim; i++) m[i] = allocaVettore(ndim);

	// Ritorno la matrice allocata
	return m;
}

void liberaMatrice(Matrice m, const unsigned ndim)
{
	// Variabili
	unsigned i;

	// Libero ogni vettore riga
	for (i = 0; i < ndim; i++) free(m[i]);

	// Libero la matrice (l'unico vettore colonna)
	free(m);
}

Vettore allocaVettore(const unsigned ndim)
{
	// Variabili
	Vettore v;

	// Alloco memoria
	v = (Vettore)malloc(ndim * sizeof(Elemento));
	
	// Controllo che l'allocazione sia andata a buon fine
	if (v == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
		exit(EXIT_FAILURE);
	}

	// Ritorno il vettore allocata
	return v;
}

int* fattorizzazioneLU(Matrice* m, const unsigned ndim)
{
	// Variabili
	unsigned i,j,k;
	int* pivot;
	Vettore tmp;

	// Istruzioni
	// Alloco la memoria per il vettore delle informazioni per ricostruire il pivoting
	pivot = (int*)malloc(ndim*sizeof(int));
	// Riempio il pivot con [0,1,2,3,...] in modo da poi saper riordinarlo
	for(i=0; i<ndim; i++) pivot[i]=i;


	for (k = 0; k<ndim-1; k++)
	{
		// Variabili
		int temp, ind_max;

		//Istruzioni
		// Cerco l'indice dell'elemento per effettuare il pivoting
		ind_max = k;
		for (i = k+1; i < ndim; i++)
		{
			if(fabs((*m)[i][k]) > fabs((*m)[ind_max][k]))
			{
				ind_max = i;
			}
		}

		// Effettuo il pivoting tra la riga k e la riga ind_max
		tmp = (*m)[ind_max];
		(*m)[ind_max] = (*m)[k];
		(*m)[k] = tmp;

		// Effettuo gli stessi cambi sul vettore pivot
		temp = pivot[ind_max];
		pivot[ind_max] = pivot[k];
		pivot[k] = temp;

		// Eseguo l'eliminazione gaussiana
		for (i = k+1; i < ndim; i++)
		{
			if(fabs((*m)[k][k]) > TOL)
			{
				(*m)[i][k] = (*m)[i][k]/(*m)[k][k];
				for (j = k+1; j < ndim; j++)
				{
					(*m)[i][j] -= (*m)[i][k]*(*m)[k][j];
				}
			}
			else
			{
				fprintf(stderr, "Eliminazione Gaussiana non riuscita\n");
				exit(EXIT_FAILURE);
			}
		}
	}

	// Ritorno il vettore contenente le informazioni dei pivoting effettuati
	return pivot;
	
}

Vettore backwardSubstitution(const Matrice a, const Vettore y, const unsigned ndim)
{
	// Variabili
	Vettore x;
	int j;
	unsigned i;

	// Alloco vettore delle incognite
	x = allocaVettore(ndim);

	// Eseguo sostituzione all'indietro
	for (j = ndim-1; j >= 0; j--)
	{
		Elemento sum;
		sum = 0.0;
		for (i = j+1; i < ndim; ++i)
		{
			sum += a[j][i]*x[i];
		}
		x[j] = (y[j] - sum)/a[j][j];
	}

	// Ritorno il vettore di soluzioni
	return x;
}

Vettore forwardSubstitution(const Matrice a, const Vettore y, const unsigned ndim)
{
	// Variabili
	Vettore x;
	unsigned i,j;

	// Alloco vettore delle incognite
	x = allocaVettore(ndim);

	// Eseguo sostituzione in avanti
	for (j = 0; j < ndim; j++)
	{
		Elemento sum;
		sum = 0;
		for (i = 0; i < j; ++i)
		{
			sum += a[j][i]*x[i];
		}
		x[j] = (y[j] - sum);
	}

	// Ritorno il vettore di soluzioni
	return x;
}

Vettore permVett(const int* const pivot, const Vettore y, const unsigned ndim)
{
	// Variabili
	unsigned i;
	Vettore Py;

	// Alloco il vettore permutato dei termini noti
	Py = allocaVettore(ndim);

	// Riempio Py in modo permutato secondo il vettore pivot
	for(i=0;i<ndim;i++) Py[pivot[i]] = y[i];

	// Ritorno il vettore permutato
	return Py;
}

Vettore risolviSistemaLineare(Matrice A, Vettore y, const unsigned ndim)
{
	// Variabili
	int* pivot;
	Vettore Py;
	Vettore tmp;
	Vettore sol;

	// Calcolo la fattorizzazione LU
	pivot = fattorizzazioneLU(&A, ndim);

	// Permutazione vett termini noti
	Py = permVett(pivot, y, ndim);

	// Risoluzione sitema lineare Lz = Py = permVett(pivot, &y)
	tmp = forwardSubstitution(A, Py, ndim);

	// Risoluzione sistema lineare Ux = z = sol
	sol = backwardSubstitution(A, tmp, ndim);

	free(pivot);
	free(Py);
	free(tmp);
	return sol;
}