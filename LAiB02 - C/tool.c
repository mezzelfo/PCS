#include "tool.h"


Matrice allocaMatrice(const size_t ndim)
{
	size_t i;
	Matrice m;

	m = (Matrice)malloc(ndim * sizeof(Vettore));
	
	if (m == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
		exit(EXIT_FAILURE);
	}
	
	for (i = 0; i < ndim; i++) m[i] = allocaVettore(ndim);

	return m;
}

void liberaMatrice(Matrice m, const size_t ndim)
{
	size_t i;

	for (i = 0; i < ndim; i++) free(m[i]);
	free(m);
}

Vettore allocaVettore(const size_t ndim)
{
	Vettore v;

	v = (Vettore)malloc(ndim * sizeof(Elemento));
	
	if (v == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
		exit(EXIT_FAILURE);
	}

	return v;
}

int* fattorizzazioneLU(Matrice* m, const size_t ndim)
{
	size_t i,j,k;
	int* pivot = (int*)malloc(ndim*sizeof(int));
	for(i=0; i<ndim; i++) pivot[i]=i;


	for (k = 0; k<ndim-1; k++)
	{
		int ind_max = k;
		for (i = k+1; i < ndim; i++)
		{
			if(fabs((*m)[i][k]) > fabs((*m)[ind_max][k]))
			{
				ind_max = i;
			}
		}
		//printf("scambio riga %d con %d\n", ind_max, k);
		//voglio scambiare la riga k con la riga ind_max
		Vettore tmp = (*m)[ind_max];
		(*m)[ind_max] = (*m)[k];
		(*m)[k] = tmp;

		int temp = pivot[ind_max];
		pivot[ind_max] = pivot[k];
		pivot[k] = temp;


		for (i = k+1; i < ndim; i++)
		{
			if(fabs((*m)[k][k]) > TOL)//Reimplement relative error 1e-15
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
	return pivot;
	
}

Vettore backwardSubstitution(const Matrice a, const Vettore y, const size_t ndim)
{
	Vettore x;
	int j;
	size_t i;
	Elemento sum;
	x = allocaVettore(ndim);

	for (j = ndim-1; j >= 0; j--)
	{
		sum = 0.0;
		for (i = j+1; i < ndim; ++i)
		{
			sum += a[j][i]*x[i];
		}
		x[j] = (y[j] - sum)/a[j][j];
	}
	return x;
}

Vettore forwardSubstitution(const Matrice a, const Vettore y, const size_t ndim)
{
	Vettore x;
	size_t i,j;
	Elemento sum;
	x = allocaVettore(ndim);

	for (j = 0; j < ndim; j++)
	{
		sum = 0;
		for (i = 0; i < j; ++i)
		{
			sum += a[j][i]*x[i];
		}
		x[j] = (y[j] - sum);
	}
	return x;
}

Vettore permVett(const int* const pivot, const Vettore y, const size_t ndim)
{
	size_t i;
	Vettore Py;
	Py = allocaVettore(ndim);

	for(i=0;i<ndim;i++)
	{
		Py[pivot[i]] = y[i];
	}
	return Py;
}

Vettore risolviSistemaLineare(Matrice A, Vettore y, const size_t ndim)
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