// Header includes
#include <stdint.h>

// C++ stdlib includes 
#include <vector>
#include <iostream>

// 3rd party libraries

// Own includes
#include <simulation_utils.h>

int main(int argc, char* argv[]) {
	const uint32_t width = 300, height = 300;
	
	// Dense vector with living cells
	std::vector<Cell> living_cells;
	const uint32_t dw = 30, dh = 30;
	for (int y = 0; y < dh; y++) {
		for (int x = 0; x < dw; x++) {
			if (x == 10 || x == 20 || y == 10 || y == 20) {
				living_cells.push_back({
					height / 2 - dh / 2 + y, 
					width / 2 - dw / 2 + x
				}); 
			}		
		}
	}

	// Dense vector with counted cells (reached from any living cell)
	std::set<Cell> counted_cells;
	
	// Sparse matrix for keeping population counts
	uint32_t* population_counts = new uint32_t[width * height];

	//Simulation
	uint32_t cycle = 1;
	while (true) {
		write_vtk(width, height, "out", cycle, living_cells);	
	
		simulate(width, height, population_counts, living_cells, counted_cells);
		cycle++;
	}

	delete[] population_counts;
}

