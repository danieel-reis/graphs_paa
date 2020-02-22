#include <stdio.h>
#include <stdlib.h>
#include "TGrafo.h"
#include "TPilha.h"
#include "TListaNave.h"

#define COLOR_WHITE 0
#define COLOR_GRAY 1
#define COLOR_BLACK 2

#define TYPE_R 'R'
#define TYPE_F 'F'
#define TYPE_B 'B'
#define TYPE_T 'T'

/* Essa função realiza a inicialização da lista do grafo com V vértices e nenhuma aresta até o momento */
TGrafo InicializaGrafo(int V, int E)
{
    TGrafo G = malloc(sizeof *G);                               /* Cria o espaço de memória para o grafo */
    G->naves = CriaListaVazia();                                /* Cria a lista de naves */
    G->V = V;                                                   /* Seta no grafo o total de vértices */
    G->E = E;                                                   /* Seta no grafo o total de arestas */
    G->adj = malloc(V * sizeof (ElementoAdjacente));            /* Cria o espaço de memória para a lista de adjacências do grafo */
    G->dv = malloc(V * sizeof (ElementoVertice));               /* Cria o espaço de memória para a lista de vértices do grafo */
    for (type v = 0; v < V; v++)                             /* Adiciona e inicializa V vértices no grafo */
    {
        G->dv[v] = malloc(sizeof (struct elementoVertice));     /* Cria o espaço de memória para um vértice do grafo */
        G->dv[v]->cor = COLOR_WHITE;                            /* Seta a cor do vértice como BRANCA */
        G->dv[v]->pai = -1;                                     /* Seta o pai do vértice como -1 (Sem pai) */
        G->dv[v]->d = 0;                                        /* Seta a distância do vértice como zero */
        G->dv[v]->v = v+1;                                      /* Seta o valor do vértice, ou seja, de qual vértice estamos falando */
        G->dv[v]->grau = 0;                                     /* Seta o grau do vértice inicialmente como zero */
    }
    return G;   /* Retorna o vértice criado */
}

/* Esse procedimento realiza a inserção de um vértice 'w' na frente na lista de adjacências de um vértice 'v' do grafo 'G' em que 'w' é adjacente a 'v' */
void InsereAresta(TGrafo G, type v, type w)
{
    ElementoAdjacente ea = malloc(sizeof (struct elementoAdjacente));   /* Cria o espaço de memória do vértice adjacente */
    ea->w = w;                                                          /* Seta o vértice adjacente 'w' adjacente ao vértice 'v' */
    ea->prox = G->adj[v];                                               /* Seta a referência de próximo vértice adjacente a 'v' ao que já tinha */
    G->adj[v] = ea;                                                     /* Insere o novo vértice adjacente no ínicio da lista */
}

/* Essa função insere um elemento num vetor dinâmico */
int* InsereListaDeInteiro(int* ptr, int* tamanhoMax, int* total, int incremento, int valor)
{
    /* Verifica se o vetor é vazio. Caso seja, aloca 'incremento' espaços no vetor */
    if (*tamanhoMax == 0) { ptr = (int *) realloc(ptr, (*tamanhoMax + incremento)*sizeof(int) ); }
    if(ptr) /* Se o vetor for válido */
    {
        /* Verifica se o vetor já está cheio. Caso esteja, realoca mais 'incremento' espaços no vetor */
        if (*total+1 > *tamanhoMax) { ptr = (int *) realloc(ptr, (*tamanhoMax + incremento)*sizeof(int) ); *tamanhoMax += incremento; }
        ptr[*total] = valor;    /* Insere o valor no vetor */
        *total = *total+1;      /* Atualiza o contador de quantos elementos tem no vetor */
    }
    else { printf("Erro ao inserir\n"); free(ptr); exit(1); }
    return ptr; /* Retorna o vetor atualizado com a inserção do elemento */
}

