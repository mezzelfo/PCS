#include <stdio.h>
#include <stdlib.h>

typedef struct s {
	int n;
	float f;
	char c[6+1];
} myStruct;

int main(int argc, char** argv)
{
	FILE* fp;
	fp = fopen("data_es2_input","r");
	if (fp==NULL)
	{
		fprintf(stderr, "Errore nell'apertura del file\n");
		return -1;
	}
	int size = 2;
	myStruct element;
	myStruct* vect = (myStruct*)malloc(sizeof(myStruct)*size);
	int riga = 0;

	while(fscanf(fp," %d %f %s\n",&(element.n), &(element.f), element.c)!= EOF)
	{
		if(riga<size-1)
		{
			vect[riga] = element;
		}
		else
		{
			size *= 2;
			vect = realloc(vect,size);
			vect[riga] = element;
		}

		riga++;
	}

	fclose(fp);

	
	fp = fopen("data_es2_output","w");
	if (fp==NULL)
	{
		fprintf(stderr, "Errore nell'apertura del file\n");
		return -1;
	}

	for(int i=riga-1;i>=0;i--)
	{
		fprintf(fp, " %d %f %s\n", vect[i].n, vect[i].f, vect[i].c);
	}

	fclose(fp);
	free(vect);
	return 0;
}
