#include <stdlib.h>
#include <stdio.h>
#include <math.h>


int allocaMatrice(double*** m,int ndim)
{
	int i;
	*m = ((double**)(malloc(ndim * sizeof(double*))));

	if (*m == NULL)
	{
		fprintf(stderr, "Allocazione non riuscita\n");
		return -1;
	}
	

	for (i = 0; i < ndim; ++i)
	{
		(*m)[i] = (double*)malloc(ndim * sizeof(double));
		if ((*m)[i] == NULL)
		{
			fprintf(stderr, "Allocazione non riuscita\n");
			return -1;
		}
	}
	return 0;
}

double hilbert(int x, int y) {return 1.0/(x+y+1);}

void riempi(double*** m, int ndim, double f(int, int))
{
	int i, j;
	for (i = 0; i < ndim; ++i)
	{
		for (j = 0; j < ndim; ++j)
		{
			(*m)[i][j] = f(i,j);
		}
	}
}

void stampa(double*** const m, int ndim)
{
	int i,j;
	for (i = 0; i < ndim; ++i)
	{
		for (j = 0; j < ndim; ++j)
		{
			printf("%f\t", (*m)[i][j]);
		}
		printf("\n");
	}
}

void LUFactor(double*** m,int** pivot, int ndim)
{
	int i,j,k;
	*pivot = (int*)malloc(ndim*sizeof(int));
	for(i=0; i<ndim; i++) (*pivot)[i]=i;


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
		printf("scambio riga %d con %d\n", ind_max, k);
		//voglio scambiare la riga k con la riga ind_max
		double* tmp = (*m)[ind_max];
		(*m)[ind_max] = (*m)[k];
		(*m)[k] = tmp;

		int temp = (*pivot)[ind_max];
		(*pivot)[ind_max] = (*pivot)[k];
		(*pivot)[k] = temp;


		for (i = k+1; i < ndim; i++)
		{
			if((*m)[k][k]!=0.0)//Reimplement relative error 1e-15
			{
				(*m)[i][k] = (*m)[i][k]/(*m)[k][k];
				for (j = k+1; j < ndim; j++)
				{
					(*m)[i][j] -= (*m)[i][k]*(*m)[k][j];
				}
			}
			else
			{
				printf("NOPE\n");
			}
		}
	}
}

void forwardSolution(double** a, double** x, double* y, int ndim)
{
	printf("Forward subs\n");
	for (int m = 0; m < ndim; m++)
	{
		double sum = 0.0;
		for (int i = 0; i < m; ++i)
		{
			sum += a[m][i]*(*x)[i];
		}
		(*x)[m] = (y[m] - sum);
	}
}

void backwardSolution(double** a, double** x, double* y, int ndim)
{
	printf("Backward subs\n");
	for (int m = ndim-1; m >= 0; m--)
	{
		double sum = 0.0;
		for (int i = m+1; i < ndim; ++i)
		{
			sum += a[m][i]*(*x)[i];
		}
		(*x)[m] = (y[m] - sum)/a[m][m];
	}
}

int	main()
{
	int ndim; 			//Dimensione Matrice
	double** matrix;	//Puntatore a Puntatore a double
	int* pivot;
	double *y, *x, *b;
	int i;

	printf("Inserisci la dimensione della matrice: ");
	scanf("%d", &ndim);

	printf("Alloco la matrice\n");
	
	if(allocaMatrice(&matrix, ndim))
	{
		printf("Errore nella memoria\n");
		return -1;
	}
	
	printf("Riempio la matrice\n");
	riempi(&matrix,ndim,&hilbert);
	
	printf("Fattorizzo la matrice\n");
	LUFactor(&matrix, &pivot, ndim);

	printf("Stampo la matrice\n");
	stampa(&matrix, ndim);

	printf("Pivot:\n");
	for (i = 0; i < ndim; ++i) printf("%d\t", pivot[i]+1);
	printf("\n");



	b = (double*)calloc(ndim,  sizeof(double));
	for (i = 0; i < ndim; ++i) b[pivot[i]]=i+2;

	
	y = (double*)calloc(ndim,  sizeof(double));
	x = (double*)calloc(ndim,  sizeof(double));
	
	
	forwardSolution(matrix, &y, b, ndim);
	backwardSolution(matrix, &x, y, ndim);
	
	printf("Termini noti:\n");
	for (i = 0; i < ndim; ++i) printf("%f\t", b[i]);
	printf("\n");

	printf("Solution:\n");
	for (i = 0; i < ndim; ++i) printf("%f\t", x[i]);
	printf("\n");

	for(i=0; i<ndim; i++)
	{
		free(matrix[i]);
	}
	free(matrix);
	free(pivot);
	free(x);
	free(y);
	free(b);


	return 0;
}
