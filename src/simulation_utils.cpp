#include <string.h>
#include <bits/stdc++.h>

#include <algorithm>
#include <sstream>
#include <fstream>


#include <simulation_utils.h>

bool operator ==(const Cell& lhs, const Cell& rhs) {
	return lhs.y == rhs.y && lhs.x == rhs.x;
}

bool operator <(const Cell& lhs, const Cell& rhs) {
	return (lhs.x < rhs.x) || ((lhs.x == rhs.x) && (lhs.y < rhs.y));
}

std::ostream& operator<<(std::ostream& os, const Cell& c) {
	os << c.x << " " << c.y;
	return os;
}

void simulate(Dimension& bounds, std::vector<Cell>& living_cells, std::map<Cell, int32_t>& counted_cells) {
	// Reset population counts
	counted_cells.clear();

	for (Cell c : living_cells) {
	 	// Update	
		counted_cells[{ c.y - 1, c.x - 1 }]++;
		counted_cells[{ c.y - 1, c.x     }]++;
		counted_cells[{ c.y - 1, c.x + 1 }]++;
		counted_cells[{ c.y    , c.x - 1 }]++;
		counted_cells[{ c.y    , c.x     }]++;
		counted_cells[{ c.y    , c.x + 1 }]++;
		counted_cells[{ c.y + 1, c.x - 1 }]++;
		counted_cells[{ c.y + 1, c.x     }]++;
		counted_cells[{ c.y + 1, c.x + 1 }]++;
	}

	std::vector<Cell> new_living_cells;
	new_living_cells.reserve(living_cells.capacity());
	
	bounds.x_min = INT_MAX;
	bounds.x_max = INT_MIN;
	bounds.y_min = INT_MAX;
	bounds.y_max = INT_MIN;

	// Foreach counted cell, set living if count is 3, or 4 + cell already lives. (Gather)
	for (auto& [cell, count] : counted_cells) {
		if (count == 3 || count == 4 && 
				std::find(living_cells.begin(), living_cells.end(), cell) != living_cells.end()) {
			new_living_cells.push_back(cell);

			// Recalculate population bounds
			if (cell.y < bounds.y_min)
				bounds.y_min = cell.y;
			if (cell.y > bounds.y_max)
				bounds.y_max = cell.y;
			if (cell.x < bounds.x_min)
				bounds.x_min = cell.x;
			if (cell.x > bounds.x_max)
				bounds.x_max = cell.x;
		}
	}

	// Move new living cells into living cells for next simulation
	living_cells = std::move(new_living_cells);
}

template <typename T>
void swap_endianness(T& value)
{
  char* value_ptr = reinterpret_cast<char*>(&value);
  for(long i = 0; i < static_cast<long>(sizeof(value)/2); i++)
    std::swap(value_ptr[sizeof(value) - 1 - i], value_ptr[i]);
}

void write_vtk(const Dimension& bounds, const char* filename, uint32_t cycle, const std::vector<Cell>& living_cells) {
	std::stringstream cc;
	cc << cycle;
	std::string filepath = "data/" + std::string(filename) + "_" + cc.str() + ".vtk";
	std::ofstream file (filepath.c_str());
	std::cout << "Writing file: " << filepath << std::endl;
	std::cout << "bounds: " 
		<< bounds.x_min << " " 
		<< bounds.x_max << " " 
		<< bounds.y_min << " " 
		<< bounds.y_max << std::endl;
	
	// Adjust bounds appropriately
	Dimension adjusted_bounds;
	adjusted_bounds.x_min = bounds.x_min - 10; //- //(20 + bounds.x_min % 20); 
	adjusted_bounds.x_max = bounds.x_max + 10; //+ //(20 - bounds.x_max % 20); 
	adjusted_bounds.y_min = bounds.y_min - 10; //- //(20 + bounds.y_min % 20); 
	adjusted_bounds.y_max = bounds.y_max + 10; //+ //(20 - bounds.y_max % 20); 

	// Width/height (including edge values)
	int32_t width = 1 + adjusted_bounds.x_max - adjusted_bounds.x_min;
	int32_t height = 1 + adjusted_bounds.y_max - adjusted_bounds.y_min;

	file << "# vtk DataFile Version 2.0" << std::endl;
	file << "Game of Life" << std::endl;
  file << "BINARY" << std::endl;
  file << "DATASET STRUCTURED_POINTS" << std::endl;
  file << "DIMENSIONS " << width << " " << height << " " << 1 << std::endl;
  file << "ORIGIN " 		
		<< adjusted_bounds.x_max - width / (double) 2 << " " 
		<< adjusted_bounds.y_max - height / (double) 2 << " " 
		<< 0.0 << std::endl;
  file << "SPACING "		<< 1.0 << " " << 1.0 << " " << 1.0 << std::endl;
  file << "POINT_DATA " << width * height << std::endl;
  file << "SCALARS cells float" << std::endl;
	file << "LOOKUP_TABLE default" << std::endl;
	
	for (int32_t y = adjusted_bounds.y_max; y >= adjusted_bounds.y_min; y--) {
		for (int32_t x = adjusted_bounds.x_min; x <= adjusted_bounds.x_max; x++) {
			Cell c = {.y = y, .x = x};
			if (std::find(living_cells.begin(), living_cells.end(), c) != living_cells.end()) {
				float value = 1;
				//file << value << std::endl;
				swap_endianness(value);
				file.write((char*)&value, sizeof(float));
			} else { 
				float value = 0;
				//file << value << std::endl;
				swap_endianness(value);
				file.write((char*)&value, sizeof(float));
			}
		}
	}

	file.close();
};
