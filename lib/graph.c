#include "graph.h"

#include <stdlib.h>

graph_t *graph_create()
{
    return (graph_t *) calloc(1, sizeof(graph_t));
}

void graph_destroy(graph_t *graph)
{
    // destroy all vertices in graph
    for (size_t i = 0; i < graph->vertices_len; i++)
        vertex_destroy(graph->vertices[i]);

    free(graph);
}

// extend the graph's vertices array to accommodate the required index
void graph_extend_vertices(graph_t *graph, size_t required_index)
{
    // resize vertices pointer array
    size_t size = graph->vertices_size * 2 > required_index ? graph->vertices_size * 2 : required_index + 4;
    graph->vertices = realloc(graph->vertices, size * sizeof(vertex_t *));

    // set new vertex pointers at the end to NULL
    for (size_t j = graph->vertices_size; j < size; j++)
        graph->vertices[j] = NULL;

    // set new vertices_size
    graph->vertices_size = size;
}

// add a vertex to the graph if it does not already exist
void graph_add_vertex(graph_t *graph, size_t index)
{
    // make sure we have enough space; resize if we need more space
    if (graph->vertices_size < index + 1)
        graph_extend_vertices(graph, index);

    // create a new vertex if one does not already exist
    if (!graph->vertices[index])
    {
        graph->vertices[index] = vertex_create();
        graph->vertices_len++;
    }
}

// add an edge to the graph
void graph_add_edge(graph_t *graph, char left_i, char right_i, size_t weight)
{
    // take character names and reduce to offset from name start (e.g. names start at 'u' -> nodes are u, v, w, x, ...)
    left_i -= NODE_NAMES_START;
    right_i -= NODE_NAMES_START;

    // add these vertices to the graph if they do not already exist
    graph_add_vertex(graph, left_i);
    graph_add_vertex(graph, right_i);

    // create two new edges: one for left->right, and one for right->left
    edge_t *e_lr = calloc(1, sizeof(edge_t));
    edge_t *e_rl = calloc(1, sizeof(edge_t));

    // left->right edge has target vertex right_i, while right->left is flipped
    e_lr->vertex = right_i;
    e_rl->vertex = left_i;

    // add these edges to the respective vertices
    vertex_add_edge(graph->vertices[left_i], e_lr);
    vertex_add_edge(graph->vertices[right_i], e_rl);
}

// load a graph from file
void graph_load(graph_t *graph, FILE *file)
{

}

// create a vertex
vertex_t *vertex_create()
{
    return (vertex_t *) calloc(1, sizeof(vertex_t));
}

// destroy a vertex
void vertex_destroy(vertex_t *v)
{
    if (!v)
        return;

    for (size_t i = 0; i < v->edges_len; i++)
        free(v->edges[i]);

    free(v);
}

// add an edge to a vertex
void vertex_add_edge(vertex_t *v, edge_t *e)
{
    // add space for this new edge if we need it
    if (v->edges_len >= v->edges_size)
    {
        // if edges_size is at its initial value of zero, set to 4. else double.
        v->edges_size = v->edges_size ? v->edges_size * 2 : 4;

        // reallocate memory to accommodate new size
        v->edges = realloc(v->edges, v->edges_size * sizeof(edge_t *));
    }

    // add this new edge to the list of edges for this vertex
    v->edges[v->edges_len++] = e;
}

// create a heap
heap_t *heap_create(size_t size)
{
    heap_t *result = calloc(1, sizeof(heap_t));

    result->data = calloc(size + 1, sizeof(size_t));
    result->prio = calloc(size + 1, sizeof(size_t));

    result->index = calloc(size, sizeof(size_t));

    result->len = 0;
    result->size = 0;

    return result;
}

// destroy a heap without touching any of the vertices themselves
void heap_destroy(heap_t *heap)
{
    free(heap->data);
    free(heap->prio);
    free(heap->index);

    free(heap);
}

// get min value from heap given three indices
size_t heap_min(heap_t *heap, size_t i, size_t j, size_t k)
{
    size_t min = i;

    if (j <= heap->len && heap->prio[j] < heap->prio[min])
        min = j;

    if (k <= heap->len && heap->prio[k] < heap->prio[min])
        min = k;

    return min;
}

// push data onto a heap
void heap_push(heap_t *heap, size_t vertex, size_t prio)
{
    size_t i = heap->index[vertex] == 0 ? ++heap->len : heap->index[vertex];
    size_t j = i / 2;

    while (i > 1)
    {
        if (heap->prio[j] < prio)
            break;

        heap->data[i] = heap->data[j];
        heap->prio[i] = heap->prio[j];
        heap->index[heap->data[i]] = i;

        i = j;
        j /= 2;
    }

    heap->data[i] = vertex;
    heap->prio[i] = prio;
    heap->index[vertex] = i;
}

// pop data from a heap
size_t heap_pop(heap_t *heap)
{
    size_t result = heap->data[1];
    size_t i = 1;

    // shuffle to handle pop
    while (1)
    {
        size_t j = heap_min(heap, heap->len, 2 * i, 2 * i + 1);

        if (j == heap->len)
            break;

        heap->data[i] = heap->data[j];
        heap->prio[i] = heap->prio[j];
        heap->index[heap->data[i]] = i;

        i = j;
    }

    heap->data[i] = heap->data[heap->len];
    heap->prio[i] = heap->prio[heap->len];
    heap->index[heap->data[i]] = i;
    heap->len--;

    return result;
}
