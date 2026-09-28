#include "DistributeInitialGrid.h"
#include "GameOfLife.h"
#include "GameOfLifeMPI.h"
#include "GameOfLifeStillLifes.h"
#include "GolGrid.h"
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_all.hpp>

using namespace Catch::Matchers;

// TEST_CASE("A test", "Example test")
// {
//     int a = 5;
//     REQUIRE(a < 6);
// }

/****************************************************************************/
/* Section 1.1 - Grid Testing
/****************************************************************************/
TEST_CASE("Check normal function for Grid", "Grid test")
{
    // Initialised the grid
    gol::Grid grid(5, 5);
    REQUIRE(grid.getRows() == 5);
    REQUIRE(grid.getCols() == 5);
    REQUIRE(grid.countAlive() == 0);

    // Set alive cells
    grid.setCell(1, 2, true);
    grid.setCell(2, 0, true);
    grid.setCell(2, 2, true);
    grid.setCell(3, 1, true);
    grid.setCell(3, 2, true);

    REQUIRE(grid.getCell(1, 2) == true);
    REQUIRE(grid.getCell(2, 0) == true);
    REQUIRE(grid.getCell(2, 2) == true);
    REQUIRE(grid.getCell(3, 1) == true);
    REQUIRE(grid.getCell(3, 2) == true);
    REQUIRE(grid.getCell(0, 0) == false);

    REQUIRE(grid.countAlive() == 5);

    // Check equivalence grid
    gol::Grid other(5, 5);
    other.setCell(2, 0, true);
    other.setCell(2, 2, true);
    other.setCell(3, 1, true);
    other.setCell(3, 2, true);
    other.setCell(1, 2, true);
    REQUIRE(grid.checkEquivalence(other) == true);

    other.setCell(0, 0, true);
    REQUIRE(grid.checkEquivalence(other) == false);

    // Check print the grid
    // grid.print();
}

/****************************************************************************/
/* Section 1.2 - Initial the grid at random test
/****************************************************************************/
TEST_CASE("Check Grid initialised at random", "Grid test")
{
    // Initialised the grid at random
    std::mt19937 rng(123);
    gol::Grid grid_random(5, 5, 8, rng);
    REQUIRE(grid_random.getRows() == 5);
    REQUIRE(grid_random.getCols() == 5);
    REQUIRE(grid_random.countAlive() == 8);

    // Check different random initialisation
    std::mt19937 rng_2(1);
    gol::Grid grid_random_2(5, 5, 8, rng_2);
    std::mt19937 rng_3(123);
    gol::Grid grid_random_3(5, 5, 8, rng_3);
    REQUIRE(grid_random_2.checkEquivalence(grid_random) == false);
    REQUIRE(grid_random_3.checkEquivalence(grid_random) == true);
}

/****************************************************************************/
/* Section 1.3 - Initialising the grid from a file
/****************************************************************************/
TEST_CASE("Check Grid initialised by a given file", "Grid test")
{
    // Initialised the grid by hand
    gol::Grid grid_glider_manual(10, 10);
    grid_glider_manual.setCell(1, 2, true);
    grid_glider_manual.setCell(2, 0, true);
    grid_glider_manual.setCell(2, 2, true);
    grid_glider_manual.setCell(3, 1, true);
    grid_glider_manual.setCell(3, 2, true);

    // Initialised the grid by file and check
    gol::Grid grid_glider("test/data/glider.txt");
    REQUIRE(grid_glider.checkEquivalence(grid_glider_manual) == true);

    gol::Grid grid_oscillator("test/data/oscillators.txt");
    REQUIRE(grid_glider.checkEquivalence(grid_glider_manual) == true);
    REQUIRE(grid_oscillator.getRows() == 12);
    REQUIRE(grid_oscillator.getCols() == 12);
    REQUIRE(grid_oscillator.countAlive() == 23);
    REQUIRE(grid_oscillator.getCell(7, 1) == true);
    REQUIRE(grid_oscillator.getCell(7, 2) == true);

    gol::Grid grid_still_life("test/data/still_lifes.txt");
    REQUIRE(grid_still_life.getRows() == 10);
    REQUIRE(grid_still_life.getCols() == 10);
    REQUIRE(grid_still_life.countAlive() == 19);
    REQUIRE(grid_still_life.getCell(1, 2) == true);
    REQUIRE(grid_still_life.getCell(2, 0) == true);

    REQUIRE_THROWS_AS(gol::Grid("test/data/input.txt"), std::runtime_error);
}

