#ifndef HEAD_H
#define HEAD_H

#define INF 99999
#define MAX 100

struct Edge
{
    int src;
    int dest;
    int weight;
};

void bellmanFord(int V, int E, struct Edge edge[], int source);

#endif
