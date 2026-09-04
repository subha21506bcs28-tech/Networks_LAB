#ifndef HEAD_H
#define HEAD_H

#define MAX 20
#define INF 99999

typedef struct
{
    int selected[MAX];
    int distance[MAX];
    int parent[MAX];
    int choose;
} Step;

extern int n;
extern char vertex[MAX];
extern int cost[MAX][MAX];

extern Step step[MAX];
extern int stepCount;

void initialize();
void addEdge(char u, char v, int w);
void dijkstra(int source);

#endif
