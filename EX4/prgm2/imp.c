#include <stdio.h>
#include "head.h"

void bellmanFord(int V, int E, struct Edge edge[], int source)
{
    int dist[MAX];
    int parent[MAX];

    int newDist[MAX];
    int newParent[MAX];

    int i, j;

    /* ---------------- INITIALIZE ---------------- */

    for(i = 1; i <= V; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    /* ---------------- INITIAL TABLE ---------------- */

    printf("\nINITIAL TABLE\n");
    printf("Node\tCost\n");

    for(i = 1; i <= V; i++)
    {
        if(dist[i] == INF)
            printf("%d\tINF\n", i);
        else
            printf("%d\t%d\n", i, dist[i]);
    }

    /* ---------------- V-1 PASSES ---------------- */

    for(i = 1; i <= V - 1; i++)
    {
        /* Copy old values */
        for(j = 1; j <= V; j++)
        {
            newDist[j] = dist[j];
            newParent[j] = parent[j];
        }

        /*
         * Relax every edge.
         * Since graph is UNDIRECTED:
         *
         * u -> v
         * v -> u
         */

        for(j = 0; j < E; j++)
        {
            int u = edge[j].src;
            int v = edge[j].dest;
            int w = edge[j].weight;

            /* u -> v */
            if(dist[u] != INF &&
               newDist[v] > dist[u] + w)
            {
                newDist[v] = dist[u] + w;
                newParent[v] = u;
            }

            /* v -> u */
            if(dist[v] != INF &&
               newDist[u] > dist[v] + w)
            {
                newDist[u] = dist[v] + w;
                newParent[u] = v;
            }
        }

        /* Update values after completing the pass */
        for(j = 1; j <= V; j++)
        {
            dist[j] = newDist[j];
            parent[j] = newParent[j];
        }

        /* ---------------- PRINT PASS ---------------- */

        printf("\nPASS %d\n", i);
        printf("Node\tCost\n");

        for(j = 1; j <= V; j++)
        {
            if(dist[j] == INF)
                printf("%d\tINF\n", j);
            else
                printf("%d\t%d\n", j, dist[j]);
        }
    }

    /* ---------------- NEGATIVE CYCLE CHECK ---------------- */

    for(j = 0; j < E; j++)
    {
        int u = edge[j].src;
        int v = edge[j].dest;
        int w = edge[j].weight;

        if(dist[u] != INF && dist[v] > dist[u] + w)
        {
            printf("\nNegative weight cycle exists in the graph.\n");
            return;
        }

        if(dist[v] != INF && dist[u] > dist[v] + w)
        {
            printf("\nNegative weight cycle exists in the graph.\n");
            return;
        }
    }

    /* ---------------- FINAL ROUTING TABLE ---------------- */

    printf("\nFINAL ROUTING TABLE\n");
    printf("Node\tCost\tNext Hop\n");

    for(i = 1; i <= V; i++)
    {
        /* Source */
        if(i == source)
        {
            printf("%d\t0\t-\n", i);
        }

        /* Destination unreachable */
        else if(dist[i] == INF)
        {
            printf("%d\tINF\t-\n", i);
        }

        else
        {
            int current = i;
            int nextHop = i;

            /*
             * Follow parent chain backwards
             * until we reach the source.
             *
             * Example:
             *
             * Source = 1
             * Path = 1 -> 3 -> 2
             *
             * parent[2] = 3
             * parent[3] = 1
             *
             * Therefore next hop for 2 = 3
             */

            while(parent[current] != -1 &&
                  parent[current] != source)
            {
                current = parent[current];
            }

            if(parent[current] == source)
            {
                nextHop = current;

                /*
                 * If destination itself is directly
                 * connected to source, show '-'
                 */
                if(nextHop == i)
                {
                    printf("%d\t%d\t-\n",
                           i, dist[i]);
                }
                else
                {
                    printf("%d\t%d\t%d\n",
                           i, dist[i], nextHop);
                }
            }
            else
            {
                printf("%d\t%d\t-\n",
                       i, dist[i]);
            }
        }
    }
}