/* Este procedimento identifica cada componente conexa, ou seja, cada nave e identifica o seu tipo */
void DFSComponenteConexa(TGrafo G, char arqOut[])
{
    TPilha* pilha;      /* Pilha usada no algoritmo DFS */
    TNave* nave;        /* Variável que irá guardar a referência de uma nave analisada */
    type u = 0;         /* Variável que irá guardar a referência de um vértice */

    pilha = CriaPilha();                          /* Cria a pilha */
    for (type s = 0; s < G->V; s++)
    {
        if (G->dv[s]->cor != COLOR_BLACK)         /* Se o vértice ainda não foi visitado */
        {
            G->naves = InsereFimLista(G->naves);        /* Cria o espaço de memória para a nave encontrada */
            nave = G->naves->fim->nave;                 /* Atualiza a referência da nave atual */
            
            int incremento = 10;    /* Variável que controla o tamanho de um incremento no vetor de inteiros */
            /* Inicializa os espaços de memória para cada vetor de inteiros */
            nave->vertices = NULL;
            /* Inicializa as variáveis que controlam as dimensões utilizadas x espaço alocado de memória para os vetores de inteiros */
            nave->tamVertices = 0;
            nave->espacoUsadoVertices = 0;
            nave->V = 1;                        /* Inicializa o contador da quantidade de vértices na componente conexa que já tem o vértice inicial */
            nave->E = 0;                        /* Inicializa o contador da quantidade de arestas na componente conexa */
            nave->maxGrau = G->dv[s]->grau;     /* Inicializa o contador de maior grau da componente conexa como sendo o grau do vértice inicial */
            nave->minGrau = G->dv[s]->grau;     /* Inicializa o contador de maior grau da componente conexa como sendo o grau do vértice inicial */
            nave->qtdVmaxGrau = 1;              /* Inicializa a quantidade de vértices de grau mínimo como 1 */
            nave->qtdVminGrau = 1;              /* Inicializa a quantidade de vértices de grau máximo como 1 */
            
            /* Adiciona vértice a componente conexa */
            nave->vertices = InsereListaDeInteiro(nave->vertices, &nave->tamVertices, &nave->espacoUsadoVertices, incremento, s);

            G->dv[s]->nave = G->naves->tamanho;                     /* Marca no vértice a qual nave ele pertence */
            G->dv[s]->cor = COLOR_GRAY;                             /* Deixa o vértice CINZA */
            pilha = InserePilha(pilha, s);                          /* Adiciona na pilha o vértice da origem */

            while(!VerificaPilhaVazia(pilha))                       /* Enquanto tiver elementos na pilha */
            {
                pilha = RetiraPilha(pilha, &u);                     /* Remove o elemento do topo da pilha */
                for (ElementoAdjacente a = G->adj[u]; a != NULL; a = a->prox)    /* Verifica todos os adjacentes do vértice u */
                {
                    nave->E = nave->E+1;   /* Incrementa o contador do tamanho da lista de adjacências do vértice s */

                    if (G->dv[a->w]->cor == COLOR_WHITE)    /* Se a cor do adjacente for BRANCA */
                    {
                        G->dv[a->w]->cor = COLOR_GRAY;          /* Deixa o vértice CINZA */
                        G->dv[a->w]->pai = u;                   /* Seta o pai */
                        G->dv[a->w]->d = G->dv[u]->d+1;         /* Computa a distância para chegar a v como sendo a distância de u+1 */
                        pilha = InserePilha(pilha, a->w);       /* Adiciona na pilha o vértice da origem */
                        
                        /* Adiciona vértice a componente conexa */
                        nave->vertices = InsereListaDeInteiro(nave->vertices, &nave->tamVertices, &nave->espacoUsadoVertices, incremento, a->w);
                        
                        nave->V = nave->V+1;  /* Incrementa o contador do total de vértices da componente conexa */

                        G->dv[a->w]->nave = G->naves->tamanho;   /* Marca no vértice a qual nave ele pertence */

                        if ((G->dv[a->w]->grau) > nave->maxGrau)    /* Contabiliza o maior grau da nave */
                        {
                            nave->maxGrau = G->dv[a->w]->grau;          /* Atualiza o valor do maior grau */
                            nave->qtdVmaxGrau = nave->qtdVmaxGrau+1;        /* Contabiliza a quantidade de vértices que tem grau máximo */
                        }
                        else if ((G->dv[a->w]->grau) == nave->maxGrau)  /* Contabiliza o maior grau da nave */
                            nave->qtdVmaxGrau = nave->qtdVmaxGrau+1;        /* Contabiliza a quantidade de vértices que tem grau máximo */
                        else if ((G->dv[a->w]->grau) < nave->minGrau)   /* Contabiliza o menor grau da nave */
                        {
                            nave->minGrau = G->dv[a->w]->grau;              /* Atualiza o valor do menor grau */
                            nave->qtdVminGrau = nave->qtdVminGrau+1;        /* Contabiliza a quantidade de vértices que tem grau mínimo */
                        }
                        else if ((G->dv[a->w]->grau) == nave->minGrau)  /* Contabiliza o menor grau da nave */
                            nave->qtdVminGrau = nave->qtdVminGrau+1;        /* Contabiliza a quantidade de vértices que tem grau mínimo */
                    }

                    if ((G->dv[s]->grau) > nave->maxGrau)     /* Contabiliza o maior grau da nave */
                        nave->maxGrau = G->dv[s]->grau;       /* Atualiza o valor do maior grau */
                }
                G->dv[u]->cor = COLOR_BLACK;            /* Após deixar todos adjacentes de u CINZA, marca u como PRETO */
            }

            nave->E/=2;    /* Divide por 2 o total de arestas para considerar apenas u->v/v->u e não ambos */
        }
    }

    /* Percorre cada componente conexa caso exista algum elemento na componente conexa e identifica cada tipo de nave */
    if(G->naves->fim->nave->espacoUsadoVertices > 0)
    {
        int totalR = 0, totalF = 0, totalB = 0, totalT = 0;

        int nave = 1;
        ElementoLista* l;   /* Ponteiro para percorrer cada elemento da lista de naves */

        for (l = G->naves->ini; l != NULL; l = l->prox)  /* Percorre cada elemento da lista */
        {
            /* Define o tipo da nave */
            if (l->nave->V == l->nave->E && l->nave->minGrau == 2 && l->nave->maxGrau == 2) /* V=E e Grau mínimo = 2 e Grau máximo = 2 */
            {
                l->nave->tipo = TYPE_T;     /* Nave do tipo TRANSPORTADORA */
                totalT++;                   /* Incrementa o contador de naves desse tipo */
            }
            else if (l->nave->V == l->nave->E+1) /* V-1=E */
            {
                if (l->nave->minGrau == 1 && l->nave->maxGrau == 2)      /* Grau mínimo = 1 e Grau máximo = 2 */
                {
                    l->nave->tipo = TYPE_R;     /* Nave do tipo RECONHECIMENTO */
                    totalR++;                   /* Incrementa o contador de naves desse tipo */
                }
                else
                {
                    l->nave->tipo = TYPE_F;     /* Nave do tipo FRIGATA */
                    totalF++;                   /* Incrementa o contador de naves desse tipo */
                }
            }
            /* V = Vmingrau + Vmaxgrau e E = Vmingrau * Vmaxgrau. Obs: Remove um da soma porque inicialmente ambos são setados com menor e maior */
            else if (
                (l->nave->minGrau == l->nave->maxGrau && l->nave->V == (l->nave->minGrau + l->nave->maxGrau) && l->nave->E == (l->nave->minGrau * l->nave->maxGrau))
                ||
                (l->nave->V == (l->nave->qtdVmaxGrau + l->nave->qtdVminGrau - 1)
                &&
                (l->nave->E == (l->nave->qtdVmaxGrau * (l->nave->qtdVminGrau - 1)) ||
                 l->nave->E == ((l->nave->qtdVmaxGrau - 1) * l->nave->qtdVminGrau))))
            {
                l->nave->tipo = TYPE_B;     /* Nave do tipo BOMBARDEIRO */
                totalB++;                   /* Incrementa o contador de naves desse tipo */
            }

            //printf("\n| Nave %5.0d | V: %9.0d | E:%9.0d | minGrau(%4.0d): %4.0d | maxGrau(%4.0d): %4.0d | Tipo: %c |\t\t",
            //       nave++, l->nave->V, l->nave->E, l->nave->qtdVminGrau, l->nave->minGrau, l->nave->qtdVmaxGrau, l->nave->maxGrau, l->nave->tipo);
            //printf("\n");
            //ElementoFila* p;
            //for (p = l->nave->componentesConexas->ini; p != NULL; p = p->prox)  /* Percorre cada elemento da fila */
            //    printf("%d, ", p->no+1);  /* Imprime cada vértice da nave */
        }
        //printf("\n");
        //printf("%d %d %d %d\n", totalR, totalF, totalB, totalT);
        
        /* Salva no arquivo */
        FILE *arq;  /* Arquivo */
        /* Abre o arquivo */
        arq = fopen(arqOut, "a"); /* Abre o arquivo no modo append (anexar) */
        if(arq == NULL) /* Erro ao abrir o arquivo */
            printf("Erro, nao foi possivel abrir o arquivo\n");
        else /* Abertura do arquivo foi bem sucedida */
            fprintf(arq, "%d %d %d %d\n", totalR, totalF, totalB, totalT);
        fclose(arq);    /* Fecha o arquivo */
    }
}

