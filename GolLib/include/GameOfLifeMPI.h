#pragma once
#include "GolGrid.h"
#include <cstdlib>
#include <iostream>
#include <mpi.h>

/**
 * @brief This function exchanges the top and bottom boundaries message of the sub-grid with neighboring processes
 *
 * This function is designed depend on MPI communication.
 *
 * @param sub_grid: The sub-grid of the current process
 * @param process_id: The process id of the current process
 * @param num_proc: The total number of processes
 * @param top_boundary: The top boundary of the sub-grid
 * @param bottom_boundary: The bottom boundary of the sub-grid
 * @param comm: The new communicator that consider too many processes given case
 */
void exchangeBoundary(gol::Grid& sub_grid, int process_id, int num_proc, bool*& top_boundary, bool*& bottom_boundary, MPI_Comm comm);

/**
 * @brief This function takes a step in the Game of Life simulation
 *
 * This function is designed to be used in a parallel MPI environment depending on the previously OpenMP code.
 * User can set the number of OMP threads to be 1 if don't have enough cores on their machine.
 *
 * @param sub_grid: The sub-grid of the current process
 * @param process_id: The process id of the current process
 * @param num_proc: The total number of processes
 * @param top_boundary: The top boundary buffer
 * @param bottom_boundary: The bottom boundary buffer
 */
void takeStepMPI(gol::Grid& sub_grid, int process_id, int num_proc, bool*& top_boundary, bool*& bottom_boundary);

/**
 * @brief This function gathers the sub-grid buffer from other processes
 *
 * This function is designed to be used in a parallel MPI environment.
 *
 * @param sub_grid: The sub-grid of the current process
 * @param process_id: The process id of the current process
 * @param num_proc: The total number of processes
 * @param rows: The row number of grid
 * @param cols: The column number of grid
 * @param comm: The new communicator that consider too many processes given case
 */
bool* gatherSubgridsMPI(const gol::Grid& sub_grid, int process_id, int num_proc, int rows, int cols, MPI_Comm comm);

/**
 * @brief This function reassembles the global grid from the sub-grids of all processes
 *
 * @param sub_grid: The sub-grid of the current process
 * @param process_id: The process id of the current process
 * @param num_proc: The total number of processes
 * @param rows: The row number of grid
 * @param cols: The column number of grid
 */
gol::Grid assembleGrid(const bool* buffer, int process_id, int rows, int cols);
