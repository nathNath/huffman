#include <stdio.h>
#include <stdlib.h>


/* Definição da Árvore */
typedef struct arvoreHuff{

    char aresta;
    int byte, frequencia;
    struct arvoreHuff *cima, *esq, *dir;

} arvoreHuff;

/* Definição da Lista */
typedef struct listaHuff{

    int n; // Números de Elementos da listaHuff
    //arvoreHuff *folha;
    //struct listaHuff *prox, *cabeca;

} listaHuff;