/* Essa função contabiliza a menor distância entre dois vértices utilizando uma busca em profundidade */
int DFS(TGrafo G, TNave* nave, type s, type v)
{
    TPilha* pilha;      /* Pilha usada no algoritmo DFS */
    type u = 0;         /* Variável que irá guardar a referência de um vértice */
    int pos;            /* Variável que irá guardar a posição da referência de um vértice */

    /* Inicialização de cada vértice da árvore */
    for (type v = 0; v < nave->espacoUsadoVertices; v++)     /* Percorre cada vértice da nave */
    {
        pos = nave->vertices[v];
        G->dv[pos]->cor = COLOR_WHITE;     /* Inicializa o vértice com a cor BRANCA */
        G->dv[pos]->d = 0;                 /* Inicializa o vértice com a distância 0 */
    }
    
    G->dv[s]->cor = COLOR_GRAY;                             /* Deixa o vértice CINZA */

    pilha = CriaPilha();                                    /* Cria a pilha */
    pilha = InserePilha(pilha, s);                          /* Adiciona na pilha o vértice da origem */
    while(!VerificaPilhaVazia(pilha))                       /* Enquanto tiver elementos na pilha */
    {
        pilha = RetiraPilha(pilha, &u);                     /* Remove o elemento do topo da pilha */
        for (ElementoAdjacente a = G->adj[u]; a != NULL; a = a->prox)    /* Verifica todos os adjacentes do vértice u */
        {
            if (G->dv[a->w]->cor == COLOR_WHITE)    /* Se a cor do adjacente for BRANCA */
            {
                G->dv[a->w]->cor = COLOR_GRAY;          /* Deixa o vértice CINZA */
                G->dv[a->w]->d = G->dv[u]->d+1;         /* Computa a distância para chegar a v como sendo a distância de u+1 */
                pilha = InserePilha(pilha, a->w);       /* Insere nó na pilha */
            }

            if (a->w == v)              /* Verifica se é o vértice objetivo */
                return G->dv[v]->d;     /* Retorna o tempo de vantagem */
        }
        G->dv[u]->cor = COLOR_BLACK;    /* Após deixar todos adjacentes de u CINZA, marca u como PRETO */  
    }
    return 0;   /* Retorna a distância 0 caso não encontrar o vértice */
}

