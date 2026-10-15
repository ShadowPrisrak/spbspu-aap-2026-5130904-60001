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
  //todo
  (void)argv;

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

  return 0;
}


