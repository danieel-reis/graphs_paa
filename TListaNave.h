#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

/* Estrutura de uma nave */
typedef struct TNave
{
    int tamVertices;                /* Total espaço alocado para armazenar os vértices (componentes conexos) na nave */
    int espacoUsadoVertices;        /* Total vértices (componentes conexos) na nave */
    int* vertices;                  /* Componentes conexas da nave */
    char tipo;                      /* Tipo da nave */
    int V;                          /* Quantidade de vértices */
    int E;                          /* Quantidade de arestas */
    int maxGrau;                    /* Maior grau */
    int minGrau;                    /* Menor grau */
    int qtdVmaxGrau;                /* Quantidade de vértices de maior grau */
    int qtdVminGrau;                /* Quantidade de vértices de menor grau */
} TNave;

/* Estrutura de um elemento da lista */
typedef struct ElementoLista
{
    TNave* nave;                    /* Referência da nave */
    struct ElementoLista* prox;     /* Referência do pŕoximo elemento da lista */
    struct ElementoLista* ant;      /* Referência do elemento anterior da lista */
} ElementoLista;

/* Estrutura de uma lista de nós */
typedef struct TLista
{
    int tamanho;                 /* Tamanho da lista */
    struct ElementoLista* ini;   /* Referência de início da lista */
    struct ElementoLista* fim;   /* Referência de fim da lista */
} TLista;

/* Essa função verifica se uma lista está vazia */
int VerificaListaVazia(TLista* l);

/* Essa função cria uma lista vazia */
TLista* CriaListaVazia();

/* Essa função insere um elemento no fim da lista */
TLista* InsereFimLista(TLista* l);

/* Essa função retira o primeiro elemento da lista e insere no nó n */
TLista* RetiraInicioLista(TLista* l, TNave* nave);

/* Essa função apaga todos os elementos da lista */
TLista* ApagaLista(TLista* l);

/* Esse procedimento exibe os dados dos nós de uma lista */
void ImprimeLista(TLista l);

#endif // LISTA_H_INCLUDED

