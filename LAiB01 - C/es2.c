#include <stdio.h>
#include <stdlib.h>

struct data
{
    int n;
    float f;
    char s[6 + 1];
};

int main()
{
    struct data tmp, *vett = NULL;
    int i, N = 0, size = 1;
    FILE *fp;

    fp = fopen("data_es2_input", "r");
    while (fscanf(fp, " %d %f %6s", &(tmp.n), &(tmp.f), tmp.s) != EOF)
    {
        if (size == N + 1)
        {
            size *= 2;
            vett = (struct data *)realloc(vett, size * sizeof(struct data));
        }
        vett[N] = tmp;
        N++;
    }
    fclose(fp);

    fp = fopen("data_es2_output", "w");
    for (i = N - 1; i >= 0; i--)
        fprintf(fp, " %d %f %6s\n", vett[i].n, vett[i].f, vett[i].s);
    fclose(fp);

    free(vett);
    return 0;
}
