#include <iostream>
#include <cstdlib>
#include <fstream>

const int maxElements = 10000;

bool readMatrix(std::ifstream &in, int *data, int &rows, int &cols)
{
  if (!(in >> rows >> cols))
  {
    return false;
  }

  if (rows < 0 || cols < 0)
  {
    return false;
  }

  if (rows * cols > maxElements)
  {
    return false;
  }

  const int total = rows * cols;
  for (int i = 0; i < total; ++i)
  {
    if (!(in >> data[i]))
    {
      return false;
    }
  }

  return true;
}

int findBestColumn(const int *data, int rows, int cols)
{
  int max_series = 0;
  int best_col = 0;

  for (int j = 0; j < cols; ++j)
  {
    int cur_series = 1;
    int col_max_series = 1;

    for (int i = 1; i < rows; ++i)
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

void process(int *data, int rows, int cols)
{
  int top = 0;
  int bottom = rows - 1;
  int left = 0;
  int right = cols - 1;
  int step = 1;

  while (top <= bottom && left <= right)
  {
    for (int i = bottom; i >= top; --i)
    {
      data[i * cols + left] -= step++;
    }
    ++left;

    if (top <= bottom)
    {
      for (int j = left; j <= right; ++j)
      {
        data[top * cols + j] -= step++;
      }
      ++top;
    }

    if (left <= right)
    {
      for (int i = top; i <= bottom; ++i)
      {
        data[i * cols + right] -= step++;
      }
      --right;
    }

    if (top <= bottom)
    {
      for (int j = right; j >= left; --j)
      {
        data[bottom * cols + j] -= step++;
      }
      --bottom;
    }
  }
}

void writeMatrix(std::ofstream &out, const int *data, int rows, int cols)
{
  out << rows << ' ' << cols << '\n';

  for (int i = 0; i < rows; ++i)
  {
    for (int j = 0; j < cols; ++j)
    {
      if (j > 0)
      {
        out << ' ';
      }
      out << data[i * cols + j];
    }
    out << '\n';
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
  const long parsed = std::strtol(argv[1], &end, 10);

  if (*end != '\0' || (parsed != 1 && parsed != 2))
  {
    std::cerr << "Error: first argument must be 1 or 2\n";
    return 1;
  }

  const int num = static_cast< int >(parsed);

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

  int rows = 0;
  int cols = 0;

  if (num == 1)
  {
    int data[maxElements];
    int original[maxElements];

    if (!readMatrix(in, data, rows, cols))
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }

    const int total = rows * cols;
    for (int i = 0; i < total; ++i)
    {
      original[i] = data[i];
    }

    process(data, rows, cols);
    writeMatrix(out, data, rows, cols);

    const int best_col = findBestColumn(original, rows, cols);
    out << best_col << '\n';
  }
  else
  {
    if (!(in >> rows >> cols))
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }

    if (rows < 0 || cols < 0 || rows * cols > maxElements)
    {
      std::cerr << "Error: cannot read matrix\n";
      return 2;
    }

    int *const data = new int[rows * cols];
    int *const original = new int[rows * cols];
    const int total = rows * cols;

    for (int i = 0; i < total; ++i)
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

    process(data, rows, cols);
    writeMatrix(out, data, rows, cols);

    const int best_col = findBestColumn(original, rows, cols);
    out << best_col << '\n';

    delete[] data;
    delete[] original;
  }

  return 0;
}
