# Respones

## Part 2.4: Running the application

There are two application cases here, which should run `cmake -B build` and `cmake --build build` at first to compile and build the excutable file.

### For glider.txt input file for 26 evolutions

Go the top folder and run following code to implement the simulation,

```bash
./build/bin/GolSimulator -f test/data/glider.txt -g 26
```

the result is,

```
Generation 0:
- - - - - - - - - - 
- - o - - - - - - - 
o - o - - - - - - - 
- o o - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 1:
- - - - - - - - - - 
- o - - - - - - - - 
- - o o - - - - - - 
- o o - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 2:
- - - - - - - - - - 
- - o - - - - - - - 
- - - o - - - - - - 
- o o o - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 3:
- - - - - - - - - - 
- - - - - - - - - - 
- o - o - - - - - - 
- - o o - - - - - - 
- - o - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 4:
- - - - - - - - - - 
- - - - - - - - - - 
- - - o - - - - - - 
- o - o - - - - - - 
- - o o - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 5:
- - - - - - - - - - 
- - - - - - - - - - 
- - o - - - - - - - 
- - - o o - - - - - 
- - o o - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 6:
- - - - - - - - - - 
- - - - - - - - - - 
- - - o - - - - - - 
- - - - o - - - - - 
- - o o o - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 7:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - o - o - - - - - 
- - - o o - - - - - 
- - - o - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 8:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - o - - - - - 
- - o - o - - - - - 
- - - o o - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 9:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - o - - - - - - 
- - - - o o - - - - 
- - - o o - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 10:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - o - - - - - 
- - - - - o - - - - 
- - - o o o - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 11:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - o - o - - - - 
- - - - o o - - - - 
- - - - o - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 12:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - o - - - - 
- - - o - o - - - - 
- - - - o o - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 13:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - o - - - - - 
- - - - - o o - - - 
- - - - o o - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 14:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - o - - - - 
- - - - - - o - - - 
- - - - o o o - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 15:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - o - o - - - 
- - - - - o o - - - 
- - - - - o - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 16:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - o - - - 
- - - - o - o - - - 
- - - - - o o - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 17:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - o - - - - 
- - - - - - o o - - 
- - - - - o o - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 18:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - o - - - 
- - - - - - - o - - 
- - - - - o o o - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Generation 19:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - o - o - - 
- - - - - - o o - - 
- - - - - - o - - - 
- - - - - - - - - - 

==============================
Generation 20:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - o - - 
- - - - - o - o - - 
- - - - - - o o - - 
- - - - - - - - - - 

==============================
Generation 21:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - o - - - 
- - - - - - - o o - 
- - - - - - o o - - 
- - - - - - - - - - 

==============================
Generation 22:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - o - - 
- - - - - - - - o - 
- - - - - - o o o - 
- - - - - - - - - - 

==============================
Generation 23:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - o - o - 
- - - - - - - o o - 
- - - - - - - o - - 

==============================
Generation 24:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - o - 
- - - - - - o - o - 
- - - - - - - o o - 

==============================
Generation 25:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - o - - 
- - - - - - - - o o 
- - - - - - - o o - 

==============================
Generation 26:
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - o - 
- - - - - - - - - o 
- - - - - - - o o o 

==============================
```

###  7 by 7 grid with 15 random initial cells for 4 evolutions

Run the following code in terminal,

```bash
./build/bin/GolSimulator -r 7 7 15 -s 123 -g 4
```

I use seed value `seed = 123` here in this case, which need to re-use latter. The result including the initial grid value is,

