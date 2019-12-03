#include "dijkstra.h"

#include <limits.h>

void dijkstra(graph_t *graph, char src, char dest)
{
    size_t i, j;

    src -= NODE_NAMES_START;
    dest -= NODE_NAMES_START;

    for (i = 0; i < graph->vertices_len; i++)
    {
        vertex_t *v = graph->vertices[i];
        v->dist = UINT_MAX;
        v->prev = 0;
        v->visited = false;
    }

    // get vertex and set own distance to zero
    vertex_t *v = graph->vertices[src];
    v->dist = 0;

    // create heap and push this vertex onto it
    heap_t *heap = heap_create(graph->vertices_len);
    heap_push(heap, src, v->dist);

    while (heap->len)
    {
        // pop the top vertex index off the heap
        i = heap_pop(heap);

        // if this is our destination, we are done
        if (i == dest)
            break;

        // get the actual vertex from the graph and mark as visited
        v = graph->vertices[i];
        v->visited = true;

        for (j = 0; j < v->edges_len; j++)
        {
            // get this edge and the vertex it points to
            edge_t *edge = v->edges[j];
            vertex_t *u = graph->vertices[edge->vertex];

            // if we haven't yet visited this edge, and it's cheaper than the previous known path, update and push
            if (!u->visited && v->dist + edge->weight <= u->dist)
            {
                u->prev = i;
                u->dist = v->dist + edge->weight;
                heap_push(heap, edge->vertex, u->dist);
            }
        }
    }
}
