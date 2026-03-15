#include "City.h"
#include "Data.h"
#include "Graph.h"

#include <vector>
#include <iostream>

int main() {
	load();

	std::vector<Edge> edges = City::gen_graph();
	std::vector<std::pair<int, int>> tree = optimal_tree(edges, City::cities.size());

	for (auto [u, v]: tree) {
		City::cities[u].print();
		std::cout << " -> ";
		City::cities[v].print();
		std::cout << "\n";
	}
}
