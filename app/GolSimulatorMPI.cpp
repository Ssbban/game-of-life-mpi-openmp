#include "DistributeInitialGrid.h"
#include "GameOfLife.h"
#include "GameOfLifeMPI.h"
#include "GolGrid.h"
#include <fstream>
#include <mpi.h>
#include <omp.h>

void printCommand(const char* argv0)
{
    std::cout << "Usage: OMP_NUM_THREADS=<num_threads> mpirun -np <num_procs> " << argv0 << " [Command_options]" << std::endl;
    std::cout << R"(
    Command options:
    -h, --help                                  Show this help message and exit
    -np <num_procs>                             Number of processes to run the simulation
    -f, --file <filename>                       Initialise grid from the specified text file
    -r, --random <rows> <cols> <alive_num>      Initialise grid with random cells
                                                Three parameters are required: Row number, Column number, and Alive cell numbers
    -s, --seed <seed>                           Optional: specify random seed (only valid with random initialisation)
    -g, --generations <num>                     Optional: Number of generations to simulate (default = 10)
    -o, --output <output_filename>              Optional: Output the result for a given directery
  )" << std::endl;
}

int main(int argc, char** argv)
{
    MPI_Init(&argc, &argv);

    int process_id_world;
    MPI_Comm_rank(MPI_COMM_WORLD, &process_id_world);
    int num_proc_world;
    MPI_Comm_size(MPI_COMM_WORLD, &num_proc_world);

    //------------------------------------------------ Parase command line --------------------------------------
    if (argc == 1)
    {
        if (process_id_world == 0)
        {
            std::cerr << "ERROR! No command provided" << std::endl;
            printCommand(argv[0]);
        }
        MPI_Finalize();
        return 1;
    }

    bool useFile = false;
    bool useRandom = false;
    std::string filename;
    int rows = 0, cols = 0;
    int aliveCount = 0;
    int generations = 10;
    size_t seed = std::random_device{}();
    bool seedSpecified = false;
    std::string output_filename;
    bool outputSpecified = false;
    std::ofstream outFile;

    // Parse all possible command
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            if (process_id_world == 0)
            {
                printCommand(argv[0]);
            }
            MPI_Finalize();
            return 0;
        }
        else if (arg == "-f" || arg == "--file")
        {
            if (i + 1 >= argc)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Missing filename for option " << arg << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            filename = argv[++i];
            useFile = true;
        }
        else if (arg == "-r" || arg == "--random")
        {
            if (i + 3 >= argc)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Missing parameters for option " << arg << std::endl;
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
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Invalid parameter for random initialisation: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
            if (rows <= 0 || cols <= 0)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! The number of rows and columns must be positive integers but " << rows << " and " << cols << " are given" << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
            if (aliveCount < 0 || aliveCount > rows * cols)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! The number of alive cells must be between 0 and " << rows * cols << " but " << aliveCount << " is given" << std::endl;
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
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Missing seed value for option " << arg << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            try
            {
                seed = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Invalid seed value: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
            seedSpecified = true;
        }
        else if (arg == "-g" || arg == "--generations")
        {
            if (i + 1 >= argc)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Missing generation number for option " << arg << std::endl;
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
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Invalid generation number: " << e.what() << std::endl;
                }
                MPI_Finalize();
                return 1;
            }
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 >= argc)
            {
                if (process_id_world == 0)
                {
                    std::cerr << "ERROR! Missing output filename for option " << arg << std::endl;
                    printCommand(argv[0]);
                }
                MPI_Finalize();
                return 1;
            }
            output_filename = argv[++i];
            outputSpecified = true;
        }
        else
        {
            if (process_id_world == 0)
            {
                std::cerr << "Unexpected option given: " << arg << std::endl;
                printCommand(argv[0]);
            }
            MPI_Finalize();
            return 1;
        }
    }

    // Check mutually exclusive terms
    if (useFile && useRandom)
    {
        if (process_id_world == 0)
        {
            std::cerr << "ERROR! File input and random initialisation are mutually exclusive" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (!useFile && !useRandom)
    {
        if (process_id_world == 0)
        {
            std::cerr << "ERROR! Must provide either input file or random initialisation options" << std::endl;
            printCommand(argv[0]);
        }
        MPI_Finalize();
        return 1;
    }
    if (seedSpecified && useFile)
    {
        if (process_id_world == 0)
        {
            std::cerr << "ERROR! Seed option is not allowed when using file input" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    if (generations <= 0)
    {
        if (process_id_world == 0)
        {
            std::cerr << "ERROR! Require a positive number of generations but " << generations << " is given" << std::endl;
        }
        MPI_Finalize();
        return 1;
    }
    //------------------------------------------------ Parase command line end --------------------------------------

    // Generate initial global grid in process 0
    gol::Grid global_grid(0, 0);
    if (process_id_world == 0)
    {
        try
        {
            if (useFile)
            {
                global_grid = gol::Grid(filename);
                rows = global_grid.getRows();
                cols = global_grid.getCols();
            }
            else if (useRandom)
            {
                std::mt19937 rng(seed);
                global_grid = gol::Grid(rows, cols, aliveCount, rng);
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR! Initialising global grid failed: " << e.what() << std::endl;
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
    }

    MPI_Bcast(&rows, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(&cols, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Create a new comm if total proc larger than rows
    int color = (process_id_world < rows) ? 0 : 1;
    MPI_Comm new_comm;
    MPI_Comm_split(MPI_COMM_WORLD, color, process_id_world, &new_comm);
    if (color == 1)
    {
        std::cerr << "WARNING: Abort processes " << process_id_world << " since total number of processes (" << num_proc_world << ") exceeds the row size of grid (" << rows << ")" << std::endl;
        MPI_Finalize();
        return 0;
    }

    int process_id;
    MPI_Comm_rank(new_comm, &process_id);
    int num_proc;
    MPI_Comm_size(new_comm, &num_proc);

    // Initialise sub-grid
    int quotient = rows / num_proc;
    int remainder = rows % num_proc;
    int sub_rows = quotient + (process_id < remainder ? 1 : 0);
    int sub_cols = cols;
    gol::Grid sub_grid(sub_rows, sub_cols);

    if (process_id == 0)
    {
        bool* buffer = extractSubGridBuffer(global_grid, num_proc, 0);
        initialiseSubGrid(buffer, sub_grid);
        delete[] buffer;

        // Send the sub-grid message
        for (size_t p = 1; p < num_proc; p++)
        {
            int p_sub_rows = quotient + (p < remainder ? 1 : 0);
            bool* send_buffer = extractSubGridBuffer(global_grid, num_proc, p);
            MPI_Send(send_buffer,
                     p_sub_rows * sub_cols,
                     MPI_CXX_BOOL,
                     p,
                     0,
                     new_comm);
            delete[] send_buffer; // Free the memory allocated in extractSubGridBuffer
        }
    }
    else
    {
        bool* recv_buffer = new bool[sub_rows * sub_cols];
        MPI_Recv(recv_buffer,
                 sub_rows * sub_cols,
                 MPI_CXX_BOOL,
                 0,
                 0,
                 new_comm,
                 MPI_STATUS_IGNORE);
        initialiseSubGrid(recv_buffer, sub_grid);
        delete[] recv_buffer;
    }

    if (outputSpecified && process_id == 0)
    {
        outFile.open(output_filename);
        if (!outFile.is_open())
        {
            std::cerr << "ERROR! Failed to open output file: " << output_filename << std::endl;
            MPI_Abort(new_comm, 1);
        }
    }

    // Implement the GOL
    bool* top_boundary = nullptr;
    bool* bottom_boundary = nullptr;
    bool* initial_data = gatherSubgridsMPI(sub_grid, process_id, num_proc, rows, cols, new_comm);
    gol::Grid initial_grid = assembleGrid(initial_data, process_id, rows, cols);

    for (int gen = 0; gen < generations; gen++)
    {
        exchangeBoundary(sub_grid, process_id, num_proc, top_boundary, bottom_boundary, new_comm);
        takeStepMPI(sub_grid, process_id, num_proc, top_boundary, bottom_boundary);
    }
    MPI_Barrier(new_comm);

    bool* final_data = gatherSubgridsMPI(sub_grid, process_id, num_proc, rows, cols, new_comm);
    gol::Grid final_grid = assembleGrid(final_data, process_id, rows, cols);

    if (process_id == 0)
    {
        if (outputSpecified)
        {
            outFile << "Start grid: \n";
            initial_grid.print(outFile);
            outFile << "==============================" << std::endl;
            outFile << "Final grid: \n";
            final_grid.print(outFile);
        }
        else
        {
            std::cout << "Start grid: \n";
            initial_grid.print();
            std::cout << "==============================" << std::endl;
            std::cout << "Final grid: \n";
            final_grid.print();
        }
    }
    if (outputSpecified && process_id == 0)
    {
        outFile.close();
    }

    MPI_Finalize();
    return 0;
}