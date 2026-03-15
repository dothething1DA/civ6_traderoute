#include "City.h"
#include "Graph.h"

#include <tuple>
#include <vector>
#include <iostream>

const int MAP_SIZE = 106;

std::vector<City> City::cities;

int west_ward_dist(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y1 - y2 + (y1 >= y2 ? 0 : MAP_SIZE);

	if (dx) dy -= (dx >> 1) + ((x1&1)^1);
	return dx + std::max(dy, 0);
}

int east_ward_dist(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1 + (y2 >= y1 ? 0 : MAP_SIZE);

	if (dx) dy -= (dx >> 1) + (x1&1);
	return dx + std::max(dy, 0);
}

int City::dist(City& c) {
	int x1 = this -> cx;
	int y1 = this -> cy;

	int x2 = c.cx;
	int y2 = c.cy;

	if (std::tie(x1, y1) > std::tie(x2, y2)) {
		// swap coordinates 1 and 2
		x1 ^= x2; x2 ^= x1; x1 ^= x2;
		y1 ^= y2; y2 ^= y1; y1 ^= y2;
	}

	int de = east_ward_dist(x1, y1, x2, y2);
	int dw = west_ward_dist(x1, y1, x2, y2);
	return std::min(de, dw);
}

int City::profit_score(City& c) {
	int res = c.food + c.production + c.gold;
	char fr = this -> focusedRs;

	if (fr == 'f') return res + c.food;
	if (fr == 'p') return res + c.production;
	return (res + c.gold);
}

void City::print(bool fullInfo) {
	std::cout << (this -> name);
	if (!fullInfo) return;

	// Print more if needed.
	// Remember to print(true) to execute the code below.
}

std::vector<Edge> City::gen_graph() {
	std::vector<Edge> res;
	for (int i = 0; i < City::cities.size(); ++i)
	for (int j = 0; j < City::cities.size(); ++j) {
		if (i == j) continue;

		// No direct traderoute available
		int dist = City::cities[i].dist(City::cities[j]);
		if (dist > 15) continue;

		int profit = City::cities[i].profit_score(City::cities[j]);
		res.push_back(Edge(i, j, dist, profit));
	}

	return res;
}
