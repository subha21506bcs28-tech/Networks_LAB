#include <stdio.h>
#include "head.h"

int main()
{
    int V, E, source;
    struct Edge edge[MAX];

    int i;

    printf("Enter number of nodes: ");
    scanf("%d", &V);

    printf("Enter number of edges: ");
    scanf("%d", &E);

    printf("Enter edges (Source Destination Cost):\n");

    for(i = 0; i < E; i++)
    {
        scanf("%d %d %d",
              &edge[i].src,
              &edge[i].dest,
              &edge[i].weight);
    }

    printf("Enter source node: ");
    scanf("%d", &source);

    bellmanFord(V, E, edge, source);

    return 0;
}