/* Esse procedimento calcula o menor tempo de vantagem entre as naves utilizando o LCA (Menor ancestral em comum) */
void TempoDeVantagem(TGrafo G, char arqOut[])
{
    type minTV = -1;        /* Mantém na memória um valor de tempo de vantagem mínimo, visto que o problema é encontrar o menor entre eles */
            
    ElementoLista* l;       /* Ponteiro para percorrer cada elemento da lista de naves */
    int count = 1, pos;
    
    type a, b, s1, s2, lca, distancia, distanciaFim, dlca, d1, d2, soma;
            
    for (l = G->naves->ini; l != NULL; l = l->prox)     /* Percorre cada nave da lista de naves */
    {               
        soma = 0;
        //printf("---> Nave %4.0d\n", count++);
        for (type v = 0; v < l->nave->espacoUsadoVertices; v++)
        {
            pos = l->nave->vertices[v];
            //printf(" (%3d, %3d - %3d|%3d) ", G->dv[pos]->v, G->dv[pos]->troca, G->dv[pos]->pai, G->dv[pos]->d);
                    
            s1 = a = G->dv[pos]->v-1;       /* Guarda a posição 'v' */
            s2 = b = G->dv[pos]->troca-1;   /* Guarda a posição 'troca' que será trocada por 'v' */
                    
            if (s1 != s2)   /* Se um vértice deve ser trocado por outro vértice que não seja ele mesmo, calcular a distância entre ambos */
            {
                if (l->nave->tipo == TYPE_T || l->nave->tipo == TYPE_B)
                {
                    distancia = DFS(G, l->nave, s1, s2);    /* Computa um DFS de s1 para s2 */
                    //printf("  (%4d,%4d) du(%4d) dv(%4d) total(%4d)\n", s1+1, s2+1, d1, d2, distancia);
                }
                else
                {
                    /* Calcula a distancia de 'u' e 'v' até a origem */
                    d1 = (G->dv[s1]->d);    /* Distância de 'u' até a origem */
                    d2 = (G->dv[s2]->d);    /* Distância de 'v' até a origem */
                    
                    /* Calcula o LCA da aresta (u,v) */
                    if (l->nave->tipo == TYPE_R)
                    {
                        lca = (d1 < d2 ? s1: s2);       /* Menor entre os dois */
                        /* Calcula a distância do menor caminho entre os vértices da aresta (u,v) */
                        dlca = (G->dv[lca]->d);
                        distancia = d1 + d2 - 2 * dlca;
                        //printf("  (%4d,%4d) lca(%4d) du(%4d) dv(%4d) dlca(%4d) total(%4d)\n", s1+1, s2+1, lca, d1, d2, dlca, distancia);
                    }
                    else if (l->nave->tipo == TYPE_F)
                    {
                        while(a != b && a != -1 && b != -1) /* Enquanto não encontrar um ancestral em comum e 'a' ou 'b' não chegar na raiz, busca o LCA */
                        {
                            if(G->dv[a]->d > G->dv[b]->d)   /* Se vértice 'a' tiver numa profundidade maior que vértice 'b', avança vértice 'a' para pai de 'a' */
                                a = G->dv[a]->pai;
                            else   /* Se vértice 'b' tiver numa profundidade maior que vértice 'a', avança vértice 'b' para pai de 'b' */
                                b = G->dv[b]->pai;
                        }
                        lca = a;    /* LCA é 'a' ou 'b', visto que a busca finaliza quando encontrar o ancestral em comum ou chegar na raiz */
                        /* Calcula a distância do menor caminho entre os vértices da aresta (u,v) */
                        dlca = (G->dv[lca]->d);
                        distancia = d1 + d2 - 2 * dlca;
                        //printf("  (%4d,%4d) lca(%4d) du(%4d) dv(%4d) dlca(%4d) total(%4d)\n", s1+1, s2+1, lca, d1, d2, dlca, distancia);
                    }
                }

                soma += distancia;  /* Incrementa o contador total do tempo de vantagem da nave */
                
                //printf("minTV = %d\tSoma = %d\tDistancia = %d\n", minTV, soma, distancia);
                if (minTV > 0 && soma > minTV)  /* Se a soma obtida corresponde a primeira nave analisada ou a soma da nave for maior que a menor conhecida */
                    break;  /* Finaliza, pois essa nave nunca será a de menor tempo de vantagem */
            }
        }
        if (minTV == -1 || soma < minTV)
            minTV = soma;
        if (minTV == 0)  /* Se a soma obtida for zero, já encontramos o menor tempo de vantagem entre todas as naves */
            break;          /* Finaliza a busca entre os vértices da nave atual */
    }

    minTV /= 2; /* Divide o tempo de vantagem por 2, visto que queremos um limite inferior */
    //printf("%5d\n", minTV);
    
    /* Salva o menor tempo de vantagem entre as naves */
    FILE *arq;  /* Arquivo */
    /* Abre o arquivo */
    arq = fopen(arqOut, "a"); /* Abre o arquivo no modo append (anexar) */
    if(arq == NULL) /* Erro ao abrir o arquivo */
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else /* Abertura do arquivo foi bem sucedida */
        fprintf(arq, "%d", minTV);
    fclose(arq);    /* Fecha o arquivo */
}

