#ifndef __SIMULATION_H__
#define __SIMULATION_H__

#include <stdint.h>
#include <vector>
#include <map>
#include <iostream>

struct Cell {
	int32_t y, x;
};

struct Dimension {
	int32_t x_min = 0, 
					x_max = 0, 
					y_min = 0,
					y_max = 0;
};

bool operator ==(const Cell&, const Cell&);
bool operator <(const Cell&, const Cell&);

std::ostream& operator<<(std::ostream&, const Cell&);

/**
	* Performs one timestep in the Game of Life simulation
	* That is, calculates which cells to kill/give birth to.
	*/
void simulate(Dimension& bounds, std::vector<Cell>& living, std::map<Cell, int32_t>& counted);

/**
	* Writes a list of cells as a vtk file.
	*/
void write_vtk(const Dimension& bounds, const char* filename, uint32_t step, const std::vector<Cell>& living_cells);

#endif //__SIMULATION_H__
