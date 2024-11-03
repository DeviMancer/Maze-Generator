#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

//************************************************************* Constructor 
graph_t *new_graph(size_t n)
{

    // Reserva memoria para la estructura graph_t
    graph_t *G = (graph_t *)malloc(sizeof(graph_t));
    if (G == NULL) return NULL;

    G->size=n;
    for (G->capa = 6; G->capa <= n; G->capa *= 2);

    // Crea la matriz de adyacencia
    G->adj = new_matrix(G->capa, G->capa, false);
    if (G->adj == NULL) {
        free(G);
       return NULL;
    }

    // Reserva memoria para alive.
    G->alive = (bool *)malloc(G->capa * sizeof(bool));
    if (G->alive == NULL) {
        free_matrix(G->adj);
        free(G);
        return NULL;
    }

    // Activamos los primeros n (size) elementos de alive.
    for (size_t i = 0; i < G->capa; i++) {
            G->alive[i] = (i < G->size);
    }

    G->next=n;
        
    return G;
}

//************************************************************ Destructor
void free_graph(graph_t *g)
{
    if (g == NULL) return;

    free_matrix(g->adj);
    free(g->alive);
}

//************************************************************* Num vertices
size_t graph_nvertices(graph_t *g)
{
    return matrix_rows(g->adj);
}

//************************************************************* graph_adjacent
bool graph_adjacent(graph_t *g, size_t v, size_t u)
{
    bool *M = (bool *)g->adj;
    size_t cols = matrix_cols(g->adj);

    return M[(v-1) * cols + (u-1)] == 1;
}

//************************************************************* graph_connect
void graph_connect(graph_t *g, size_t v, size_t u)
{   
    matrix_set(g->adj, v-1, u-1, true);
    matrix_set(g->adj, u-1, v-1, true);
}

//************************************************************* graph_disconnect
void graph_disconnect(graph_t *g, size_t v, size_t u)
{
    matrix_set(g->adj, v-1, u-1, false);
    matrix_set(g->adj, u-1, v-1, false);
}

//************************************************************* graph_add
size_t graph_add(graph_t *g)
{
    //TODO: Si g->next == g->capa, entonces redimensionar...

    // Activamos un nodo en alive
    size_t newNode = g->next;
    g->alive[newNode] = 1;

    // Actualizamos graph_t
    ++(g->next); // Esta linea no me convence. Pero asegura funcionar si no se remueve un nodo arbitrario.
    ++(g->size);

    return newNode;
}

//************************************************************* Print graph
//void graph_print(graph_t *g){}





