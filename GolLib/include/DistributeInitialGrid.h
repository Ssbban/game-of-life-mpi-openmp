#pragma once
#include "GolGrid.h"

/**
 * @brief This function extract the sub-grid data corresponding to a given process number from the global grid
 *
 * Divide the global grid into num_proc rows as evenly as possible and return a boolean array buffer of the subgrids corresponding to the specified process_id.
 * The number of rows allocated is determined by the division quotient and remainder, with the first remainder processes getting an extra row each.
 *
 * @param global_grid: The global grid is the original grid that is to be divided into sub-grids
 * @param num_proc: The number of processes
 * @param process_id: The process id of the current process
 * @return A pointer to the buffer containing the sub-grid data
 */
bool* extractSubGridBuffer(const gol::Grid& global_grid, int num_proc, int process_id);

/**
 * @brief This function intialised the received buffer contents to the specified sub-grid object
 *
 * @param buffer: The buffer containing the sub-grid data
 * @param sub_grid: The sub-grid object to be initialised
 */
void initialiseSubGrid(bool* buffer, gol::Grid& sub_grid);