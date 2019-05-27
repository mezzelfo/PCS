#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned N, i;
    char tmp, *vett;

    printf("Inserire la dimensione del vettore: ");
    scanf(" %d", &N);
    vett = (char *)malloc(N * sizeof(char));
    if (vett == NULL)
        exit(EXIT_FAILURE);

    printf("Inserire i %d caratteri\n", N);
    for (i = 0; i < N; i++)
        scanf(" %c", &(vett[i]));

#if VERBOSITY >= 1
    for (i = 0; i < N; i++)
        printf("Carattere %d: %c", i, vett[i]);
#endif

    for (i = 0; i < N / 2; i++)
    {
#if VERBOSITY >= 1
        printf("Scambio %c con %c", vett[i], vett[N - i - 1]);
#endif
        tmp = vett[i];
        vett[i] = vett[N - i - 1];
        vett[N - i - 1] = tmp;
    }
    printf("Risultato:\n");
    for (i = 0; i < N; i++)
        printf("%c\n", vett[i]);

    free(vett);
    return 0;
}
