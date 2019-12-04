#include <common.h>
#include <graph.h>
#include <dijkstra.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    errno = 0;

    // allow passing router text file as arg, default to router.txt
    const char *filename = argc > 1 ? argv[1] : "router.txt";
    printf("Loading network graph from %s ... ", filename);

    // open router text file
    FILE *infile = fopen(filename, "r");
    abort_if_error();

    // create graph and load from file
    graph_t *graph = graph_create();
    graph_load(graph, infile);
    abort_if_error();

    // close file
    fclose(infile);
    abort_if_error();

    // done reading graph from file
    printf("OK\n");

    // print graph as adjacency matrix, because we can
    printf("\nGraph as adjacency matrix:\n\n");
    graph_print_adjacency(graph);
    abort_if_error();

    // truncate dijkstra's output file
    FILE *outfile = fopen("LS.txt", "w+");
    abort_if_error();

    // do dijkstra's to find the shortest path to each node, for each node
    printf("\nShortest paths:\n\n");
    for (size_t i = 0; i < graph->vertices_len; i++)
    {
        for (size_t j = 0; j < graph->vertices_len; j++)
        {
            if (i == j) continue;

            dijkstra(graph, i, j);
            graph_print_shortest_path(outfile, graph, i, j);
            abort_if_error();
        }

        if (i < graph->vertices_len - 1)
        {
            print_and_file(outfile, "%s", "--------\n");
        }
    }

    print_and_file(outfile, "%s", "\n");
    fclose(outfile);

    graph_destroy(graph);
    return errno;
}
