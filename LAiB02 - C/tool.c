#include "tool.h"


Matrice allocaMatrice(const size_t ndim)
{
	size_t i;
	Matrice m;

	m = (Matrice)malloc(ndim * sizeof(Vettore));
	
	if (m == NULL) {
		fprintf(stderr, "Allocazione non riuscita\n");
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
	}

	return v;
}

int* fattorizzazioneLU(Matrice* m, const size_t ndim)
{
	size_t k, i, j, ind_max;
	int* pivot = (int*)malloc(ndim*sizeof(int));
	for(i=0; i<ndim; i++) pivot[i]=i;
	
	for(k=0; k<ndim-1; k++)
	{
		ind_max = k;
		for (i = k+1; i < ndim; i++)
		{
			if(abs((*m)[i][k]) > abs((*m)[ind_max][k]))
			{
				ind_max = i;
			}
		}

		printf("scambio riga %ld con %ld\n", ind_max, k);
		//voglio scambiare la riga k con la riga ind_max
		Vettore tmp = (*m)[ind_max];
		(*m)[ind_max] = (*m)[k];
		(*m)[k] = tmp;

		double temp = pivot[ind_max];
		pivot[ind_max] = pivot[k];
		pivot[k] = temp;


		// ricerca elemento pivot
		for(i=k+1; i<ndim; i++)
			if(abs((*m)[k][k])>TOL)
			{
				(*m)[i][k] = (*m)[i][k] / (*m)[k][k];
				for(j=k+1; j<ndim; j++)
					(*m)[i][j] -= (*m)[i][k] * (*m)[k][j];
			}
		//else // messaggio di errore
	}
	return pivot;
	
}

Vettore forwardSubstitution(const Matrice m, const Vettore terminiNoti, const size_t ndim)
{
	Vettore sol;
	size_t i,j;

	sol = allocaVettore(ndim);
	for (j = 0; j < ndim; j++)
	{
		double sum = 0.0;
		for (i = 0; i < j; ++i)
		{
			sum += m[j][i]*sol[i];
		}
		sol[j] = (terminiNoti[j] - sum);
	}
	return sol;
}

Vettore backwardSubstitution(const Matrice m, const Vettore terminiNoti, const size_t ndim)
{
	Vettore sol;
	int i,j;

	sol = allocaVettore(ndim);
	for (j = ndim-1; j >= 0; j--)
	{
		double sum = 0.0;
		for (i = j+1; i < ndim; ++i)
		{
			sum += m[j][i]*sol[i];
		}
		sol[j] = (terminiNoti[j] - sum)/m[j][j];
	}
	return sol;
}

void print(const Matrice m, const size_t ndim)
{
	size_t i,j;

	for (i = 0; i < ndim; i++)
	{
		for (j = 0; j < ndim; j++)
		{
			printf("%f\t",m[i][j]);
		}
		printf("\n");
	}
}
