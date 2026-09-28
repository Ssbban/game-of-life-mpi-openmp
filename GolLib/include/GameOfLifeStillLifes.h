#pragma once
#include "GolGrid.h"
#include <mpi.h>

/**
 * @brief This function checks the input grid is still life or not
 * @param grid: The grid of GOL
 */
bool checkStillLife(const gol::Grid& grid);

/**
 * @brief This function check the uniqueness of current grid with the still lifes list
 *
 * @param grid: The current grid of GOL
 * @param stillLifes_list: The list of still life
 */
bool checkUnique(const gol::Grid& grid, const std::vector<gol::Grid>& stillLifes_list);

/**
 * @brief This function send the grid message
 *
 * @param grid: The current grid of GOL
 * @param dest: The rank of the process send the message to in the given communicator.
 * @param tag: An integer identifier which can be used to distinguish between types of messages.
 */
void sendGrid(const gol::Grid& grid, int dest, int tag);

/**
 * @brief This function receive the grid message
 *
 * @param dest: The rank of the process send the message to in the given communicator.
 * @param tag: An integer identifier which can be used to distinguish between types of messages.
 */
gol::Grid recvGrid(int dest, int tag);

/**
 * @brief This function let the other processes to check the stop message send form lead process
 *
 * @param source_process_id: The other process id
 * @param localStop: The local stop signal
 */
void checkStopMsg(int source_process_id, bool& localStop);

/**
 * @brief This function used to asynchronously check and process messages sent by all processes
 *
 * @param num_proc: The total number of process
 * @param foundCount: The number of still life have founded
 * @param target_still: The target number of still life
 * @param still_life_list: The list of still life grids
 * @param finished_procs: The number of finished processes
 * @param globalDone: The bool type for global done or not
 */
void leadCheckMsg(int num_proc, int& foundCount, int target_still, std::vector<gol::Grid>& still_life_list, int& finished_procs, bool& globalDone);