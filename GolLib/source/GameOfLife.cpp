#include "GameOfLife.h"
#include <algorithm>
#include <utility>

GameOfLife::GameOfLife(const gol::Grid& intitial_grid) : current_grid(intitial_grid) {}

void GameOfLife::takeStep()
{
    size_t rows = current_grid.getRows();
    size_t cols = current_grid.getCols();
    gol::Grid next_grid(rows, cols);

#pragma omp parallel for collapse(2) default(none) shared(rows, cols, current_grid, next_grid)
    for (size_t i = 0; i < rows; i++)
    {
        for (size_t j = 0; j < cols; j++)
        {
            bool current_status = current_grid.getCell(i, j);
            size_t neighborCount = current_grid.getNeighboursAlive(i, j);

            bool next_status = false;
            if (!current_status && neighborCount == 3)
            {
                next_status = true;
            }
            else if (current_status && (neighborCount == 2 || neighborCount == 3))
            {
                next_status = true;
            }
            next_grid.setCell(i, j, next_status);
        }
    }
    current_grid = next_grid;
}

void GameOfLife::printGrid(std::ostream& os) const
{
    current_grid.print(os);
    os << "==============================" << std::endl;
}

const gol::Grid& GameOfLife::getGrid() const
{
    return current_grid;
}