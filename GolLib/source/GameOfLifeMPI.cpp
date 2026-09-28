#include "GameOfLifeMPI.h"
#include "GameOfLife.h"
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mpi.h>
#include <sstream>
#include <thread>

void exchangeBoundary(gol::Grid& sub_grid, int process_id, int num_proc, bool*& top_boundary, bool*& bottom_boundary, MPI_Comm comm)
{
    size_t sub_rows = sub_grid.getRows();
    size_t sub_cols = sub_grid.getCols();
    top_boundary = new bool[sub_cols]();
    bottom_boundary = new bool[sub_cols]();

    // Exchange top and bottom boundaries with neighboring processes
    if (process_id > 0)
    {
        bool* send_buffer = new bool[sub_cols];
        for (int j = 0; j < sub_cols; j++)
            send_buffer[j] = sub_grid.getCell(0, j);

        if (process_id % 2 == 0)
        {
            MPI_Send(send_buffer, sub_cols, MPI_CXX_BOOL, process_id - 1, 1, comm);
            MPI_Recv(top_boundary, sub_cols, MPI_CXX_BOOL, process_id - 1, 2, comm, MPI_STATUS_IGNORE);
        }
        else
        {
            MPI_Recv(top_boundary, sub_cols, MPI_CXX_BOOL, process_id - 1, 2, comm, MPI_STATUS_IGNORE);
            MPI_Send(send_buffer, sub_cols, MPI_CXX_BOOL, process_id - 1, 1, comm);
        }
        delete[] send_buffer;
    }

    if (process_id < num_proc - 1)
    {
        bool* send_buffer = new bool[sub_cols];
        for (int j = 0; j < sub_cols; j++)
        {
            send_buffer[j] = sub_grid.getCell(sub_rows - 1, j);
        }

        if (process_id % 2 == 0)
        {
            MPI_Send(send_buffer, sub_cols, MPI_CXX_BOOL, process_id + 1, 2, comm);
            MPI_Recv(bottom_boundary, sub_cols, MPI_CXX_BOOL, process_id + 1, 1, comm, MPI_STATUS_IGNORE);
        }
        else
        {
            MPI_Recv(bottom_boundary, sub_cols, MPI_CXX_BOOL, process_id + 1, 1, comm, MPI_STATUS_IGNORE);
            MPI_Send(send_buffer, sub_cols, MPI_CXX_BOOL, process_id + 1, 2, comm);
        }
        delete[] send_buffer;
    }
}

void takeStepMPI(gol::Grid& sub_grid, int process_id, int num_proc, bool*& top_boundary, bool*& bottom_boundary)
{
    // Initialize the grid
    size_t sub_rows = sub_grid.getRows();
    size_t sub_cols = sub_grid.getCols();
    gol::Grid extended_grid(sub_rows + 2, sub_cols);

    for (int j = 0; j < sub_cols; j++)
    {
        extended_grid.setCell(0, j, (process_id > 0) ? top_boundary[j] : false);
    }
    for (int i = 0; i < sub_rows; i++)
    {
        for (int j = 0; j < sub_cols; j++)
        {
            extended_grid.setCell(i + 1, j, sub_grid.getCell(i, j));
        }
    }
    for (int j = 0; j < sub_cols; j++)
    {
        extended_grid.setCell(sub_rows + 1, j, (process_id < num_proc - 1) ? bottom_boundary[j] : false);
    }

    // Update the extended grid using GameOfLife
    GameOfLife gol_simulator(extended_grid);
    gol_simulator.takeStep();
    gol::Grid updated_grid = gol_simulator.getGrid();
    for (int i = 0; i < sub_rows; i++)
    {
        for (int j = 0; j < sub_cols; j++)
        {
            sub_grid.setCell(i, j, updated_grid.getCell(i + 1, j));
        }
    }
}

bool* gatherSubgridsMPI(const gol::Grid& sub_grid, int process_id, int num_proc, int rows, int cols, MPI_Comm comm)
{
    int count = sub_grid.getRows() * cols;
    if (process_id == 0)
    {
        bool* global_buffer = new bool[rows * cols];
        for (int i = 0; i < sub_grid.getRows(); i++)
        {
            for (int j = 0; j < cols; j++)
            {
                global_buffer[i * cols + j] = sub_grid.getCell(i, j);
            }
        }

        // Receive sub-grids data from other processes
        int quotient = rows / num_proc;
        int remainder = rows % num_proc;
        int row_start = quotient + (0 < remainder ? 1 : 0);
        for (int p = 1; p < num_proc; p++)
        {
            int p_rows = quotient + (p < remainder ? 1 : 0);
            int p_count = p_rows * cols;
            int offset = row_start * cols;
            MPI_Recv(global_buffer + offset,
                     p_count,
                     MPI_CXX_BOOL,
                     p,
                     3,
                     comm,
                     MPI_STATUS_IGNORE);
            row_start += p_rows;
        }
        return global_buffer;
    }

    else
    {
        bool* send_buffer = new bool[count];
        for (int i = 0; i < sub_grid.getRows(); i++)
        {
            for (int j = 0; j < cols; j++)
            {
                send_buffer[i * cols + j] = sub_grid.getCell(i, j);
            }
        }
        MPI_Send(send_buffer,
                 count,
                 MPI_CXX_BOOL,
                 0,
                 3,
                 comm);
        delete[] send_buffer;
        return nullptr;
    }
}

gol::Grid assembleGrid(const bool* assemble_buffer, int process_id, int rows, int cols)
{
    if (!assemble_buffer)
    {
        return gol::Grid(0, 0);
    }
    gol::Grid global_grid(rows, cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            global_grid.setCell(r, c, assemble_buffer[r * cols + c]);
        }
    }
    return global_grid;
}