```
Generation 0:
o - o - o - - 
- - - o - o - 
o - o - - - - 
o o - - - o o 
- - - - - - o 
o - - - - o o 
- - - - - - - 

==============================
Generation 1:
- - - o o - - 
- - o o o - - 
o - o - o o o 
o o - - - o o 
o o - - - - - 
- - - - - o o 
- - - - - - - 

==============================
Generation 2:
- - o - o - - 
- o o - - - - 
o - o - - - o 
- - o - o - o 
o o - - - - - 
- - - - - - - 
- - - - - - - 

==============================
Generation 3:
- o o o - - - 
- - o - - - - 
- - o - - o - 
o - o o - o - 
- o - - - - - 
- - - - - - - 
- - - - - - - 

==============================
Generation 4:
- o o o - - - 
- - - - - - - 
- - o - o - - 
- - o o o - - 
- o o - - - - 
- - - - - - - 
- - - - - - - 

==============================
```

## Part 3.2: Shared Memory Parallelism

I run the benchmark for strong scaling and weak scaling with random 20% cells alive initialisation, `Grid size = 1000 * 1000` and one generation only. The results run for `thread numbers = {1, 2, 4, 6, 8, 10, 12, 14, 16}`. The user can run the code `./build/bin/GolBenchmarks -n 1,2,4,6,8,10,12,14,16` to get the benchmark on their device (the number of threads could vary depending on their device, noticed that a command separated list with no spaces). The below block gives the benchmark result in my device:

```
Running benchmarks with the following numbers of threads: 1 2 4 6 8 10 12 14 16 
Benchmarking Strong Scaling with 1 threads.
Time = 0.0109439
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 2 threads.
Time = 0.00565892
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 4 threads.
Time = 0.00310902
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 6 threads.
Time = 0.00275024
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 8 threads.
Time = 0.00236673
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 10 threads.
Time = 0.00221222
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 12 threads.
Time = 0.00203219
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 14 threads.
Time = 0.00230223
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Strong Scaling with 16 threads.
Time = 0.0034521
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 1 threads.
Time = 0.0105518
Info: Grid=1000x1000, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 2 threads.
Time = 0.0113709
Info: Grid=1414x1414, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 4 threads.
Time = 0.0109387
Info: Grid=2000x2000, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 6 threads.
Time = 0.0118497
Info: Grid=2449x2449, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 8 threads.
Time = 0.0204562
Info: Grid=2828x2828, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 10 threads.
Time = 0.0217768
Info: Grid=3162x3162, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 12 threads.
Time = 0.0225102
Info: Grid=3464x3464, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 14 threads.
Time = 0.0235397
Info: Grid=3741x3741, iteration=1, random initial with 20% alive

Benchmarking Weak Scaling with 16 threads.
Time = 0.0303836
Info: Grid=4000x4000, iteration=1, random initial with 20% alive
```

Conclude these results in the table below, noticed that the speedup is defined as the ratio of the time taken for thread 1 to the time taken for thread n `Time(threads_n) / Time(threads_1)`,

- For Strong Scaling:
Strong scaling is a size-fixed problem while increasing the number of threads to reduce the running time. Here we observe how the speedup changes with the number of threads. Ideal scaling generally means that computing performance increases linearly with the increase in the number of threads, that is, when the number of threads becomes `N` times the original, the time required is `1/N` times the original, or the speedup ratio is N times the original.

```
Threads |   Grid Size   |   Time (s)   |  Speedup
----------------------------------------------------
1       |  1000 x 1000  |  0.01094390  |   1.00
2       |  1000 x 1000  |  0.00565892  |   1.93
4       |  1000 x 1000  |  0.00310902  |   3.52
6       |  1000 x 1000  |  0.00275024  |   3.98
8       |  1000 x 1000  |  0.00236673  |   4.62
10      |  1000 x 1000  |  0.00221222  |   4.95
12      |  1000 x 1000  |  0.00203219  |   4.25
14      |  1000 x 1000  |  0.00230223  |   4.75
16      |  1000 x 1000  |  0.00345210  |   3.17
```

However, the above result shows that when the number of threads increases from 1 to 2, 4, 6 and 8, the time taken is significantly shortened, while obtaining an approximated linear relationship between the speedup ratio and thread number. However, the speedup ratio does not change significantly as the number of threads increases further, while the highest speedup ratio is approximately 5. 


