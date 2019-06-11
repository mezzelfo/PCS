#include <stdio.h>
#include <stdlib.h>

int main()
{
    // N: dimesione del vettore. vett indirizzo del vettore. i e tmp variabili d'appoggio
    unsigned N, i;
    char tmp, *vett;

    // Leggo da stdin la dimensione N e alloco la memoria, controllando eventuali errori.
    printf("Inserire la dimensione del vettore: ");
    scanf(" %d", &N);
    vett = (char *)malloc(N * sizeof(char));
    if (vett == NULL)
        exit(EXIT_FAILURE);

    // Leggo un carattere alla volta da stdin
    printf("Inserire i %d caratteri\n", N);
    for (i = 0; i < N; i++)
        scanf(" %c", &(vett[i]));

#if VERBOSITY >= 1
    for (i = 0; i < N; i++)
        printf("Carattere %d: %c\n", i, vett[i]);
#endif

    // Rigiro il vettore
    for (i = 0; i < N / 2; i++)
    {
#if VERBOSITY >= 2
        printf("Scambio %c con %c\n", vett[i], vett[N - i - 1]);
#endif
        // Scambio dei caratteri
        tmp = vett[i];
        vett[i] = vett[N - i - 1];
        vett[N - i - 1] = tmp;
    }

    // Stampo il risultato
    printf("Risultato:\n");
    for (i = 0; i < N; i++)
        printf("%c\n", vett[i]);
    // Libero la memoria e termino
    free(vett);
    return 0;
}