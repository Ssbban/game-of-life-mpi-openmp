#include "GameOfLife.h"
#include "GameOfLifeStillLifes.h"
#include <iostream>
#include <mpi.h>
#include <omp.h>
#include <random>

void printCommand(const char* argv0)
{
    std::cout << "Usage: OMP_NUM_THREADS=<num_threads>" << argv0 << "[Options]" << std::endl;
    std::cout << R"(Options:
    Required:
    -r, --random <rows> <cols> <alive_num>      Initialise grid with random cells
                                                Three parameters are required: Row number, Column number, and Alive cell numbers
    Optional:
    -h, --help                                  Show this help message and exit
    -n, --stillLifes <num>                      Number of unique still lifes to find (default=5)
    -t, --trials <num>                          Maximum number of trials to attempt (default=20)
    -g, --generations <num>                     Max generations per trial before giving up (default=10)
    -s, --seed <seed>                           Random seed for reproducibility (default=none)
  )" << std::endl;
}

enum MSG_TAG : int
{
    MSG_FOUND = 100,
    MSG_DONE = 101,
    MSG_STOP = 102
};

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int process_id;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id);
    int num_proc;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc);

    //------------------------------------------------ Parase command line --------------------------------------
    if (process_id == 0 && argc == 1)
    {
        std::cerr << "ERROR! No command provide" << std::endl;
        printCommand(argv[0]);
        MPI_Finalize();
        return 1;
    }

    bool useRandom = false;
    int rows = 0;
    int cols = 0;
    int aliveCount = 0;
    int generations = 10;
    int maxTrials = 20;
    int targetStill = 5;
    unsigned seed = std::random_device{}();
    bool seedSpecified = false;

    // Parse all possible command
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            if (process_id == 0) printCommand(argv[0]);
            MPI_Finalize();
            return 0;
        }
        else if (arg == "-r" || arg == "--random")
        {
            if (i + 3 >= argc)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Missing parameters for -r option" << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                rows = std::stoi(argv[++i]);
                cols = std::stoi(argv[++i]);
                aliveCount = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Invalid parameter for -r option: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
            useRandom = true;
        }
        else if (arg == "-s" || arg == "--seed")
        {
            if (i + 1 >= argc)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Missing seed value for -s option" << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                seed = std::stoul(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id == 0) std::cerr << "ERROR! Invalid seed value: " << e.what() << std::endl;
                MPI_Finalize();
            }
            seedSpecified = true;
        }
        else if (arg == "-g" || arg == "--generations")
        {
            if (i + 1 >= argc)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Missing generation number for -g option" << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                generations = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Invalid generation number: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
        }
        else if (arg == "-t" || arg == "--trials")
        {
            if (i + 1 >= argc)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Missing trial number for -t option" << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                maxTrials = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Invalid trial number given: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
        }
        else if (arg == "-n" || arg == "--stillLifes")
        {
            if (i + 1 >= argc)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Missing still lifes target for -n option" << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                targetStill = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id == 0)
                {
                    std::cerr << "ERROR! Invalid still lifes target given: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
        }
        else
        {
            if (process_id == 0)
            {
                std::cerr << "ERROR! Unexpected option: " << arg << std::endl;
                printCommand(argv[0]);
            }
            MPI_Finalize();
            return 1;
        }
    }

    // Check all parameters are valid
    if (!useRandom)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! Random grid initialisation is required" << std::endl;
            printCommand(argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    if (rows <= 0 || cols <= 0)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! The number of rows and columns must be positive integers but " << rows << " and " << cols << " are given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (aliveCount < 0 || aliveCount > rows * cols)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! The number of alive cells must be between 0 and " << rows * cols << " but " << aliveCount << " is given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (generations <= 0)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! Require a positive number of generations but " << generations << " is given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (maxTrials <= 0)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! Require a positive number of trials but " << maxTrials << " is given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (targetStill <= 0)
    {
        if (process_id == 0)
        {
            std::cerr << "ERROR! Require a positive number of still lifes but " << targetStill << " is given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (maxTrials < targetStill)
    {
        if (process_id == 0)
        {
            std::cerr << "WARNING! The max trials number " << maxTrials << " is less than the target number of still lifes " << targetStill << std::endl;
        }
    }
    if (maxTrials < num_proc)
    {
        if (process_id == 0)
        {
            std::cerr << "WARNING! The number of processes " << num_proc << " is exceed the max trial number " << targetStill
                      << ". It is strongly recommended to use a smaller num_proce" << std::endl;
        }
    }
    //------------------------------------------------ Parase command line end --------------------------------------

    int quotient = maxTrials / num_proc;
    int remainder = maxTrials % num_proc;
    int localTrials = quotient + ((process_id < remainder) ? 1 : 0);

    unsigned local_seed = seed + process_id;
    std::mt19937 rng(local_seed);

    std::vector<gol::Grid> still_life_list;
    int foundCount = 0;
    int finishedProcs = 0;
    bool Done = false;
    bool localStop = false;
    int trialDone = 0;
    bool doneSent = false;

    if (process_id == 0)
    {
        std::cout << "MPI Still lifes finder start with " << num_proc << " processes..." << std::endl;
    }

    // Initialised all processes job
    while (!Done && !localStop)
    {
        if (process_id == 0)
        {
            leadCheckMsg(num_proc, foundCount, targetStill, still_life_list, finishedProcs, Done);
        }
        else
        {
            checkStopMsg(0, localStop);
        }

        if (!localStop)
        {
            if (trialDone < localTrials)
            {
                trialDone++;
                gol::Grid grid(rows, cols, aliveCount, rng);
                bool found = false;
                for (int gen = 0; gen < generations && !found; gen++)
                {
                    GameOfLife simulation(grid);
                    simulation.takeStep();
                    gol::Grid next_grid = simulation.getGrid();
                    if (checkStillLife(next_grid))
                    {
                        sendGrid(next_grid, 0, MSG_FOUND);
                        found = true;
                    }
                    grid = next_grid;
                }
            }
            else
            {
                if (!doneSent)
                {
                    MPI_Send(nullptr,
                             0,
                             MPI_CHAR,
                             0,
                             MSG_DONE,
                             MPI_COMM_WORLD);
                    doneSent = true;
                }
                localStop = true;
            }
        }

        if (process_id == 0)
        {
            leadCheckMsg(num_proc, foundCount, targetStill, still_life_list, finishedProcs, Done);
        }
        if (Done)
        {
            localStop = true;
        }
    }

    // Output the result
    if (process_id == 0)
    {
        std::cout << "Total unique still life found: " << still_life_list.size() << std::endl;
        if (!still_life_list.empty())
        {
            for (size_t i = 0; i < still_life_list.size(); i++)
            {
                std::cout << "#" << (i + 1) << ": Unique still life" << std::endl;
                still_life_list[i].print();
                std::cout << "==============================" << std::endl;
            }
        }
    }

    MPI_Finalize();
    return 0;
}