/****************************************************************************/
/* Section 1.4 - Fetching live neighbours
/****************************************************************************/
TEST_CASE("Check the number of live neighbours", "Grid test")
{
    // Initialised the grid
    gol::Grid grid(5, 5);
    grid.setCell(1, 2, true);
    grid.setCell(2, 0, true);
    grid.setCell(2, 2, true);
    grid.setCell(3, 1, true);
    grid.setCell(3, 2, true);

    // Check the number of live neighbours
    REQUIRE(grid.getNeighboursAlive(2, 2) == 3);
    REQUIRE(grid.getNeighboursAlive(3, 0) == 2);
    REQUIRE(grid.getNeighboursAlive(4, 0) == 1);
    REQUIRE(grid.getNeighboursAlive(0, 0) == 0);
}

/****************************************************************************/
/* Section 4.2 - Game of Life MPI
/****************************************************************************/
TEST_CASE("Test sub-grid distribution strategy", "MPI Test")
{
    // Initialise the global grid
    const int rows = 20;
    const int cols = 10;
    const int num_proc = 3;
    unsigned seed = 123;
    int aliveCount = rows * cols * 0.2;
    std::mt19937 rng(seed);
    gol::Grid global_grid(rows, cols, aliveCount, rng);

    int quotient = rows / num_proc;
    int remainder = rows % num_proc;
    int expected_sub_rows[num_proc] = {7, 7, 6};

    // Check my strategy works for each sub-grid
    for (int p = 0; p < num_proc; p++)
    {
        int sub_rows = quotient + (p < remainder ? 1 : 0);
        int sub_cols = cols;
        gol::Grid sub_grid(sub_rows, sub_cols);

        bool* buffer = extractSubGridBuffer(global_grid, num_proc, p);
        initialiseSubGrid(buffer, sub_grid);
        delete[] buffer;

        int start_row = p * quotient + (p < remainder ? p : remainder);
        for (int i = 0; i < sub_rows; i++)
        {
            for (int j = 0; j < sub_cols; j++)
            {
                bool expected_cell = global_grid.getCell(start_row + i, j);
                bool actual_cell = sub_grid.getCell(i, j);
                REQUIRE(actual_cell == expected_cell);
            }
        }
        REQUIRE(sub_grid.getRows() == expected_sub_rows[p]);
        REQUIRE(sub_grid.getCols() == cols);
    }
}

/****************************************************************************/
/* Section 4.4 - Grid assembly and output
/****************************************************************************/
TEST_CASE("Test sub-grid assembly where rows are not divisible by num_proc", "MPI Test")
{
    size_t rows = 7;
    size_t cols = 5;
    size_t num_proc = 5;

    gol::Grid global_grid(rows, cols);
    {
        std::mt19937 rng(123);
        std::uniform_int_distribution<int> dist(0, 1);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                bool val = (dist(rng) == 1);
                global_grid.setCell(r, c, val);
            }
        }
    }

    // Divede the global grid into three sub-grids as three processes
    int quotient = rows / num_proc;
    int remainder = rows % num_proc;
    bool* global_buffer = new bool[rows * cols];
    int offset = 0;

    for (int p = 0; p < num_proc; p++)
    {
        int sub_rows = quotient + ((p < remainder) ? 1 : 0);
        bool* sub_buffer = extractSubGridBuffer(global_grid, num_proc, p);

        gol::Grid subGrid(sub_rows, cols);
        initialiseSubGrid(sub_buffer, subGrid);

        for (int r = 0; r < sub_rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                global_buffer[(offset + r) * cols + c] = subGrid.getCell(r, c);
            }
        }
        offset += sub_rows;
        delete[] sub_buffer;
    }

    gol::Grid final_grid = assembleGrid(global_buffer, 0, rows, cols);
    REQUIRE(final_grid.getRows() == rows);
    REQUIRE(final_grid.getCols() == cols);
    REQUIRE(final_grid.checkEquivalence(global_grid) == true);

    delete[] global_buffer;
}