- For Week Scaling:
For weak scaling, we will increase the problem size in the same proportion as we increase the number of threads, which means that if the number of threads becomes `N` times the original, the problem size becomes `N` times the original (`Grid size = Rows * Cols * N`). Therefore, for ideal weak scaling, we expect that the running time will not increase as the number of threads increases, that is, speedup always remains at 1. This is because in ideal weak scaling, the problem size increases as the number of threads increases, so the problem size that each thread needs to handle remains the same.

In this assignment, we use $`(1000 * \sqrt(thread_num)) × (1000 * \sqrt(thread_num))`$ as the weak scaling model. Although the number of threads that is not a perfect square needs to be rounded appropriately, resulting in the total problem size not necessarily being exactly times thread_num, this can ensure that the Grid size remains square and consistent with strong scaling, and this error can be ignored since it is relatively small.

```
Threads |   Grid Size   |   Time (s)   |  Speedup
----------------------------------------------------
1       |  1000 x 1000  |  0.0105518   |   1.00
2       |  1414 x 1414  |  0.0113709   |   1.08
4       |  2000 x 2000  |  0.0109387   |   1.04
6       |  2449 x 2449  |  0.0118497   |   1.12
8       |  2828 x 2828  |  0.0204562   |   1.94
10      |  3162 x 3162  |  0.0217768   |   2.06
12      |  3464 x 3464  |  0.0225102   |   2.13
14      |  3741 x 3741  |  0.0235397   |   2.23
16      |  4000 x 4000  |  0.0303836   |   2.88
```

It can be seen that the results at `thread number = {1, 2, 4, 6}` are almost in line with the ideal scalability and are only slightly higher than 1. However, as expected, the results from `thread number = 6` to `thread number = 16` show that the required implementation time increases rapidly, which means a bad scaling in larger thread numbers.

- Why:
The above result does not seem to be consistent with our expected idea scaling, which may be for the following two reasons: 1. With more thread numbers, the total time spent decreases, and the weight of overhead (such as creating and destroying threads) increases. 2. Hyper-threading technology makes the operating system think that the number of cores is twice the number of cores that exist physically. Because my device only has 8 physical cores. Strictly speaking, it is difficult for us to get performance improvements by using more threads than available cores. This is why the performance improvement is almost the highest when I use 8 threads.

## Part 4.1: Distributed Memory Parallelism
When parallelizing the grid to a distributed memory environment, at each time step, we can divide the entire grid into sub-grids. Each MPI process is responsible for updating its local sub-grid. However, the boundary cells of the sub-grid need to synchronize the boundary messages of other processes (the states of the external cell) to achieve correct updates. Therefore, it is necessary to exchange boundary data information with adjacent regions at each update step and correctly update each process according to the rules of the GOL.

There are two different classical partitioning methods **Row/column division** or **Block division**, 

### Row/column Division:
For example, we divide the entire `R * C` grid into `p` sub-grids along the column direction (assume that `p` divides `R`, or makes an approximate division). It seems like `p` vertical sections, which is a process with sub-grid size $`R * \frac{C}{p}`$ (it can also be divided by rows, with similar rules).

For each process, updating the boundary of the sub-grid only requires exchanging boundary columns with its left and right neighbours. This means that the total grid can be perfectly divided into `p` column sections (process). The leftmost and rightmost sections each send and receive `R` units to the other process, while the sub-grid between these two processes sends and receives `2 * R` units each. Therefore, in total, we need to send `2R * (p - 1)` unit size of the message and send `(p - 1) * 2` messages for each update step.

### Block Division: 
Another common method is to divide the grid into blocks. If `p` is a perfect square number, we can divide an `R * C` grid into `p` processes, while `p` can be decomposed into two integers `p_r`(the number of sub-grid in each row) and `p_c`(the number of sub-grid in each column), satisfying `p = p_r * p_c`. Each process is responsible for a sub-grid, whose size is approximately $`\frac{R}{p_c} * \frac{C}{p_r}`$.

