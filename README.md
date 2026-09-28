# Game Of Life
## Assignment 2
This codebase contains assignment 2 of the C++ module at UCL using OpenMP and MPI. The main goal of the project is to implement Conway's Game of Life (GOL), with some examples given in this document. The project defines a grid class and GameOfLife written by the author, and implements two main features:

- Execute GOL with shared memory and distributed memory
- Parallel still life search via distributed trials using MPI and asynchronous messaging

The code is designed with modularity in mind, and includes unit tests for core functionality. The project is compiled with CMake, which requires at least CMake version 3.28 and C++17.

### Project structure
```
Assignment1/
├── app/                # Application code (GolSimulator, GolSimulatorMPI GolStillLifeFinder)
├── benchmark/          # The benchmark test for strong scaling and week scaling vary the numbers of threads
├── GolLib/             # Library code (GolGrid, GamOfLife, GameOfLifeMPI, DistributeInitialGrid and GameOfLifeStillLifes)
├── test/               # Unit tests
├── CMakeLists.txt      # Main build configuration
├── README.md           # This file
└── Responses.md        # Response to all question in the PDF note
```

### GolLib code:
- `GolGrid` allows construct grids from files, random, and only size of grid (dead cell). It store cell data contiguously in buffer, while including the function like `setCell(row, col, value)`, `getCell(row, col)`, `countAlive()`, `checkEquivalence()`, etc.
- `GamOfLife`, simulating the GOL for a given grid including functions `takeStep()`, `printGrid()` and `getGrid()`.
- `GameOfLifeMPI`, the same objective like `GameOfLife` but in MPI distributed memory parallelism, including `exchangeBoundary(...)`, `gatherSubgridsMPI(...)` and `assembleGrid(...)`, etc.
- `DistributeInitialGrid`, extract sub grid from total grid using `extractSubGridBuffer` and `initialiseSubGrid`.
- `GameOfLifeStillLifes`, used to find Still Life Grid.

### App:
This assignment gives some examples using the application and puts the example in `Responses.md` file.

`GolSimulator` will simulating the GOL using OpenMP. 
`GolSimulatorMPI` will simulating the GOL using MPI. 
`GolStillLifeFinder` will find the target number of still life for a given grid size.

### Benchmark:
This part is mainly to verify the implement time of using different numbers of threads on the GOL of the Shared Memory Parallelism method. Specifically, I verified strong scaling and week scaling on my device and wrote the analysis in Part 3.2 of Responses.md. Run the code below to use the benchmark on the users own device, note there is no space between each number while each number means the thread number user want to test in benchmark (if not given will run 1 thread as default).

```bash
`./build/bin/GolBenchmarks -n 1,2,4,6,8,10,12,14,16`
```

## Dependence
This repository requires,
- C++17 or higher compiler.
- CMake 3.28+ for building.
- Catch2 for unit testing.

### Catch2:
Catch 2 is require for the unit test, run the code below to install,
```bash
git clone https://github.com/catchorg/Catch2 Catch2
cd Catch2
cmake -B build -DBUILD_TESTING=OFF
cmake --build build
cmake --install build/.
```

## Compile and build
In the same directory as this `README.md` file, run the following code in the terminal to build and compile,

```bash
cmake -B build
cmake --build build
```

Then you should now be able to find `GolBenchmarks`, `GolSimulator`, `GolSimulatorMPI`, `GolStillLifeFinder` and `GolTests` in the `/build/bin/` folder. To test this program, run `./build/bin/PROGRAM_NAME` in the terminal. The `GolTests` contains only the unit test for this project. All tests should be passed in normal situations when running `./build/bin/TestOptimisation` in terminal.

## Application
As described above, there are three main apps (ignoring the benchmark), and the following is an example of running the code:

### GolSimulator
The user can run the following code to see an example of glider GOL using share memory, and check more command options by add `-h` or `--help`.

```bash
OMP_NUM_THREADS=1 ./build/bin/GolSimulator -f test/data/glider.txt -g 26
```

### GolSimulatorMPI
The user can run the following code to see an example of glider GOL using MPI, and check more command options by add `-h` or `--help`. According to the requirements, this app will only output the initial grid and the result grid. If users are running this code on a laptop, the author strongly recommends using OMP_NUM_THREADS=1 to avoid inefficiencies caused by insufficient resources.

```bash
OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolSimulatorMPI -f ./test/data/glider.txt -g 26
```

### GolStillLifeFinder
Users can run the following code to view and use MPI's still life search example, and add `-h` or `--help` to view more command options. Since the code uses an asynchronous strategy, multiple runs with the same seed may have some differences. If users run this code on a laptop, the author strongly recommends using OMP_NUM_THREADS=1 to avoid inefficiencies caused by insufficient resources.

```bash
OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolStillLifeFinder -r 4 4 6 -g 10 -t 100 -n 5 -s 521
```