/* Esse procedimento executa o software */
void executa(char* arqIn, char* arqOut)
{
    FILE *arq;                                  /* Arquivo lido */
    int qtd_vertices, qtd_arestas;              /* Dimensões do grafo */
    type u, v;                                  /* Posição atual (vértice u, v) */
    int contador;

    /* Le o arquivo */
    arq = fopen(arqIn, "r"); /* Abre o arquivo no modo read (leitura) */

    if(arq == NULL) /* Erro ao abrir o arquivo */
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else /* Abertura do arquivo foi bem sucedida */
    {
        while(1)
        {
            contador = 0; /* Inicializa o contador */
            fscanf(arq,"%d %d\n", &qtd_vertices, &qtd_arestas);      /* Le a primeira linha (contem as dimensoes do grafo) */
            //printf("%d, %d\n", qtd_vertices, qtd_arestas);           /* Imprime a primeira linha lida */
            TGrafo G = InicializaGrafo(qtd_vertices, qtd_arestas);   /* Inicializa a matriz, criando as células cabeça */
            while (contador < qtd_arestas)
            {
                /* Percorre o resto do arquivo, lendo linha a linha até chegar ao EOF, ou seja, ao marcador de fim do arquivo */
                if((fscanf(arq,"%d %d\n", &u, &v)) == EOF)
                    return;

                u--;    /* Armazena os vértices usando a posição 0 */
                v--;    /* Armazena os vértices usando a posição 0 */
                InsereAresta(G, u, v);      /* Insere na matriz a aresta u -> v */
                InsereAresta(G, v, u);      /* Insere na matriz a aresta v -> u */
                G->dv[u]->grau = G->dv[u]->grau+1;           /* Atualiza o grau do vértice u */
                G->dv[v]->grau = G->dv[v]->grau+1;           /* Atualiza o grau do vértice v */

                //printf("(%6.0d, %6.0d) - Grau(u): %2.0d - Grau(v): %2.0d\n",
                //       G->dv[u]->v, G->dv[v]->v, G->dv[u]->grau, G->dv[v]->grau);

                contador++; /* Incrementa o contador */
            }

            /* Identifica todas trocas que devem ser realizadas */
            contador = 0; /* Inicializa o contador */
            while (contador < qtd_vertices)
            {
                /* Percorre o resto do arquivo, lendo linha a linha até chegar ao EOF, ou seja, ao marcador de fim do arquivo */
                if((fscanf(arq,"%d %d\n", &u, &v)) == EOF)
                    return;

                G->dv[--u]->troca = v;    /* Obs: represento de 0 a n-1, e não de 1 a n */
                //printf("(%d, %d)\n", u+1, v+1);    /* Imprime os valores lidos na linha */

                contador++; /* Incrementa o contador */
            }

            //printf("\n\nGrafo\n");
            //for (type v = 0; v < G->V; v++)  /* Percorre cada vértice do grafo e exibe um vértice 'u' */
            //{
            //    printf("%d ", v);
            //    for (ElementoAdjacente a = G->adj[v]; a != NULL; a = a->prox)   /* Exibe cada vértice 'u' adjacente a 'v' */
            //        printf("%d, ", a->w);
            //    printf("\n");
            //}

            DFSComponenteConexa(G, arqOut);     /* Separa o grafo em naves e define os seus respectivos tipos */
            
            //for (type v = 0; v < G->V; v++)  /* Percorre cada vértice e exibe seus dados */ 
            //    printf("V = %2d - D = %2d - NAVE = %2d\n", G->dv[v]->v, G->dv[v]->d, G->dv[v]->nave);

            TempoDeVantagem(G, arqOut);         /* Calcula o menor tempo de vantagem da nave */
        }
    }
}
