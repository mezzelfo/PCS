#include <stdio.h>
#include <stdlib.h>

struct data
{
    int n;
    float f;
    char s[6 + 1];
    struct data *next;
};

int main()
{
    struct data *tmp, *head = NULL;
    FILE *fp;

    fp = fopen("data_es2_input", "r");
    tmp = (struct data *)malloc(sizeof(struct data));
    while (fscanf(fp, " %d %f %6s", &(tmp->n), &(tmp->f), tmp->s) != EOF)
    {
        tmp->next = head;
        head = tmp;
        tmp = (struct data *)malloc(sizeof(struct data));
    }
    fclose(fp);

    fp = fopen("data_es2_output", "w");
    while (head != NULL)
    {
        fprintf(fp, " %d %f %6s\n", head->n, head->f, head->s);
        tmp = head;
        free(head);
        head = tmp->next;
    }
    fclose(fp);

    free(head);
    return 0;
}
