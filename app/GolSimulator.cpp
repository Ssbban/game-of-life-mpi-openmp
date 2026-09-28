#include "GameOfLife.h"
#include "GolGrid.h"
#include <fstream>
#include <omp.h>
#include <thread>

void printCommand(const char* argv0)
{
    std::cout << "Usage: OMP_NUM_THREADS=<num_threads> " << argv0 << " [Command_options]" << std::endl;
    std::cout << R"(Command options:
    -h, --help                                  Show this help message and exit
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
    //------------------------------------------------ Parase command line --------------------------------------
    if (argc == 1)
    {
        std::cerr << "ERROR! No command provided" << std::endl;
        printCommand(argv[0]);
        return 1;
    }

    bool useFile = false;
    bool useRandom = false;
    std::string filename;
    int rows = 0;
    int cols = 0;
    int aliveCount = 0;
    size_t seed = std::random_device{}();
    bool seedSpecified = false;
    int generations = 10;
    std::string output_filename;
    bool outputSpecified = false;
    std::ofstream outFile;

    // Parse all possible command
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "-h" || arg == "--help")
        {
            printCommand(argv[0]);
            return 0;
        }
        else if (arg == "-f" || arg == "--file")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR! Missing filename for option " << arg << std::endl;
                printCommand(argv[0]);
                return 1;
            }
            filename = argv[++i];
            useFile = true;
        }
        else if (arg == "-r" || arg == "--random")
        {
            if (i + 3 >= argc)
            {
                std::cerr << "ERROR! Missing parameters for option " << arg << std::endl;
                printCommand(argv[0]);
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
                std::cerr << "ERROR! Invalid parameter for random initialisation due to " << e.what() << " is fail" << std::endl;
                return 1;
            }
            if (rows <= 0 || cols <= 0)
            {
                std::cerr << "ERROR! The number of rows and columns must be positive integers but " << rows << " and " << cols << " are given" << std::endl;
                return 1;
            }
            if (aliveCount < 0 || aliveCount > rows * cols)
            {
                std::cerr << "ERROR! The number of alive cells must be between 0 and " << rows * cols << " but " << aliveCount << " is given" << std::endl;
                return 1;
            }
            useRandom = true;
        }
        else if (arg == "-s" || arg == "--seed")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR! Missing seed value for option " << arg << std::endl;
                printCommand(argv[0]);
                return 1;
            }
            try
            {
                seed = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                std::cerr << "ERROR! Invalid seed value due to" << e.what() << " is fail" << std::endl;
                return 1;
            }
            seedSpecified = true;
        }
        else if (arg == "-g" || arg == "--generations")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR! Missing generation number for option " << arg << std::endl;
                printCommand(argv[0]);
                return 1;
            }
            try
            {
                generations = std::stoi(argv[++i]);
            }
            catch (const std::exception& e)
            {
                std::cerr << "ERROR! Invalid generation number: " << e.what() << std::endl;
                return 1;
            }
        }
        else if (arg == "-o" || arg == "--output")
        {
            if (i + 1 >= argc)
            {
                std::cerr << "ERROR! Missing output filename for option " << arg << std::endl;
                printCommand(argv[0]);
                return 1;
            }
            output_filename = argv[++i];
            outputSpecified = true;
        }
        else
        {
            std::cerr << "Unexpected option given: " << arg << std::endl;
            printCommand(argv[0]);
            return 1;
        }
    }

    // Check all parameters are valid
    if (useFile && useRandom)
    {
        throw std::runtime_error("ERROR! File input and random initialisation are mutually exclusive");
    }
    if (!useFile && !useRandom)
    {
        std::cerr << "ERROR! Require either input file or random generator to initialised the grid" << std::endl;
        printCommand(argv[0]);
        return 1;
    }
    if (seedSpecified && useFile)
    {
        throw std::runtime_error("ERROR! Using text file to initialised the grid but seed is given");
    }
    if (generations <= 0)
    {
        std::cerr << "ERROR! Require a positive number of generations but " << generations << " is given" << std::endl;
        return 1;
    }

    // Initialised grid
    gol::Grid initial_grid(0, 0);
    if (useFile)
    {
        try
        {
            initial_grid = gol::Grid(filename);
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR! Initialising grid from file is fail due to " << e.what() << std::endl;
            return 1;
        }
    }
    else if (useRandom)
    {
        std::mt19937 rng(seed);
        try
        {
            initial_grid = gol::Grid(rows, cols, aliveCount, rng);
        }
        catch (const std::exception& e)
        {
            std::cerr << "ERROR! Initialising random grid is fail because " << e.what() << std::endl;
            return 1;
        }
    }

    if (outputSpecified)
    {
        outFile.open(output_filename);
        if (!outFile.is_open())
        {
            std::cerr << "ERROR! Could not open output file " << output_filename << std::endl;
            return 1;
        }
    }
    //------------------------------------------------ Parase command line --------------------------------------

    // Implement the GOL
    GameOfLife simulation(initial_grid);
    for (int gen = 0; gen < generations + 1; gen++)
    {
        std::string output_head = "Generation " + std::to_string(gen) + ":\n";
        if (outputSpecified)
        {
            outFile << output_head;
            simulation.printGrid(outFile);
            simulation.takeStep();
        }
        else
        {
            std::cout << output_head;
            simulation.printGrid();
            simulation.takeStep();
            std::this_thread::sleep_for(std::chrono::milliseconds(300));
        }
    }
    if (outputSpecified)
    {
        outFile.close();
    }

    return 0;
}
