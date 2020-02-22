#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED

/* Define o tipo do vértice para inteiro */
#define type int

/* Estrutura de um elemento da pilha */
typedef struct ElementoPilha
{
    int no;                         /* Referência do nó contido na pilha */
    struct ElementoPilha* prox;     /* Referência do próximo elemento da pilha */
    struct ElementoPilha* ant;      /* Referência do elemento anterior da pilha */
} ElementoPilha;

/* Estrutura da pilha */
typedef struct TPilha
{
    struct ElementoPilha* ini;      /* Referência de início da pilha */
    struct ElementoPilha* fim;      /* Referência de fim da pilha */
} TPilha;

/* Essa função verifica se uma pilha está vazia ou não */
int VerificaPilhaVazia(TPilha* f);

/* Essa função cria uma pilha */
TPilha* CriaPilha();

/* Essa função insere um elemento (nó) na pilha */
TPilha* InserePilha(TPilha* f, type no);

/* Essa função retira o primeiro elemento da pilha e insere no nó n */
TPilha* RetiraPilha(TPilha* f, type* n);

/* Essa função apaga todos os elementos da pilha */
TPilha* ApagaPilha(TPilha* f);

#endif // PILHA_H_INCLUDED


