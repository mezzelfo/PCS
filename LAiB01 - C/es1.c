#include <stdio.h>
#include <stdlib.h>

// vett: puntatore a vettore di caratteri.
// Scambiare caratteri in posizione i e j
void scambia(char *vett, unsigned i, unsigned j)
{
    char tmp = vett[i];
    vett[i] = vett[j];
    vett[j] = tmp;
}

int main()
{
    // N: dimesione del vettore. vett indirizzo del vettore. i variabile d'appoggio
    unsigned N, i;
    char *vett;

    // Leggo da stdin la dimensione N e alloco memoria, controllando per errori.
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
        // Scambio dei caratteri tramite funzione
        scambia(vett, i, N - i - 1);
    }

    // Stampo il risultato, libero la memoria e termino
    printf("Risultato:\n");
    for (i = 0; i < N; i++)
        printf("%c\n", vett[i]);
    free(vett);
    return 0;
}