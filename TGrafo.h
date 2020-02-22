#include "TListaNave.h"
#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

/* Define o tipo do vértice para inteiro */
#define type int

/* Estrutura da lista de adjacências de cada vértice */
typedef struct elementoAdjacente *ElementoAdjacente;
struct elementoAdjacente
{
    type w;                     /* Vértice 'w' adjacente a 'v' */
    ElementoAdjacente prox;     /* Referência do pŕoximo vértice adjacente */
};

/* Estrutura de um vértice */
typedef struct elementoVertice *ElementoVertice;
struct elementoVertice {
    type v;             /* Valor do vértice */
    type troca;         /* Vértice no qual este vértice deve ser trocado */
    int cor;            /* Cor do vértice */
    type d;             /* Distância do vértice até alguém */
    type pai;           /* Pai do vértice */
    type grau;          /* Grau do vértice */
    int nave;           /* Nave na qual o vértice está inserido */
};

/* Estrutura de um grafo */
struct grafo
{
    int V;                      /* Total de vértices do grafo */
    int E;                      /* Total de arestas do grafo */
    ElementoAdjacente* adj;     /* Lista de adjacências do grafo */
    ElementoVertice* dv;        /* Lista de vértices do grafo */
    TLista* naves;              /* Lista de naves do grafo */
};
typedef struct grafo *TGrafo;    /* Um TGrafo é um ponteiro para um grafo. */

/* Esse procedimento executa o software */
void executa(char* arqIn, char* arqOut);

#endif // GRAFO_H_INCLUDED











