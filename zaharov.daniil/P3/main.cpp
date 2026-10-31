#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstddef>
#include <memory>

namespace zaharov
{

  const int maxElements = 10000;

  std::istream &readMatrix(std::ifstream &in, int *data, size_t &rows, size_t &cols)
  {
    if (!(in >> rows >> cols))
    {
      return in;
    }

    if (rows * cols > maxElements)
    {
      return in;
    }

    const size_t total = rows * cols;
    for (size_t i = 0; i < total; ++i)
    {
      if (!(in >> data[i]))
      {
        return in;
      }
    }

    return in;
  }

  size_t findBestColumn(const int *data, size_t rows, size_t cols)
  {
    size_t max_series = 0;
    size_t best_col = 0;

    for (size_t j = 0; j < cols; ++j)
    {
      size_t cur_series = 1;
      size_t col_max_series = 1;

      for (size_t i = 1; i < rows; ++i)
      {
        if (data[i * cols + j] == data[(i - 1) * cols + j])
        {
          ++cur_series;
        }
        else
        {
          cur_series = 1;
        }

        if (cur_series > col_max_series)
        {
          col_max_series = cur_series;
        }
      }

      if (col_max_series > max_series)
      {
        max_series = col_max_series;
        best_col = j + 1;
      }
    }
    return best_col;
  }

  void applySpiralDecrease(int *data, size_t rows, size_t cols)
  {
    size_t top = 0;
    size_t bottom = rows - 1;
    size_t left = 0;
    size_t right = cols - 1;
    int step = 1;

    while (top <= bottom && left <= right)
    {
      for (size_t i = bottom; i >= top; --i)
      {
        data[i * cols + left] -= step++;
      }
      ++left;

      if (top <= bottom)
      {
        for (size_t j = left; j <= right; ++j)
        {
          data[top * cols + j] -= step++;
        }
        ++top;
      }

      if (left <= right)
      {
        for (size_t i = top; i <= bottom; ++i)
        {
          data[i * cols + right] -= step++;
        }
        --right;
      }

      if (top <= bottom)
      {
        for (size_t j = right; j >= left; --j)
        {
          data[bottom * cols + j] -= step++;
        }
        --bottom;
      }
    }
  }

  std::ostream &writeMatrix(std::ofstream &out, const int *data, size_t rows, size_t cols)
  {
    out << rows << ' ' << cols << '\n';

    for (size_t i = 0; i < rows; ++i)
    {
      for (size_t j = 0; j < cols; ++j)
      {
        out << data[i * cols + j];
        if (j + 1 < cols)
        {
          out << ' ';
        }
      }
      out << '\n';
    }
    return out;
  }

  int run(int argc, char *argv[])
  {
    if (argc != 4)
    {
      std::cerr << "Error: expected 3 arguments\n";
      return 1;
    }

    char *end = nullptr;
    const long parsed = std::strtol(argv[1], &end, 10);

    if (*end != '\0' || (parsed != 1 && parsed != 2))
    {
      std::cerr << "Error: first argument must be 1 or 2\n";
      return 1;
    }

    const size_t num = static_cast< size_t >(parsed);

    std::ifstream in(argv[2]);
    if (!in)
    {
      std::cerr << "Error: cannot open input file\n";
      return 2;
    }

    std::ofstream out(argv[3]);
    if (!out)
    {
      std::cerr << "Error: cannot open output file\n";
      return 2;
    }

    size_t rows = 0;
    size_t cols = 0;

    int *data = nullptr;
    int *original = nullptr;
    int stack_data[maxElements];
    int stack_original[maxElements];

    if (num == 1)
    {
      data = stack_data;
      original = stack_original;
    }
    else
    {
      if (!(in >> rows >> cols) || rows == 0 || cols == 0 || rows * cols > maxElements)
      {
        std::cerr << "Error: cannot read matrix\n";
        return 2;
      }

      data = new int[rows * cols];
      original = new int[rows * cols];

      const size_t total = rows * cols;
      for (size_t i = 0; i < total; ++i)
      {
        if (!(in >> data[i]))
        {
          delete[] data;
          delete[] original;
          std::cerr << "Error: cannot read matrix\n";
          return 2;
        }
        original[i] = data[i];
      }
    }

    if (num == 1)
    {
      if (!readMatrix(in, data, rows, cols))
      {
        std::cerr << "Error: cannot read matrix\n";
        return 2;
      }
      const size_t total = rows * cols;
      for (size_t i = 0; i < total; ++i)
      {
        original[i] = data[i];
      }
    }

    applySpiralDecrease(data, rows, cols);
    writeMatrix(out, data, rows, cols);

    const size_t best_col = findBestColumn(original, rows, cols);
    out << best_col << '\n';

    if (num == 2)
    {
      delete[] data;
      delete[] original;
    }

    return 0;
  }

}

int main(int argc, char *argv[])
{
  return zaharov::run(argc, argv);
}
