#include <stdio.h>
#include "head.h"

int findNextHop(int source, int destination, int parent[])
{
    int current;
    int previous;

    if (parent[destination] == source)
        return -1;

    current = destination;
    previous = -1;

    while (current != source && current != -1)
    {
        previous = current;
        current = parent[current];
    }

    if (current == source)
        return previous;

    return -1;
}

int main()
{
    int edges;
    int source;

    int i, j;

    char u, v;
    char sourceName;

    int w;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter vertex names: ");

    for (i = 0; i < n; i++)
        scanf(" %c", &vertex[i]);

    initialize();

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("\nEnter edges as: From To Weight\n");

    for (i = 0; i < edges; i++)
    {
        scanf(" %c %c %d", &u, &v, &w);

        if (w < 0)
        {
            printf("\nError: Dijkstra cannot be applied ");
            printf("for negative edge cost.\n");

            return 0;
        }

        addEdge(u, v, w);
    }

    printf("\nEnter source vertex: ");
    scanf(" %c", &sourceName);

    source = -1;

    for (i = 0; i < n; i++)
    {
        if (vertex[i] == sourceName)
        {
            source = i;
            break;
        }
    }

    if (source == -1)
    {
        printf("Invalid source vertex\n");
        return 0;
    }

    dijkstra(source);

    printf("\n\n========== DIJKSTRA'S ALGORITHM ==========\n");

    for (i = 0; i < stepCount - 1; i++)
    {
        printf("\nStep %d:\n", i + 1);

        printf("S = { ");

        for (j = 0; j < n; j++)
        {
            if (step[i].selected[j])
                printf("%c ", vertex[j]);
        }

        printf("}\n");

        printf("P = { ");

        for (j = 0; j < n; j++)
        {
            if (!step[i].selected[j])
                printf("%c ", vertex[j]);
        }

        printf("}\n\n");

        for (j = 0; j < n; j++)
        {
            if (!step[i].selected[j] &&
                j != source)
            {
                printf("d(%c,%c) = ",
                       vertex[source],
                       vertex[j]);

                if (step[i].distance[j] == INF)
                    printf("INF");
                else
                    printf("%d", step[i].distance[j]);

                printf("\n");
            }
        }

        printf("\n");

        if (step[i].choose != -1)
        {
            printf("Therefore choose vertex %c\n",
                   vertex[step[i].choose]);
        }
    }

    printf("\n\n========== FINAL SHORTEST PATHS ==========\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        printf("\n");

        if (step[stepCount - 1].distance[i] == INF)
        {
            printf("Destination : %c\n", vertex[i]);
            printf("Cost        : INF\n");
            printf("Next Hop    : -\n");
            printf("Path        : No path\n");

            continue;
        }

        int path[MAX];
        int pathSize = 0;
        int current = i;

        while (current != -1)
        {
            path[pathSize++] = current;
            current =
                step[stepCount - 1].parent[current];
        }

        int nextHop;

        nextHop = findNextHop(
            source,
            i,
            step[stepCount - 1].parent
        );

        printf("Destination : %c\n", vertex[i]);

        printf("Cost        : %d\n",
               step[stepCount - 1].distance[i]);

        if (nextHop == -1)
            printf("Next Hop    : -\n");
        else
            printf("Next Hop    : %c\n",
                   vertex[nextHop]);

        printf("Path        : ");

        for (j = pathSize - 1; j >= 0; j--)
        {
            printf("%c", vertex[path[j]));

            if (j != 0)
                printf(" -> ");
        }

        printf("\n");
    }

    printf("\n\n=============== ROUTING TABLE ===============\n\n");

    printf("---------------------------------------------\n");
    printf("| Destination | Cost | Next Hop |\n");
    printf("---------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        if (i == source)
            continue;

        if (step[stepCount - 1].distance[i] == INF)
        {
            printf("|      %c       | INF  |     -     |\n",
                   vertex[i]);

            continue;
        }

        int nextHop;

        nextHop = findNextHop(
            source,
            i,
            step[stepCount - 1].parent
        );

        if (nextHop == -1)
        {
            printf("|      %c       | %4d |     -     |\n",
                   vertex[i],
                   step[stepCount - 1].distance[i]);
        }
        else
        {
            printf("|      %c       | %4d |     %c     |\n",
                   vertex[i],
                   step[stepCount - 1].distance[i],
                   vertex[nextHop]);
        }
    }

    printf("---------------------------------------------\n");

    return 0;
}
