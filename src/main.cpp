// Header includes
#include <stdint.h>

// C++ stdlib includes 
#include <iostream>

// 3rd party libraries

// Own includes
#include <simulation_utils.h>

#include <ctime>
#include <time.h>

int main(int argc, char* argv[]) {	
	Dimension bounds = {.x_min = 0, .x_max = 11, .y_min = 0, .y_max = 2};
	std::vector<Cell> living_cells;

	living_cells.push_back({0, 2});
	living_cells.push_back({1, 2});
	living_cells.push_back({1, 0});
	living_cells.push_back({2, 2});
	living_cells.push_back({2, 1});

	living_cells.push_back({0, 9});
	living_cells.push_back({1, 9});
	living_cells.push_back({2, 9});
	living_cells.push_back({1, 11});
	living_cells.push_back({2, 10});

	living_cells.push_back({10, 3});
	living_cells.push_back({10, 2});
	living_cells.push_back({11, 3});
	living_cells.push_back({11, 1});
	living_cells.push_back({12, 3});

	living_cells.push_back({10, 8});
	living_cells.push_back({10, 9});
	living_cells.push_back({11, 8});
	living_cells.push_back({11, 10});
	living_cells.push_back({12, 8});
//  Random cells 
//	 srand(time(0));
//	for (int y = -30; y < 30; y++) {
//		for (int x = -30; x < 30; x++) {
//			if(rand() % 3 == 0)
//				living_cells.push_back({y, x});
//		}
//	}

	// Dense vector with counted cells (reached from any living cell)
	std::map<Cell, int32_t> counted_cells;

	//Simulation
	uint32_t cycle = 1;

	std::clock_t vtk_total;
	vtk_total -= vtk_total;
	std::clock_t simulate_total;
	simulate_total -= simulate_total;	
	while (true) {	
		auto t_vtk = std::clock();
			write_vtk(bounds, "out", cycle, living_cells);	
		vtk_total += ( std::clock() - t_vtk ) * 1000000 / (double) CLOCKS_PER_SEC;


		auto t_sim = std::clock();
			simulate(bounds, living_cells, counted_cells);
		simulate_total += ( std::clock() - t_sim ) * 1000000 / (double) CLOCKS_PER_SEC;

		std::cout << "Living cells: " << living_cells.size() << std::endl;
		//std::cout << "Counted cells: " << counted_cells.size() << std::endl;
		//std::cout << "Bounds width: " << bounds.x_max - bounds.x_min 
		// << ", height: " << bounds.y_max - bounds.y_min << std::endl;

		//		std::cout << "IO cycles per sec: " 
//			<< vtk_total / (double) cycle 
//			<< "microseconds, SIM per cycle: " 
//			<< simulate_total / (double) cycle << "microseconds" <<std::endl;
//		std::cout << "Living cells: " << living_cells.size() << std::endl;

		cycle++;
	}
}

