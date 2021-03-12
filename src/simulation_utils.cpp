#include <string.h>
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

void simulate(uint32_t width, uint32_t height, uint32_t* population_counts, 
		std::vector<Cell>& living_cells, std::set<Cell>& counted_cells) {
	// Reset population counts
	memset(population_counts, 0, width * height);
	
	// Reset counted_cells to 0 without reallocation.
	counted_cells.clear();

	// Foreach living cell
	for (Cell c : living_cells) {
		// Increment each neighboring cell's occurrence count, 
		// 	and mark it as counted
		population_counts[(c.y - 1) * width + (c.x - 1)]++;
		population_counts[(c.y - 1) * width + (c.x    )]++;
		population_counts[(c.y - 1) * width + (c.x + 1)]++;
		population_counts[(c.y    ) * width + (c.x - 1)]++;
		population_counts[(c.y    ) * width + (c.x    )]++;
		population_counts[(c.y    ) * width + (c.x + 1)]++;
		population_counts[(c.y + 1) * width + (c.x - 1)]++;
		population_counts[(c.y + 1) * width + (c.x    )]++;
		population_counts[(c.y + 1) * width + (c.x + 1)]++;
		
		counted_cells.insert({c.y - 1, c.x - 1});
		counted_cells.insert({c.y - 1, c.x    });
		counted_cells.insert({c.y - 1, c.x + 1});
		counted_cells.insert({c.y    , c.x - 1});
		counted_cells.insert({c.y    , c.x    });
		counted_cells.insert({c.y    , c.x + 1});
		counted_cells.insert({c.y + 1, c.x - 1});
		counted_cells.insert({c.y + 1, c.x    });
		counted_cells.insert({c.y + 1, c.x + 1});
	}

	std::vector<Cell> new_living_cells;
	new_living_cells.reserve(living_cells.capacity());

	// Foreach counted cell, set living if count is 3, or 4 + cell already lives. (Gather)
	for (Cell c : counted_cells) {
		if (population_counts[c.y * width + c.x] == 3 || 
				population_counts[c.y * width + c.x] == 4 && 
				std::find(living_cells.begin(), living_cells.end(), c) != living_cells.end()) {
			// Only add cell if it wouldn't contribute to out of bounds reads next iteration.
			if (c.x > 0 && c.x < width - 1 && c.y > 0 && c.y < height - 1)
				new_living_cells.push_back(c);		
		}
	}

	// Move new living cells into living cells for next simulation
	living_cells = std::move(new_living_cells);
}

template <typename T>
void SwapEnd(T& var)
{
  char* varArray = reinterpret_cast<char*>(&var);
  for(long i = 0; i < static_cast<long>(sizeof(var)/2); i++)
    std::swap(varArray[sizeof(var) - 1 - i],varArray[i]);
}

void write_vtk(uint32_t width, uint32_t height, const char* filename, uint32_t cycle, const std::vector<Cell>& living_cells) {
	std::stringstream cc;
	cc << cycle;
	std::string filepath = "data/" + std::string(filename) + "_" + cc.str() + ".vtk";
	std::ofstream file (filepath.c_str());
	//std::cout << "Writing file: " << filepath << std::endl;
	
	file << "# vtk DataFile Version 2.0" << std::endl;
	file << "Game of Life" << std::endl;
  file << "BINARY" << std::endl;
  file << "DATASET STRUCTURED_POINTS" << std::endl;
  file << "DIMENSIONS " << width << " " << height << " " << 1 << std::endl;
  file << "ORIGIN " 		<< 0.0 << " " << 0.0 << " " << 0.0 << std::endl;
  file << "SPACING "		<< 1.0 << " " << 1.0 << " " << 1.0 << std::endl;
  file << "POINT_DATA " << width * height << std::endl;
  file << "SCALARS rhoe float" << std::endl;
	file << "LOOKUP_TABLE default" << std::endl;

	for (uint32_t y = 0; y < height; y++) {
		for (uint32_t x = 0; x < width; x++) {
			Cell c = {y, x};
			if (std::find(living_cells.begin(), living_cells.end(), c) != living_cells.end()) {
				float value = 1;
				SwapEnd(value);
				file.write((char*)&value, sizeof(float));
			} else { 
				float value = 0;
				SwapEnd(value);
				file.write((char*)&value, sizeof(float));
			}
		}
	}

	file.close();
};
