#include <iostream>
#include <cstdlib>
#include <fstream>

const int MAX_ELEMENTS = 10000;

bool readMatrix(std::ifstream &in, int *data, int &rows, int &cols)
{
  if (!(in >> rows >> cols)) {
    return false;
  }

  if (rows <= 0 || cols <= 0) {
    return false;
  }

  if (rows * cols > MAX_ELEMENTS) {
    return false;
  }

  int total = rows * cols;
  for (int i = 0; i<total; ++i) {
    if (!(in >> data[i])) {
      return false;
    }
  }

  return true;
}

void process(int *data, int rows, int cols)
{
  //todo
  (void)data;
  (void)rows;
  (void)cols;
}

void writeMatrix(std::ofstream &out, int *data, int rows, int cols)
{
  out << rows << '' << cols << '\n';

  for (int i = 0; i<rows; ++i) {
    for (int j = 0; j<cols; ++j) {
      if (j>0) {
        out << '';
      }
      out << data[i * cols + j];
    }
    out << '\n';
  }
}

int main(int argc, char *argv[])
{
  (void)argv; //todo

  if (argc != 4) {
    std:cerr << "Error: expected 3 arguments\n";
    return 1;
  }

  char *end = nullptr;
  long parsed = std::strtol(argv[1], &end, 10);

  if (*end != '\0' || (parsed != 1 && parsed !=2)) {
    std:cerr << "Error: first argument must be 1 or 2\n";
    return 1;
  }

  int num = static_cast<int>(parsed);
  (void)num; //todo

  std::ifstream in(argv[2]);
  if (!in) {
    std::cerr << "Error: cannot open input file\n";
    return 2;
  }

  std::ofstream out(argv[3]);
  if (!out) {
    std:cerr << "Error: cannot open output file\n";
    return 2;
  }

  int data[MAX_ELEMENTS];
  int rows = 0;
  int cols = 0;

  if (!readMatrix(in, data, rows, cols)) {
    std::cerr << "Error: cannot read matrix\n";
    return 2;
  }

  process(data, rows, cols);
  writeMatrix(out, data, rows, cols);

  return 0;
}


