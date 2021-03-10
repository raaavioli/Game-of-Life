#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <stdint.h>
#include <vector>
#include <set>
#include <iostream>

struct Cell {
	uint32_t y, x;
};

bool operator ==(const Cell&, const Cell&);
bool operator <(const Cell&, const Cell&);

std::ostream& operator<<(std::ostream&, const Cell&);

/**
	* Performs one timestep in the Game of Life simulation
	* That is, calculates which cells to kill/give birth to.
	*/
void simulate(const uint32_t width, const uint32_t height, uint32_t* population_counts,
		std::vector<Cell>& living, std::set<Cell>& counted);

/**
	* Writes a list of cells as a vtk file.
	*/
void write_vtk(const uint32_t width, const uint32_t height, 
		const char* filename, uint32_t step, const std::vector<Cell>& living_cells);

#endif //__SIMULATION_H__
