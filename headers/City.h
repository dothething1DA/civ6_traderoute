#ifndef City_H
#define City_H

#include "Graph.h"
#include <string>
#include <vector>

class City {
public:
	static std::vector<City> cities;

	City() {}
	City(std::string name, char fr, int x, int y, int f, int p, int g):
	name(name), focusedRs(fr), cx(x), cy(y), food(f), production(p), gold(g) {}

	int dist(City &c);
	int profit_score(City &c); // Profit score for traderoute to city c
	void print(bool fullInfo=false);

	static std::vector<Edge> gen_graph(); // Generate edge list from all instances of the class
	static void create_city(std::string name, char fr, int x, int y, int f, int p, int g) {
		cities.emplace_back(name, fr, x, y, f, p, g);
	}

private:
	std::string name;
	char focusedRs;

	int cx, cy; // coordinates
	int food, production, gold; // bonus
};

#endif
