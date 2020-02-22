#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TPilha.h"

/* Essa função verifica se uma pilha está vazia ou não */
int VerificaPilhaVazia(TPilha* f)
{
    return (f->fim == NULL); /* Verifica se o início da pilha é null */
}

/* Essa função cria uma pilha */
TPilha* CriaPilha()
{
    TPilha* f = (TPilha*) malloc (sizeof(TPilha));  /* Cria a nova célula da pilha */
    f->ini = f->fim = NULL;                         /* Seta o início e o fim da pilha pra null, pois está vazia */
    return f;                                       /* Retorna a referência da pilha criada */
}

/* Essa função insere um elemento (nó) na pilha */
TPilha* InserePilha(TPilha* f, type no)
{
    /* Aloca os espaços de memória */
    ElementoPilha* novo = (ElementoPilha*) malloc(sizeof(ElementoPilha));

    novo->no = no;      /* Copia os dados do nó */

    novo->prox = NULL;          /* Liga a referência de próxima célula e anterior pra null */
    novo->ant = f->fim;         /* Liga a referência de ant da nova célula para o atual topo da pilha */

    if(!VerificaPilhaVazia(f))      /* Se a pilha não está vazia, então a nova célula será a última da pilha */
        f->fim->prox = novo;        /* Insere a nova célula no topo da pilha */
    else
        f->ini = novo;              /* Se a pilha está vazia, então a nova célula será a primeira da pilha */
    f->fim = novo;                  /* Atualiza a referência de fim da pilha para a nova célula criada */
    return f;                       /* Retorna a referência da pilha atualizada */
}

/* Essa função retira o primeiro elemento da pilha e insere no nó n */
TPilha* RetiraPilha(TPilha* f, type* n)
{
    if(VerificaPilhaVazia(f))        /* Se a pilha está vazia */
    {
        f->ini = f->fim = NULL;     /* Seta o inicio e o fim da pilha pra null */
        return f;                   /* Retorna a referência da pilha */
    }

    /* Cria um nó e copia nele os dados do nó da pilha */
    *n = f->fim->no;                /* Guarda o valor */

    if (f->fim->ant != NULL)    /* Se a fila tem mais de um elemento */
    {
        ElementoPilha* t = f->fim->ant;     /* Armazena a penúltima posição da pilha */
        f->fim->ant->prox = NULL;           /* Liga a referência do prox do penúltimo elemento para NULL, pois ele será o novo topo da pilha */
        free(f->fim);                       /* Apaga a célula da última posição da pilha */
        f->fim = t;                         /* Retrocede o fim para o penúltimo elemento da pilha */
    }
    else    /* Se a fila tem apenas um elemento */
        f->fim = NULL;     /* Seta o fim da pilha pra null */
    if(f->fim == NULL)
        f->ini == NULL;
    return f;                           /* Retorna a referência de início da pilha */
}

/* Essa função apaga todos os elementos da pilha */
TPilha* ApagaPilha(TPilha* f)
{
    if(VerificaPilhaVazia(f))       /* Se a pilha está vazia */
    {
        f->ini = f->fim = NULL;     /* Seta o inicio e o fim da pilha pra null */
        return f;                   /* Retorna a referência da pilha */
    }
    ElementoPilha* p = f->ini;      /* Armazena a primeira posição da pilha */
    while(p != NULL)                /* Enquanto a pilha não estiver vazia */
    {
        ElementoPilha* t = p->prox; /* Guarda a posição do próximo elemento da pilha */
        free(p);                    /* Apaga a célula da posição atual */
        p = t;                      /* Avança para o próximo elemento da pilha */
    }
    f->ini = f->fim = NULL;         /* Seta o início e o fim da pilha como null */
    free(f);                        /* Apaga a pilha */
    return f;                       /* Retorna a referência de início da pilha */
}
