
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "ficheiro.h"
#include "oper.h"
NO* createNode(int);

typedef struct node
{
    VERTICE vertex;
    struct node* next;
}NO;

typedef struct Graph{
    int numVertices;
    NO** adjLists;
}GRAFO;

/*coordenadas e valor de cada vertice*/
typedef struct _vertice{
    int x_vert;
    int y_vert;
    int peso;
}VERTICE;



NO* createNode(int v)
{
    NO* newNode = malloc(sizeof(NO));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}


GRAFO* createGraph(int vertices)
{
    GRAFO* graph = malloc(sizeof(GRAFO));
    graph->numVertices = vertices;
 
    graph->adjLists = malloc(vertices * sizeof(NO*));
 
    int i;
    for (i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
 
    return graph;
}
 
void addEdge(GRAFO* graph, int src, int dest)
{
    /* Add edge from src to dest*/
    NO* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    /* Add edge from dest to src*/
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(GRAFO* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        NO* temp = graph->adjLists[v];
        printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}


void inicializaD(GRAFO *g, int *d, int *p, int s){
    int v;
    for (v = 0; v< g->vertices; v++ ){
        d[v] = INT_MAX / 2; /* INT_MAX corresponde ao maior número possível, simbolicamente representa +infinito*/
        p[v] = -1;
    }
    d[s] = 0;
}

/*relaxamaneto entre u e v*/

void relaxa(GRAFO *g, int *d, int *p, int u, int v){
    /*u e v são predecessores*/
    ADJACENCIA *ad = g->adj[u].head; //cabeça da lista de adjacências
    while(ad && ad->vertice != v){ //Enquanto existem vizinhos e adjacência for diferente de v
        ad = ad->prox;
        //Acabou lista??
        if(ad){
            if(d[v] > d[u] + ad->peso){ //estimada é maior que peso da casa mais distancia?
                //substituir por alternativa melhor
                d[v] = d[u] + ad->peso;
                p[v] = u;

            }
        }

    }
}

/*Esta funcao varre todos os vertices e retorna true se encontrar algum aberto, retorna false se todos os vertices estao fechados*/
bool existeAberto(GRAFO *g, int *aberto){
    int i;
    for(i= 0; i< g->vertices; i++){
        if (aberto[i])
            return true;
        return false;
    }
}

/*Vai à procura do meno nó aberto*/

int menorDist(GRAFO *g, int *aberto, int *d){
    int i;

    /*Vai a procura do primeiro indice com sinal que esta aberto*/

    for (i = 0; i < g->vertices; i++){
        if(aberto[i])
            break;
    }

    /*"varreu" e nao encontro entao volta ao ciclo*/

    if (i == g->vertices)
        return (-1);
    int menor = i;

    /*a partir do que foi calculado*/

    for (i = menor + 1; i < g->vertices; i++){
        if(aberto[i] && (d[menor] > d[i]))
            menor = i;
        return menor; /*indice do arranjo com menor distancia*/
    }
}

/*Função chamada para calcular o caminho de custo mínimo entre dois pontos*/
    
    int *dijkstra(GRAFO *g, int s){
    int *d = (int*) malloc (g->vertices * sizeof(int));

    /*arranjo dos predecessores */

    int p[g->vertices];

    /*inicializar distancias e predecessores*/

    bool aberto[g->vertices];
    int i;
    for(i = 0; i<g->vertices; i++){

        /*marcar todos os pontos como abertos*/

        aberto[i] = true;
    }

    while (existeAberto(g, aberto)){
        int u = menorDist(g, aberto);

        /*vai escolher de todos os abertos o que tem menor distancia*/

        aberto[u] = false;

        /*vai fechar o nó do ponto com menor custo*/

        ADJACENCIA *ad = g->adj[u].cab;
        while(ad){                               /*procurar nos vizinhos de u que acabou de ser fechado */
            relaxa(g, d, p, u, ad->vertice);
            ad = ad->prox;

        }
    }
    return(d);

    /*retornamos arranjo com as distâncias */
}


/*Estruturas necessarias para o programa*/

/*
Graphinit cria grafo com o número final de vértices, sem arestas.
GraphinsertE insere uma aresta, caso não exista .
GraphremoveE retira uma aresta, caso exista.
Graphedges conta o número de arestas.
Graphcopy cria uma segunda cópia do grafo .
Graphdestroy faz o inverso de Graphinit.
*/


/*
GRAFO createGraph(int vertices);
void addEdge(GRAFO* graph, int src, int dest);
void printGraph(GRAFO* graph);

int main()
{
    GRAFO* graph = createGraph(6);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 4);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 4, 6);
    addEdge(graph, 5, 1);
    addEdge(graph, 5, 6);
 
    printGraph(graph);
 
    return 0;
}*/