TEST_CASE("Test sub-grid assembly and output for row is divided by num_proc", "MPI Test")
{
    size_t rows = 9;
    size_t cols = 9;
    size_t num_proc = 3;

    gol::Grid global_grid(rows, cols);
    {
        std::mt19937 rng(123);
        std::uniform_int_distribution<int> dist(0, 1);
        for (int r = 0; r < rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                bool val = (dist(rng) == 1);
                global_grid.setCell(r, c, val);
            }
        }
    }

    // Divede the global grid into three sub-grids as three processes
    int quotient = rows / num_proc;
    int remainder = rows % num_proc;
    bool* global_buffer = new bool[rows * cols];
    int offset = 0;

    for (int p = 0; p < num_proc; p++)
    {
        int sub_rows = quotient + ((p < remainder) ? 1 : 0);
        bool* sub_buffer = extractSubGridBuffer(global_grid, num_proc, p);

        gol::Grid subGrid(sub_rows, cols);
        initialiseSubGrid(sub_buffer, subGrid);

        for (int r = 0; r < sub_rows; r++)
        {
            for (int c = 0; c < cols; c++)
            {
                global_buffer[(offset + r) * cols + c] = subGrid.getCell(r, c);
            }
        }
        offset += sub_rows;
        delete[] sub_buffer;
    }

    gol::Grid final_grid = assembleGrid(global_buffer, 0, rows, cols);
    REQUIRE(final_grid.getRows() == rows);
    REQUIRE(final_grid.getCols() == cols);
    REQUIRE(final_grid.checkEquivalence(global_grid) == true);

    delete[] global_buffer;
}

/****************************************************************************/
/* Section 5.1 - SillLifes Finder Serial approach
/****************************************************************************/
TEST_CASE("Test grid evolution for still life", "StillLifes")
{
    // Still life grid
    gol::Grid still_file_1("./test/data/still_life_test_1.txt");
    gol::Grid still_file_2("./test/data/still_life_test_2.txt");
    gol::Grid still_file("test/data/still_lifes.txt");
    gol::Grid still_block(4, 4);
    still_block.setCell(1, 1, true);
    still_block.setCell(1, 2, true);
    still_block.setCell(2, 1, true);
    still_block.setCell(2, 2, true);

    REQUIRE(checkStillLife(still_file_1) == true);
    REQUIRE(checkStillLife(still_file_2) == true);
    REQUIRE(checkStillLife(still_file) == true);
    REQUIRE(checkStillLife(still_block) == true);

    GameOfLife simulation(still_file);
    simulation.takeStep();
    gol::Grid next_still_file = simulation.getGrid();
    REQUIRE(still_file.checkEquivalence(next_still_file));

    // Non-still life grid
    gol::Grid not_still_glider("test/data/glider.txt");
    gol::Grid not_still_glider_2("test/data/gosper_glider_gun.txt");
    REQUIRE(checkStillLife(not_still_glider) == false);
    REQUIRE(checkStillLife(not_still_glider_2) == false);

    GameOfLife simulation_2(not_still_glider_2);
    simulation_2.takeStep();
    gol::Grid next_glider_2 = simulation_2.getGrid();
    REQUIRE(not_still_glider_2.checkEquivalence(next_glider_2) == false);
}

TEST_CASE("Test uniqueness of still life grids", "StillLifes")
{
    // Construct still life grids
    size_t rows = 4;
    size_t cols = 4;
    gol::Grid dead_grid(rows, cols);

    gol::Grid still_block(rows, cols);
    still_block.setCell(1, 1, true);
    still_block.setCell(1, 2, true);
    still_block.setCell(2, 1, true);
    still_block.setCell(2, 2, true);

    gol::Grid still_file("test/data/still_lifes.txt");
    gol::Grid still_file_1("test/data/still_life_test_1.txt");
    gol::Grid still_file_2("test/data/still_life_test_2.txt");

    // Check the uniqueness of still life grids
    std::vector<gol::Grid> still_lifes_list;
    still_lifes_list.push_back(dead_grid);
    still_lifes_list.push_back(still_block);
    still_lifes_list.push_back(still_file);

    gol::Grid another_dead(rows, cols);
    REQUIRE(checkUnique(still_block, still_lifes_list) == false);
    REQUIRE(checkUnique(another_dead, still_lifes_list) == false);
    REQUIRE(checkUnique(still_file, still_lifes_list) == false);

    REQUIRE(checkUnique(still_file_1, still_lifes_list) == true);
    REQUIRE(checkUnique(still_file_2, still_lifes_list) == true);
    still_lifes_list.push_back(still_file_1);
    still_lifes_list.push_back(still_file_2);
    REQUIRE(checkUnique(still_file_1, still_lifes_list) == false);
    REQUIRE(checkUnique(still_file_2, still_lifes_list) == false);
}