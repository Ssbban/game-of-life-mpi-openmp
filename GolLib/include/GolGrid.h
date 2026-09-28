#ifndef golGrid_h
#define golGrid_h
#include <algorithm>
#include <iostream>
#include <memory>
#include <random>

using std::size_t;

namespace gol
{
class Grid
{
public:
    /**
     * @brief The constructor of Grid without random alive cells
     * @param rows
     * @param cols
     */
    Grid(size_t rows, size_t cols);

    /**
     * @brief The constructor of Grid with random alive cells
     * @param rows: The rows of the grid
     * @param cols: The columns of the grid
     * @param aliveCount: The number of alive cells
     * @param rng: The random number generator
     */
    Grid(size_t rows, size_t cols, size_t aliveCount, std::mt19937& rng);

    /**
     * @brief The constructor of Grid with given input
     * @param filename: The filename of the input file
     */
    Grid(const std::string& filepath);

    ~Grid();

    Grid(const Grid& other);
    Grid& operator=(const Grid& other);

    size_t getRows() const;
    size_t getCols() const;

    void setCell(size_t row, size_t col, bool alive);
    bool getCell(size_t row, size_t col) const;

    size_t countAlive() const;
    bool checkEquivalence(const Grid& other_grid) const;
    void print(std::ostream& os = std::cout) const;

    size_t getNeighboursAlive(size_t row, size_t col) const;

private:
    size_t row_num;
    size_t col_num;
    bool* data;

    size_t index(size_t row, size_t col) const;
};

} // namespace gol

#endif