Each process needs to exchange boundary data with up to 8 adjacent processes (horizontal boundary: above, and below sub-grids; vertical boundary: left and right sub-grids; and diagonal sub-grids), but for processes located on the global boundary requires less message send. 

- For vertical boundary:
The total number of vertical boundaries in each row of sub-grids is `p_c * (p_r - 1)`, since each vertical dividing line corresponds to two adjacent processes, requiring two-way communication, therefore requiring to send `2 * p_c * (p_r - 1)` message. Each time information is sent, it is the state of the sub-grid boundary cell. Therefore, the size of the information sent for each vertical boundary is $`\frac{R}{p_c}`$.

- For horizontal boundary:
For a similar reason, the number of messages sent will be `2 * p_r * (p_c - 1)`. The size of the information sent for each horizontal boundary is $`\frac{C}{p_r}`$. The message sent by the diagonal sub-grid is only 1 cell.

- For diagonal boundary:
Each sub-block may have 4 diagonal neighbours, and it is worth noting that edge blocks may have fewer. Calculate the number of diagonals in the two diagonal directions respectively, and get `2 * (p_r - 1) * (p_c - 1)`, the message sent will be double `4 * (p_r - 1) * (p_c - 1)`.

Thus the total number of message send is `2 * p_c * (p_r - 1) + 2 * p_r * (p_c - 1) + 4 * (p_r - 1) * (p_c - 1)`, while total send `2C * (p_c - 1) + 2R * (p_r - 1) + 4 * (p_r - 1) * (p_c - 1)`.

### Choice of Approach
When designing a distributed system, we need to reduce the frequency of message transmission and the size of messages as much as possible. To facilitate the comparison of the above two methods, assume that we apply them in a square grid (`N * N`). We can see that for the method of dividing by row/column, each process sends more data at a time (`~N`), but the number of messages required to be sent is less; for the method of dividing by block (split into `p` processes), each process sends less data at a time ($`~N/\sqrt{p}`$), but the number of messages required to be sent is more. Generally speaking, for a given amount of data, a smaller number of large messages is better than a large number of small messages, so I use the method of divide by row/column (this method is also simpler). More specifically, for this project I used row divide, which is more suitable for memory management.

## Part 4.5: Running the MPI application
This part will manually test the MPI application, more specifically, three cases are applied to check my code works normally. If the user is not using it on a large server, there may not be enough cores to support the strategy of mixing MPI and OpenMP. In this case, the author recommends setting `OMP_NUM_THREADS = 1` during actual implementation. I will provide the command line arguments and outputs below. 

### The glider.txt case:
To implement the `GolSimulatorMPI.cpp` for `glider.txt` as input and `generations = 26`, run the following code `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolSimulatorMPI -f ./test/data/glider.txt -g 26`. 

```
Start grid: 
- - - - - - - - - - 
- - o - - - - - - - 
o - o - - - - - - - 
- o o - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 

==============================
Final grid: 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - - - 
- - - - - - - - o - 
- - - - - - - - - o 
- - - - - - - o o o 
```

The above result is the same as the previous result in non-parallel application.

### The 7 * 7 random grid
To implement the `GolSimulatorMPI.cpp` for `7 * 7` random grid as an initial grid with `seed = 123` and `generations = 4`, run the following code `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolSimulatorMPI -r 7 7 15 -s 123 -g 4`. 

```
Start grid: 
o - o - o - - 
- - - o - o - 
o - o - - - - 
o o - - - o o 
- - - - - - o 
o - - - - o o 
- - - - - - - 

==============================
Final grid: 
- o o o - - - 
- - - - - - - 
- - o - o - - 
- - o o o - - 
- o o - - - - 
- - - - - - - 
- - - - - - - 
```

