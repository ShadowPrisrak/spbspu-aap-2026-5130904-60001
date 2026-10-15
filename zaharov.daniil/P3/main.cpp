#include <iostream>
#include <cstdlib>
#include <fstream>

bool readMatrix()
{
  //todo
  return false;
}

void process()
{
  //todo
}

void writeMatrix()
{
  //todo
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

  return 0;
}


