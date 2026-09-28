#include "DistributeInitialGrid.h"

bool* extractSubGridBuffer(const gol::Grid& global_grid, int num_proc, int process_id)
{
    // Calculate the number of rows and columns for the sub-grid
    size_t rows = global_grid.getRows();
    size_t cols = global_grid.getCols();
    int quotient = rows / num_proc;
    int remainder = rows % num_proc;

    int sub_rows = quotient + (process_id < remainder ? 1 : 0);
    int sub_cols = cols;
    int start_row = process_id * quotient + (process_id < remainder ? process_id : remainder);
    bool* buffer = new bool[sub_rows * sub_cols];

    for (int i = 0; i < sub_rows; i++)
    {
        for (int j = 0; j < sub_cols; j++)
        {
            buffer[i * sub_cols + j] = global_grid.getCell(start_row + i, j);
        }
    }
    return buffer;
}

void initialiseSubGrid(bool* buffer, gol::Grid& sub_grid)
{
    size_t sub_rows = sub_grid.getRows();
    size_t sub_cols = sub_grid.getCols();
    for (size_t i = 0; i < sub_rows; i++)
    {
        for (size_t j = 0; j < sub_cols; j++)
        {
            sub_grid.setCell(i, j, buffer[i * sub_cols + j]);
        }
    }
}