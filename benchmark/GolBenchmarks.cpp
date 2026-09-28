#include "GameOfLife.h"
#include "GolGrid.h"
#include <chrono>
#include <iostream>
#include <omp.h>
#include <sstream>
#include <string>
#include <vector>

class BenchmarkData
{
public:
    BenchmarkData(std::string benchmarkName, unsigned int threads)
        : name(benchmarkName), numThreads(threads)
    {
    }
    double time;
    std::string name;
    unsigned int numThreads;
    std::string info;

    void start()
    {
        t1 = std::chrono::high_resolution_clock::now();
    }

    void finish()
    {
        std::chrono::high_resolution_clock::time_point t2 =
            std::chrono::high_resolution_clock::now();
        time = (t2 - t1).count() / 1e9;
    }

    std::chrono::high_resolution_clock::time_point t1;
};

inline void parseThreads(std::vector<unsigned int>& threads,
                         const std::string& input)
{
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ','))
    {

        if (std::stol(token) < 0)
            throw std::invalid_argument(
                "Negative argument in --numthreads option: " + token);
        try
        {
            threads.push_back(std::stoul(token));
        }
        catch (...)
        {
        }
    }
}

std::ostream& operator<<(std::ostream& os, const BenchmarkData& b)
{
    std::cout << "Benchmarking " << b.name << " with " << b.numThreads
              << " threads." << std::endl;
    std::cout << "Time = " << b.time << std::endl;
    std::cout << "Info: " << b.info << std::endl;
    return os;
}

int main(int argc, char** argv)
{
    std::vector<unsigned int> numThreads = {1}; // Default to single thread

    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--numthreads" || arg == "-n" && (i + 1 < argc))
        {
            numThreads.clear();
            parseThreads(numThreads, argv[i + 1]);
            ++i;
        }
    }

    std::cout << "Running benchmarks with the following numbers of threads: ";
    for (unsigned int t : numThreads)
    {
        std::cout << t << " ";
    }
    std::cout << std::endl;

    // Strong scaling
    const size_t dim = 1000;
    unsigned seed = 123;
    std::mt19937 rng(seed);
    gol::Grid strong_grid(dim, dim, 0.2 * dim * dim, rng);
    GameOfLife strongScaling(strong_grid);

    for (auto t : numThreads)
    {
        omp_set_num_threads(t);

        BenchmarkData strong_data("Strong Scaling", t);

        strong_data.start();
        strongScaling.takeStep();
        strong_data.finish();

        strong_data.info = "Grid=" + std::to_string(dim) + "x" + std::to_string(dim) + ", iteration=1, random initial with 20" + "%" + " alive";
        std::cout << strong_data << std::endl;
    }

    // Week scaling
    std::mt19937 rng2(123);

    for (auto t : numThreads)
    {
        omp_set_num_threads(t);
        size_t dim_week_scale = 1000 * std::sqrt(double(t));
        gol::Grid week_grid(dim_week_scale, dim_week_scale, 0.2 * dim_week_scale * dim_week_scale, rng2);

        BenchmarkData week_data("Weak Scaling", t);
        GameOfLife weekScaling(week_grid);

        week_data.start();
        weekScaling.takeStep();
        week_data.finish();

        week_data.info = "Grid=" + std::to_string(dim_week_scale) + "x" + std::to_string(dim_week_scale) + ", iteration=1, random initial with 20" + "%" + " alive";
        std::cout << week_data << std::endl;
    }

    return 0;
}