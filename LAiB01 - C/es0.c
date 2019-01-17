#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n;
	printf("Inserisci la dimensione del vettore\n");
	scanf(" %d", &n);
	//Alloco memoria
	char* p = (char*)malloc(sizeof(char)*n);
	//check null
	if(p==NULL)
	{
		fprintf(stderr, "Allocazione non riuscita\n");
	}

	printf("Inserisci i %d caratteri\n", n);
	for (int i = 0; i < n; ++i)
	{
		scanf(" %c", &(p[i]));
		#if VERBOSITY >=1
		printf("Ho letto %c\n", p[i]);
		#endif
	}

	printf("Permuto il vettore\n");
	for (int i = 0; i <= (int)(n/2-1); ++i)
	{
		char temp = p[i];
		p[i] = p[n-i-1];
		p[n-i-1] = temp;
		#if VERBOSITY >=2
		printf("Ho scambiato %c con %c\n", p[i], p[n-i-1]);
		#endif
	}

	printf("Stampo il vettore\n");
	for (int i = 0; i < n; ++i)
	{
		printf("%c\n", p[i]);
	}
	free(p);
	return 0;
}
