#include <gtest/gtest.h>

#include <simulation_utils.h>

TEST(SimulationTest, TestSinglePopulationDies) {
	// Arrange
	std::map<Cell, int32_t> counted_cells;
	std::vector<Cell> living_cells;

	living_cells.push_back({0,0});
	Dimension d = {.x_min = 0, .x_max = 0, .y_min = 0, .y_max = 0};

	// Act
	simulate(d, living_cells, counted_cells);

	// Assert
	ASSERT_EQ(living_cells.size(), 0);
	ASSERT_EQ(counted_cells.size(), 9);
	for (int y = -1; y <= 1; y++) {
		for (int x = -1; x <= 1; x++) {
			int32_t actual = counted_cells[{y, x}];
			ASSERT_EQ(actual, 1);
		}
	}
}

TEST(SimulationTest, TestSimpleReproduction) {
	// Arrange
	std::map<Cell, int32_t> counted_cells;
	std::vector<Cell> living_cells;
	std::vector<Cell> expected;

	/**
		DDDDD    DDLDD
		DLLLD -> DDLDD
		DDDDD    DDLDD
	*/	
	living_cells.push_back({0,-1});
	living_cells.push_back({0,0});
	living_cells.push_back({0,1});
	Dimension dim = {.x_min = -1, .x_max = 1, .y_min = 0, .y_max = 0};

	expected.push_back({-1,0});
	expected.push_back({0,0});
	expected.push_back({1,0});
	Dimension expected_dim = {.x_min = 0, .x_max = 0, .y_min = -1, .y_max = 1};

	// Act
	simulate(dim, living_cells, counted_cells);

	// Assert
	ASSERT_EQ(living_cells.size(), expected.size());
	for (int i = 0; i < expected.size(); i++) {
		ASSERT_EQ(living_cells[i], expected[i]);
	}

	ASSERT_EQ(counted_cells.size(), 15);
	ASSERT_EQ(dim.x_min, expected_dim.x_min);
	ASSERT_EQ(dim.x_max, expected_dim.x_max);
	ASSERT_EQ(dim.y_min, expected_dim.y_min);
	ASSERT_EQ(dim.y_max, expected_dim.y_max);
}


TEST(SimulationTest, TestCourseDescriptionExample) {
	// Arrange
	std::map<Cell, int32_t> counted_cells;
	std::vector<Cell> living_cells;
	std::vector<Cell> expected;

	/**
		DDD      DDD
		DLDDD    DLDD
		DLLLD -> DLLD
		DDDDD    DDLD
              DDD
	*/	
	living_cells.push_back({0,0});
	living_cells.push_back({1,0});
	living_cells.push_back({0,1});
	living_cells.push_back({0,2});
	Dimension dim = {.x_min = 0, .x_max = 2, .y_min = 0, .y_max = 1};

	expected.push_back({0,0});
	expected.push_back({1,0});
	expected.push_back({-1,1});
	expected.push_back({0,1});
	Dimension expected_dim = {.x_min = 0, .x_max = 1, .y_min = -1, .y_max = 1};

	// Act
	simulate(dim, living_cells, counted_cells);

	// Assert
	ASSERT_EQ(living_cells.size(), expected.size());
	ASSERT_EQ(living_cells.size(), 4);
	for (int i = 0; i < expected.size(); i++) {
		ASSERT_EQ(living_cells[i], expected[i]);
	}

	ASSERT_EQ(counted_cells.size(), 18);
	ASSERT_EQ(dim.x_min, expected_dim.x_min);
	ASSERT_EQ(dim.x_max, expected_dim.x_max);
	ASSERT_EQ(dim.y_min, expected_dim.y_min);
	ASSERT_EQ(dim.y_max, expected_dim.y_max);
}

TEST(SimulationTest, TestInfinitePattern) {

}
