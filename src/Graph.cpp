#include "Graph.h"

#include <set>
#include <tuple>
#include <vector>
#include <utility>

const double EPS = 0.001;

struct DSU {
	std::vector<int> par;

	void init(int n) {
		par.clear();
		par.resize(n+1, -1);
	}

	int root(int x) {
		if (par[x] < 0) return x;
		while (par[par[x]] >= 0) par[x] = par[par[x]];
		return par[x];
	}

	void join(int x, int y) {
		x = root(x);
		y = root(y);
		if (x > y) {
			x ^= y;
			y ^= x;
			x ^= y;
		}

		par[x] += par[y];
		par[y] = x;
	}
};

auto cmp = [](std::pair<double, int> a, std::pair<double, int> b) {
	return std::tie(a.first, a.second) > std::tie(b.first, b.second);
};

int n;
DSU dsu;
std::set<std::pair<double, int>, decltype(cmp)> pq(cmp); // priority queue of edges

std::vector<std::pair<int, int>> result;

// Check if the sum(profit)/sum(dist) ratio can be >= x
bool profitable(std::vector<Edge> &edges, double x) {
	for (int i = 0; i < edges.size(); ++i) {
		double weight = ((double)edges[i].profit) - ((double)edges[i].dist) * x;
		pq.insert({weight, i});
	}

	dsu.init(n);

	double total_weight = 0;

	while (pq.size()) {
		std::pair<double, int> e = *pq.begin();
		pq.erase(pq.begin());

		int u = edges[e.second].u;
		int v = edges[e.second].v;

		if (dsu.root(u) == dsu.root(v)) continue;

		dsu.join(u, v);
		total_weight += e.first;
	}

	return total_weight >= 0.0;
}

void construct_tree(std::vector<Edge> &edges, double x) {
	for (int i = 0; i < edges.size(); ++i) {
		double weight = ((double)edges[i].profit) - ((double)edges[i].dist) * x;
		pq.insert({weight, i});
	}

	dsu.init(n);

	while (pq.size()) {
		std::pair<double, int> e = *pq.begin();
		pq.erase(pq.begin());

		int u = edges[e.second].u;
		int v = edges[e.second].v;

		if (dsu.root(u) == dsu.root(v)) continue;

		dsu.join(u, v);
		result.push_back({u, v});
	}
}

std::vector<std::pair<int, int>> optimal_tree(std::vector<Edge> &e, int N) {
	n = N;
	double l = 0;
	double r = 0;

	for (Edge& x: e) r = std::max(r, ((double)x.profit)/((double)x.dist));

	while (r-l > EPS) {
		double mid = (r + l) / 2.0;
		if (profitable(e, mid)) l = mid;
		else r = mid;
	}

	construct_tree(e, l);
	return result;
}
