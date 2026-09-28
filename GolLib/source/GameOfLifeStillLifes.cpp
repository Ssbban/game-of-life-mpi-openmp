#include "GameOfLifeStillLifes.h"
#include "GameOfLife.h"
#include <mpi.h>

bool checkStillLife(const gol::Grid& grid)
{
    GameOfLife simulation(grid);
    simulation.takeStep();
    gol::Grid next_grid = simulation.getGrid();
    return grid.checkEquivalence(next_grid);
}

bool checkUnique(const gol::Grid& grid, const std::vector<gol::Grid>& stillLifes)
{
    for (const auto& sl : stillLifes)
    {
        if (grid.checkEquivalence(sl))
        {
            return false;
        }
    }
    return true;
}

void sendGrid(const gol::Grid& grid, int dest, int tag)
{
    int rows = grid.getRows();
    int cols = grid.getCols();

    int meta[2] = {rows, cols};
    MPI_Send(meta,
             2,
             MPI_INT,
             dest,
             tag,
             MPI_COMM_WORLD);

    bool* buffer = new bool[rows * cols];
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            buffer[r * cols + c] = grid.getCell(r, c);
        }
    }
    MPI_Send(buffer,
             rows * cols,
             MPI_CXX_BOOL,
             dest,
             tag,
             MPI_COMM_WORLD);
    delete[] buffer;
}

gol::Grid recvGrid(int dest, int tag)
{
    MPI_Status status;

    int meta[2];
    MPI_Recv(meta,
             2,
             MPI_INT,
             dest,
             tag,
             MPI_COMM_WORLD,
             &status);
    int rows = meta[0];
    int cols = meta[1];

    bool* buffer = new bool[rows * cols];
    MPI_Recv(buffer,
             rows * cols,
             MPI_CXX_BOOL,
             dest,
             tag,
             MPI_COMM_WORLD,
             &status);

    gol::Grid g(rows, cols);
    for (int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            g.setCell(r, c, buffer[r * cols + c]);
        }
    }
    delete[] buffer;
    return g;
}

enum MSG_TAG : int
{
    MSG_FOUND = 100,
    MSG_DONE = 101,
    MSG_STOP = 102
};

void checkStopMsg(int source_process_id, bool& localStop)
{
    int flag = 0;
    MPI_Status st;
    MPI_Iprobe(source_process_id,
               MSG_STOP,
               MPI_COMM_WORLD,
               &flag,
               &st);
    if (flag == 1)
    {
        char dummy_msg;
        MPI_Recv(&dummy_msg,
                 1,
                 MPI_CHAR,
                 source_process_id,
                 MSG_STOP,
                 MPI_COMM_WORLD,
                 &st);
        localStop = true;
    }
}

void leadCheckMsg(int num_proc, int& foundCount, int target_still, std::vector<gol::Grid>& still_life_list, int& finished_proc, bool& globalDone)
{
    int flag = 0;
    MPI_Status st;
    MPI_Iprobe(MPI_ANY_SOURCE,
               MPI_ANY_TAG,
               MPI_COMM_WORLD,
               &flag,
               &st);
    if (!flag) return;

    int src = st.MPI_SOURCE;
    int tag = st.MPI_TAG;
    if (tag == MSG_FOUND)
    {
        // Discart exceed message
        gol::Grid found_grid = recvGrid(src, MSG_FOUND);
        if (foundCount >= target_still)
        {
            return;
        }
        // Add the unique still life grid
        if (checkStillLife(found_grid) && checkUnique(found_grid, still_life_list))
        {
            still_life_list.push_back(found_grid);
            foundCount++;
            if (foundCount >= target_still)
            {
                for (int p = 1; p < num_proc; p++)
                {
                    char dummy_msg;
                    MPI_Send(&dummy_msg,
                             1,
                             MPI_CHAR,
                             p,
                             MSG_STOP,
                             MPI_COMM_WORLD);
                }
                globalDone = true;
            }
        }
    }

    else if (tag == MSG_DONE)
    {
        MPI_Recv(nullptr,
                 0,
                 MPI_CHAR,
                 src,
                 MSG_DONE,
                 MPI_COMM_WORLD,
                 &st);
        finished_proc++;
        if (finished_proc == num_proc)
        {
            globalDone = true;
        }
    }
};