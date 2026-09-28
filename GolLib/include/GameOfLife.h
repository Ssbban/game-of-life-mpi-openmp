#pragma once
#include "GolGrid.h"

class GameOfLife
{
public:
    /**
     * @brief This function takes a grid object and initialises the Game of Life simulation
     * @param initial_grid: The initial grid to be used for the simulation
     */
    GameOfLife(const gol::Grid& initial_grid);

    /**
     * @brief This function takes a step in the GOL simulation
     */
    void takeStep();

    /**
     * @brief This function intialised the received buffer contents to the specified sub-grid object
     * @param os: The output stream to print the grid to
     */
    void printGrid(std::ostream& os = std::cout) const;

    /**
     * @brief This function use to get the current grid
     * Hepful if need to print each step during GOL
     */
    const gol::Grid& getGrid() const;

private:
    gol::Grid current_grid;
};