The above result is the same as the previous result in a non-parallel application.

### The p138-oscillator.txt case:
This case contains two application tests for `generations = 69` and `generations = 138`， which is half of the period of the oscillator and the full period of the oscillator, respectively.

- For Generation 69
To implement the `GolSimulatorMPI.cpp` for `p138-oscillator.txt` grid as input with `generations = 69`, run the following code `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolSimulatorMPI -f ./test/data/p138_oscillators.txt -g 69`. 

```
Start grid: 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - o - - - - - o o o - - - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - o o - o o - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - o - - o - - - - - - - - - o - - - - - - - - - - - 
- - - - - - - - - - o - o - - - - - - - - - o - o - - - - - - - - - - 
- - - - - - - - - - - o - - - - - - - - - o - - o - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - o o - o o - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - - - o o o - - - - - o - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

==============================
Final grid: 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - o o o - - - - - o - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - o o - o o - - - - - - - - - - 
- - - - - - - - - - - o - - - - - - - - - o - - o - - - - - - - - - - 
- - - - - - - - - - o - o - - - - - - - - - o - o - - - - - - - - - - 
- - - - - - - - - - o - - o - - - - - - - - - o - - - - - - - - - - - 
- - - - - - - - - - o o - o o - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - o - - - - - o o o - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
```

- For Generation 138
To implement the `GolSimulatorMPI.cpp` for `p138-oscillator.txt` grid as input with `generations = 138`, run the following code `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolSimulatorMPI -f ./test/data/p138_oscillators.txt -g 138`. 

```
Start grid: 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - o - - - - - o o o - - - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - o o - o o - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - o - - o - - - - - - - - - o - - - - - - - - - - - 
- - - - - - - - - - o - o - - - - - - - - - o - o - - - - - - - - - - 
- - - - - - - - - - - o - - - - - - - - - o - - o - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - o o - o o - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - - - o o o - - - - - o - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 

==============================
Final grid: 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - o - - - - - o o o - - - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - - - 
- - - - - - - - - - o o - o o - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - o - - o - - - - - - - - - o - - - - - - - - - - - 
- - - - - - - - - - o - o - - - - - - - - - o - o - - - - - - - - - - 
- - - - - - - - - - - o - - - - - - - - - o - - o - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - o o - o o - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - - - - o - - - - - - - - - - - - - 
- - - - - - - - - - - - - - o o o - - - - - o - - - - - - - - - - - - 
- - - - - - - - - - - - - o - - - o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o - - o - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - o o o - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
```

The above result verify that the resulting grid after 138 evolutions is equivalent to the input.

## Part 5.3: Running the app
This part evolves a series of `4 * 4` random grids and finds 5 still lifes grids as below. User can run the following code `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolStillLifeFinder -r 4 4 6 -g 10 -t 100 -n 5 -s 521`. The result is,

```
MPI Still lifes finder start with 4 processes...
Total unique still life found: 5
#1: Unique still life
- - - - 
- - - - 
- - - - 
- - - - 

==============================
#2: Unique still life
- - - - 
- - o - 
- o - o 
- - o o 

==============================
#3: Unique still life
- o o - 
o - - o 
- o o - 
- - - - 

==============================
#4: Unique still life
- - - - 
- - - - 
- o o - 
- o o - 

==============================
#5: Unique still life
- o o - 
o - o - 
- o - - 
- - - - 

==============================
```

Users can still increase the probability of successfully finding target still life by relaxing the 'search conditions', that is, increasing the values of `-g` and `-t` to find more still life. For example, users can use the following code to check more 4 by 4 still life grids if they want (OPTIONAL: Due to it being too lengthy, this document does not display the result), `cmake --build build/ && OMP_NUM_THREADS=1 mpirun -np 4 ./build/bin/GolStillLifeFinder -r 4 4 6 -g 200 -t 50000 -n 80 -s 521`.