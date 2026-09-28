#include "GolGrid.h"
#include <fstream>

using std::size_t;
using std::vector;

namespace gol
{
// Constructor initialised all cells to dead
Grid::Grid(size_t rows, size_t cols) : row_num(rows), col_num(cols), data(new bool[rows * cols])
{
    std::fill(data, data + row_num * col_num, false);
}

// Constructor initialised the grid by random
Grid::Grid(size_t rows, size_t cols, size_t aliveCount, std::mt19937& rng) : row_num(rows), col_num(cols), data(new bool[rows * cols])
{
    if (aliveCount > rows * cols)
    {
        throw std::invalid_argument("ERROR! The alive cell setted is larger than the total number of cells.");
    }

    std::fill(data, data + row_num * col_num, false);

    // Generate random alive cells
    std::uniform_int_distribution<size_t> dist(0, rows * cols - 1);
    vector<size_t> indices(row_num * col_num);
    std::iota(indices.begin(), indices.end(), 0);
    std::shuffle(indices.begin(), indices.end(), rng);

    for (size_t i = 0; i < aliveCount; i++)
    {
        size_t index = indices[i];
        data[index] = true;
    }
}

// Constructor initialised the grid with given input
Grid::Grid(const std::string& filepath)
{
    std::fstream file;
    file.open(filepath, std::ios::in);

    if (!file.is_open())
    {
        throw std::runtime_error("ERROR! The file " + filepath + " is not open.");
    }

    vector<vector<bool>> temp_data;
    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }
        // Tokenise the line
        std::vector<std::string> tokens;
        size_t pos = 0;
        size_t next = 0;
        do
        {
            next = line.find(' ', pos);
            std::string token = line.substr(pos, next - pos);
            if (!token.empty())
            {
                tokens.push_back(token);
            }
            pos = next + 1;
        } while (next != std::string::npos);

        std::vector<bool> row_data;
        for (const auto& token : tokens)
        {
            if (token.size() != 1)
            {
                throw std::runtime_error("ERROR! Invalid token is given: " + token);
            }
            char c = token[0];
            if (c == 'o')
            {
                row_data.push_back(true);
            }
            else if (c == '-')
            {
                row_data.push_back(false);
            }
            else
            {
                throw std::runtime_error("ERROR! Unexpected character is given: " + std::string(1, c));
            }
        }
        if (!row_data.empty())
        {
            temp_data.push_back(std::move(row_data));
        }
    }
    file.close();

    // Check file format correct
    if (temp_data.empty())
    {
        throw std::runtime_error("ERROR! File is empty or in invalid format: " + filepath);
    }
    size_t temp_cols = temp_data.front().size();
    for (const auto& row : temp_data)
    {
        if (row.size() != temp_cols)
        {
            throw std::runtime_error("ERROR! Inconsistent row lengths in file: " + filepath);
        }
    }

    // Set the grid data
    row_num = temp_data.size();
    col_num = temp_cols;
    data = new bool[row_num * col_num];

    size_t idx = 0;
    for (const auto& row : temp_data)
    {
        for (bool cell : row)
        {
            data[idx++] = cell;
        }
    }
}

Grid::~Grid()
{
    if (!data)
        return;
    delete[] data;
}

Grid::Grid(const Grid& other) : row_num(other.row_num), col_num(other.col_num)
{
    data = new bool[row_num * col_num];
    for (int i = 0; i < row_num * col_num; i++)
    {
        data[i] = other.data[i];
    }
}

Grid& Grid::operator=(const Grid& other)
{
    delete[] data;

    row_num = other.row_num;
    col_num = other.col_num;

    size_t total = row_num * col_num;

    data = new bool[total];
    for (size_t i = 0; i < total; i++)
    {
        data[i] = other.data[i];
    }
    return *this;
}

size_t Grid::getRows() const
{
    return row_num;
}

size_t Grid::getCols() const
{
    return col_num;
}

void Grid::setCell(size_t row, size_t col, bool alive)
{
    if (row >= row_num || col >= col_num)
    {
        throw std::out_of_range("ERROR! The index of cell is out of range.");
    }
    data[index(row, col)] = alive;
}

bool Grid::getCell(size_t row, size_t col) const
{
    if (row >= row_num || col >= col_num)
    {
        throw std::out_of_range("ERROR! The index of cell is out of range.");
    }
    return data[index(row, col)];
}

size_t Grid::countAlive() const
{
    size_t count = 0;
    for (size_t i = 0; i < row_num * col_num; i++)
    {
        if (data[i])
        {
            count++;
        }
    }
    return count;
}

bool Grid::checkEquivalence(const Grid& other_grid) const
{
    if (row_num != other_grid.row_num || col_num != other_grid.col_num)
    {
        return false;
    }

    for (size_t i = 0; i < row_num * col_num; i++)
    {
        if (data[i] != other_grid.data[i])
        {
            return false;
        }
    }
    return true;
}

void Grid::print(std::ostream& os) const
{
    for (size_t i = 0; i < row_num; i++)
    {
        for (size_t j = 0; j < col_num; j++)
        {
            os << (getCell(i, j) ? 'o' : '-') << ' ';
        }
        os << "\n";
    }
    os << std::endl;
}

size_t Grid::index(size_t row, size_t col) const
{
    return row * col_num + col;
}

size_t Grid::getNeighboursAlive(size_t row, size_t col) const
{
    if (row >= row_num || col >= col_num)
    {
        throw std::out_of_range("ERROR! The cell index is out of range.");
    }

    size_t count = 0;
    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            if (i == 0 && j == 0)
            {
                continue;
            }

            int new_row = row + i;
            int new_col = col + j;

            // Check the index within the grid and count the alive cells
            if (new_row >= 0 && new_row < row_num && new_col >= 0 && new_col < col_num)
            {
                if (getCell(new_row, new_col))
                {
                    count++;
                }
            }
        }
    }
    return count;
}
} // namespace gol
