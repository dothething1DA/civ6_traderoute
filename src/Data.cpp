#include "Data.h"
#include "City.h"

#include <string>
#include <fstream>
#include <iostream>

const std::string filePath = "../data/cities.txt";

std::fstream file;

void openFile() {
	file.open(filePath, std::ios::in);
}

void closeFile() {
	file.close();
}

void load() {
	openFile();

	// read data from file
	while (true) {
		std::string name;
		file >> name;

		// If end of file or file is broken
		if (!file.good()) break;

		char focusedRs;
		file >> focusedRs;

		int cx, cy;
		file >> cx >> cy;

		int food, production, gold;
		file >> food >> production >> gold;

		if (!file.good()) {
			std::cout << "Invalid format. Please check input file";
			exit(0);
		}

		City::create_city(name, focusedRs, cx, cy, food, production, gold);
	}

	closeFile();
}
