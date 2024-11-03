#ifndef __GRAPH_H__
#define __GRAPH_H__

#include <stdbool.h>
#include <stddef.h>
#include "matrix.h"

typedef struct graph_t {
    matrix_t *adj;
    size_t m; //Que hace m?
    size_t size;
    size_t capa;
    size_t next;
    bool *alive;
} graph_t;

/************************/
/* Constructor de grafo */
/************************/

graph_t *new_graph(size_t n);

/***********************/
/* Destructor de grafo */
/***********************/

void free_graph(graph_t *g);

/**************/
/* Selectores */
/**************/

/* Precondiciones:
   a) g != NULL */
size_t graph_nvertices(graph_t *g);

/* Precondiciones:
   a) g != NULL
   b) v, u < graph_nvertices(g) */
bool graph_adjacent(graph_t *g, size_t v, size_t u);

/* Precondiciones:
   a) g != NULL
   b) v, u < graph_nvertices(g)

   Poscondiciones:
   a) graph_adjacent(g, v, u) == true */
void graph_connect(graph_t *g, size_t v, size_t u);

/* Precondiciones:
   a) g != NULL
   b) v, u < graph_nvertices(g)

   Poscondiciones:
   a) graph_adjacent(g, v, u) == false */
void graph_disconnect(graph_t *g, size_t v, size_t u);

/* Precondiciones:
   a) g != NULL
   b) graph_nvertices(g) == n

   Poscondiciones:
   a) 0 < graph_nvertices(g)
   b) graph_nvertices(g) == n + 1 */
size_t graph_add(graph_t *g);


void graph_print(graph_t *g);

#endif /* __GRAPH_H__ */

