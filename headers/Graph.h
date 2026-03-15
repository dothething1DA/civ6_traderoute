#ifndef Graph_H
#define Graph_H

#include <vector>
#include <utility>

struct Edge {
    int u, v;
    int dist;
    int profit;

    Edge() {}
    Edge(int u, int v, int d, int p): u(u), v(v), dist(d), profit(p) {}
};

std::vector<std::pair<int, int>> optimal_tree(std::vector<Edge> &e, int n);

#endif
