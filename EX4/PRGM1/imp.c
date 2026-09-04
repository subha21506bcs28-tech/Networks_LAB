#include "head.h"

int n;
char vertex[MAX];
int cost[MAX][MAX];

Step step[MAX];
int stepCount;

void initialize()
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == j)
                cost[i][j] = 0;
            else
                cost[i][j] = INF;
        }
    }
}

void addEdge(char u, char v, int w)
{
    int i, j;

    for (i = 0; i < n; i++)
    {
        if (vertex[i] == u)
            break;
    }

    for (j = 0; j < n; j++)
    {
        if (vertex[j] == v)
            break;
    }

    if (i < n && j < n)
    {
        cost[i][j] = w;
        cost[j][i] = w;
    }
}

void dijkstra(int source)
{
    int distance[MAX];
    int parent[MAX];
    int selected[MAX];

    int i, j;
    int current;
    int min;

    stepCount = 0;

    for (i = 0; i < n; i++)
    {
        distance[i] = INF;
        parent[i] = -1;
        selected[i] = 0;
    }

    distance[source] = 0;

    selected[source] = 1;

    for (i = 0; i < n; i++)
    {
        if (cost[source][i] != INF && i != source)
        {
            distance[i] = cost[source][i];
            parent[i] = source;
        }
    }

    while (1)
    {
        current = -1;
        min = INF;

        for (i = 0; i < n; i++)
        {
            if (!selected[i] && distance[i] < min)
            {
                min = distance[i];
                current = i;
            }
        }

        if (current != -1)
        {
            for (i = 0; i < n; i++)
            {
                if (!selected[i] &&
                    distance[i] == min &&
                    i < current)
                {
                    current = i;
                }
            }
        }

        if (current == -1)
            break;

        for (i = 0; i < n; i++)
        {
            step[stepCount].selected[i] = selected[i];
            step[stepCount].distance[i] = distance[i];
            step[stepCount].parent[i] = parent[i];
        }

        step[stepCount].choose = current;

        stepCount++;

        selected[current] = 1;

        for (j = 0; j < n; j++)
        {
            if (!selected[j] && cost[current][j] != INF)
            {
                int newDistance =
                    distance[current] + cost[current][j];

                if (newDistance < distance[j])
                {
                    distance[j] = newDistance;
                    parent[j] = current;
                }
                else if (newDistance == distance[j] &&
                         (parent[j] == -1 ||
                          current < parent[j]))
                {
                    parent[j] = current;
                }
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        step[stepCount].selected[i] = selected[i];
        step[stepCount].distance[i] = distance[i];
        step[stepCount].parent[i] = parent[i];
    }

    step[stepCount].choose = -1;

    stepCount++;
}
