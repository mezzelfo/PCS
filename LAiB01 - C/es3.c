#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s
{
	int n;
	float f;
	char c[6];
	struct s* back;
	struct s* next;
} myStruct;

int main(int argc, char** argv)
{

	FILE* fp;
	myStruct* ptr;
	myStruct* ptrOld;

	int size = 0;

	fp = fopen("data_es2_input","r");
	if (fp==NULL)
	{
		fprintf(stderr, "Errore nell'apertura del file\n");
		return -1;
	}

	ptrOld = NULL;
	ptr = (myStruct*)malloc(sizeof(myStruct)); size++;
	

	while(fscanf(fp," %d %f %s\n",&(ptr->n), &(ptr->f), ptr->c) != EOF )
	{
		ptr->back = ptrOld;
		ptrOld = ptr;
		ptr = (myStruct*)malloc(sizeof(myStruct)); size++;
		ptrOld->next = ptr;
	}
	free(ptr);
	ptr = ptrOld;

	
	fclose(fp);

	fp = fopen("data_es2_output","w");
	if (fp==NULL)
	{
		fprintf(stderr, "Errore nell'apertura del file\n");
		return -1;
	}


	while(ptr->back!=NULL)
	{
		fprintf(fp," %d %f %s\n", ptr->n, ptr->f, ptr->c);
		ptr = ptr->back;
		free(ptr->next);
	}
	fprintf(fp," %d %f %s\n", ptr->n, ptr->f, ptr->c);
	free(ptr);
	
	fclose(fp);
	return 0;
}
