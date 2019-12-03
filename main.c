#include <common.h>
#include <graph.h>
#include <dijkstra.h>

#include <errno.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 2)
        return abort_args(argv[0]);

    const char *filename = argv[1];
    errno = 0;

    // TODO create and initialize graph

    printf("Loading network graph from %s ... ", filename);

    // open file
    FILE *infile = fopen(filename, "r");
    if (infile == NULL || errno != 0)
        return abort_error(errno);

    // TODO load graph

    // close file
    fclose(infile);
    printf("OK\n");

    // TODO dijkstra for each node as source

    return 0;
}
