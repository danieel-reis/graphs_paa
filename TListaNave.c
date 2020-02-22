#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TListaNave.h"

/* Essa função verifica se uma lista está vazia */
int VerificaListaVazia(TLista* l)
{
    return (l->ini == NULL); /* Verifica se o início da lista é null */
}

/* Essa função cria uma lista vazia */
TLista* CriaListaVazia()
{
    TLista* l = (TLista*) malloc (sizeof(TLista));  /* Cria a nova célula da lista */
    l->ini = l->fim = NULL;                         /* Seta o início e o fim da lista pra null, pois está vazia */
    return l;                                       /* Retorna a referência da lista criada */
}

/* Essa função insere um elemento no fim da lista */
TLista* InsereFimLista(TLista* l)
{
    /* Aloca os espaços de memória */
    ElementoLista* novo = (ElementoLista*) malloc(sizeof(ElementoLista));
    novo->nave = (TNave*)malloc(sizeof(TNave));

    /* Copia os dados do nó */
    novo->nave->tipo = 0;
    novo->nave->vertices = NULL;

    novo->prox = NULL;              /* Liga a referência de próxima célula pra null */
    if(VerificaListaVazia(l))       /* Verifica se a lista está vazia */
    {
        novo->ant = NULL;           /* Liga a referência de anterior da nova célula pra null */
        l->ini = novo;              /* Define a nova célula como primeira da lista */
    }
    else
    {
        l->fim->prox = novo;        /* Se a lista não está vazia, então a nova célula sera a última da lista */
        novo->ant = l->fim;         /* Liga a referência de anterior da nova célula para o atual último elemento da lista */
    }
    l->fim = novo;                  /* Atualiza a referência de fim da lista para a nova célula criada */

    l->tamanho++;                   /* Informa que foi adicionado um elemento a lista */
    return l;                       /* Retorna a referência da lista atualizada */
}

/* Essa função retira o primeiro elemento da lista e insere no nó n */
TLista* RetiraInicioLista(TLista* l, TNave* n)
{
    if(VerificaListaVazia(l))       /* Se a lista está vazia */
    {
        l->ini = l->fim = NULL;     /* Seta o início e o fim da lista pra null */
        return l;                   /* Retorna a referência da lista */
    }

    /* Cria um nó e copia nele os dados do nó da lista */
    n->vertices = l->ini->nave->vertices;   /* Guarda as componentes conexas */
    n->tipo = l->ini->nave->tipo;           /* Guarda o tipo */

    ElementoLista* t = l->ini->prox;    /* Armazena a segunda posição da lista */
    free(l->ini);                       /* Apaga a célula da primeira posição da lista */
    l->ini = t;                         /* Avança o início para o próximo elemento da lista */
    if(VerificaListaVazia(l))           /* Se a lista está vazia */
        l->fim = NULL;                  /* Fim da lista é nulo */
    l->tamanho--;                       /* Informa que foi retirado um elemento da lista */
    return l;                           /* Retorna a referência de início da lista */
}

/* Essa função apaga todos os elementos da lista */
TLista* ApagaLista(TLista* l)
{
    if(VerificaListaVazia(l))       /* Se a lista está vazia */
    {
        l->ini = l->fim = NULL;     /* Seta o inicio e o fim da lista pra null */
        return l;                   /* Retorna a referência da lista */
    }
    ElementoLista* p = l->ini;      /* Armazena a primeira posição da lista */
    while(p != NULL)                /* Enquanto a lista não estiver vazia */
    {
        ElementoLista* t = p->prox; /* Guarda a posição do próximo elemento da lista */
        free(p);                    /* Apaga a célula da posição atual */
        p = t;                      /* Avança para o próximo elemento da lista */
    }
    l->ini = l->fim = NULL;         /* Seta o início e o fim da lista como null */
    free(l);                        /* Apaga a lista */
    return l;                       /* Retorna a referência de início da lista */
}

/* Esse procedimento exibe os dados dos nós de uma lista */
void ImprimeLista(TLista l)
{
    if(VerificaListaVazia(&l))          /* Verifica se a lista está vazia */
        return;
    ElementoLista* p;                   /* Ponteiro usado para percorrer cada elemento da lista */
    for (p=l.ini; p!= NULL; p=p->prox)  /* Percorre cada elemento da lista */
    {
        /* Imprime cada nave da lista */
        printf("Type: %d\n", p->nave->tipo);
    }
}

