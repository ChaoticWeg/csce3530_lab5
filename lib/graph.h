#ifndef INC_3530_LAB5_GRAPH_H
#define INC_3530_LAB5_GRAPH_H

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define NODE_NAMES_START 'u'
#define FILE_MAX_LINE_LEN 100


// ================
//  STRUCT: EDGE_T
// ================


// edge struct: holds vertex index and weight
typedef struct
{
    size_t vertex; // the destination vertex to which this edge points
    size_t weight; // the cost of traveling along this edge
}
edge_t;


// ==================
//  STRUCT: VERTEX_T
// ==================


// vertex struct: holds edges and values for dijkstra
typedef struct
{
    // edges
    edge_t **edges;
    size_t edges_len;
    size_t edges_size;

    // dijkstra values
    size_t dist;
    size_t prev;
    bool visited;
}
vertex_t;

// create/destroy a vertex
vertex_t *vertex_create();
void vertex_destroy(vertex_t *);

// get an edge to a destination vertex
edge_t *vertex_get_edge(const vertex_t *, size_t);

// create a vertex
void vertex_add_edge(vertex_t *, edge_t *);


// =================
//  STRUCT: GRAPH_T
// =================


// graph struct: holds vertices
typedef struct
{
    vertex_t **vertices;
    size_t vertices_len;
    size_t vertices_size;
} graph_t;

// create/destroy graph
graph_t *graph_create();
void graph_destroy(graph_t *);

// add a vertex to the graph
void graph_add_vertex(graph_t *, size_t);

// get a vertex from the graph
vertex_t *graph_get_vertex(const graph_t *, size_t);

// add an edge to the graph
void graph_add_edge(graph_t *, char, char, size_t);

// load a graph from file
void graph_load(graph_t *, FILE *);

// print a graph as an adjacency matrix
void graph_print_adjacency(const graph_t *);

// print the shortest path between two vertices
void graph_print_shortest_path(FILE *, const graph_t *, size_t, size_t);


// ================
//  STRUCT: HEAP_T
// ================


// heap struct: holds execution data for dijkstra
typedef struct
{
    size_t *data;
    size_t *prio;

    size_t *index;
    size_t len;
    size_t size;
}
heap_t;

heap_t *heap_create(size_t);
void heap_destroy(heap_t *);

size_t heap_min(heap_t *, size_t, size_t, size_t);

void heap_push(heap_t *, size_t, size_t);
size_t heap_pop(heap_t *);


#endif //INC_3530_LAB5_GRAPH_H
