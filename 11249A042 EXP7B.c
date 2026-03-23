#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int comparator(const void *a, const void *b)
{
    int *p1 = (int *)a;
    int *p2 = (int *)b;
    return p1[2] - p2[2];
}

void makeSet(int parent[], int rank[], int n)
{
    int i;
    for (i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;
    return parent[component] = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

int kruskalAlgo(int vertices, int edges, int edge[][3])
{
    qsort(edge, edges, sizeof(edge[0]), comparator);

    int parent[MAX];
    int rank[MAX];

    makeSet(parent, rank, vertices);

    int minCost = 0;
    int i;

    for (i = 0; i < edges; i++) {
        int u = edge[i][0];
        int v = edge[i][1];
        int wt = edge[i][2];

        int p1 = findParent(parent, u);
        int p2 = findParent(parent, v);

        if (p1 != p2) {
            unionSet(p1, p2, parent, rank);
            minCost += wt;
        }
    }

    return minCost;
}

int main()
{
    int edge[5][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    printf("%d", kruskalAlgo(4, 5, edge));

    return 0;
}
