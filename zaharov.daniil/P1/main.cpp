#include <iostream>

int main()
{
  int prev = 0;
  if (!(std::cin >> prev))
  {
    if (std::cin.eof())
    {
      std::cerr << "Error: cannot compute characteristic\n";
      return 2;
    }

    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }

  if (prev == 0)
  {
    std::cout << 0 << '\n';
    std::cerr << "Error: cannot compute PTH-TRP characteristic\n";
    return 2;
  }

  int max_equal = 1;
  int cur_equal = 1;
  int first = prev;
  int second = 0;
  int third = 0;
  int have = 1;
  int pyth_count = 0;
  int cur = 0;
  while (std::cin >> cur)
  {
    if (cur == 0)
    {
      break;
    }

    if (cur == prev)
    {
      ++cur_equal;
      if (cur_equal > max_equal)
      {
        max_equal = cur_equal;
      }
    }
    else
    {
      cur_equal = 1;
      if (cur_equal > max_equal)
      {
        max_equal = cur_equal;
      }
    }

    if (have == 1)
    {
      second = cur;
      have = 2;
    }
    else if (have == 2)
    {
      third = cur;
      have = 3;

      if (first * first + second * second == third * third)
      {
        ++pyth_count;
      }
    }
    else if (have >= 3)
    {
      first = second;
      second = third;
      third = cur;

      if (first * first + second * second == third * third)
      {
        ++pyth_count;
      }
    }

    prev = cur;
  }

  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Error: input is not a sequence\n";
    return 1;
  }

  if (have < 3)
  {
    std::cout << max_equal << "\n";
    std::cerr << "Error: cannot compute PTH-TRP characteristic\n";
    return 2;
  }

  std::cout << pyth_count << "\n";
  std::cout << max_equal << '\n';
  return 0;
}
