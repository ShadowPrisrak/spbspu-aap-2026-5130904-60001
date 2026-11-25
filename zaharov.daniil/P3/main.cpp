#include <iostream>
#include <fstream>
#include <cstdlib>
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
    if (rows > maxElements || cols > maxElements || rows * cols > maxElements)
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
    if (rows == 0 || cols == 0)
    {
      return;
    }
    int top = 0;
    int bottom = static_cast< int >(rows) - 1;
    int left = 0;
    int right = static_cast< int >(cols) - 1;
    int step = 1;

    while (top <= bottom && left <= right)
    {
      for (int i = bottom; i >= top; --i)
      {
        data[i * static_cast< int >(cols) + left] -= step++;
      }
      ++left;
      if (top <= bottom)
      {
        for (int j = left; j <= right; ++j)
        {
          data[top * static_cast< int >(cols) + j] -= step++;
        }
        ++top;
      }
      if (left <= right)
      {
        for (int i = top; i <= bottom; ++i)
        {
          data[i * static_cast< int >(cols) + right] -= step++;
        }
        --right;
      }
      if (top <= bottom)
      {
        for (int j = right; j >= left; --j)
        {
          data[bottom * static_cast< int >(cols) + j] -= step++;
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
        if (j > 0)
        {
          out << ' ';
        }
        out << data[i * cols + j];
      }
      out << '\n';
    }
    return out;
  }

}

int main(int argc, char *argv[])
{
  if (argc != 4)
  {
    std::cerr << "Error: expected 3 arguments\n";
    return 1;
  }

  char *end = nullptr;
  long parsed = 0;
  parsed = std::strtol(argv[1], std::addressof(end), 10);

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
  int stack_data[zaharov::maxElements];
  int stack_original[zaharov::maxElements];

  if (num == 1)
  {
    data = stack_data;
    original = stack_original;
    if (!zaharov::readMatrix(in, data, rows, cols))
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }
  }
  else
  {
    if (!(in >> rows >> cols))
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }
    if (rows > zaharov::maxElements || cols > zaharov::maxElements || rows * cols > zaharov::maxElements)
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
    }
  }

  const size_t total = rows * cols;
  for (size_t i = 0; i < total; ++i)
  {
    original[i] = data[i];
  }

  zaharov::applySpiralDecrease(data, rows, cols);
  zaharov::writeMatrix(out, data, rows, cols);
  out << zaharov::findBestColumn(original, rows, cols) << '\n';

  if (num == 2)
  {
    delete[] data;
    delete[] original;
  }

  return 0;
}
