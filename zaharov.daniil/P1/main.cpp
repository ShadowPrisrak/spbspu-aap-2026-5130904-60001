#include <iostream>
#include <cstddef>
#include <climits>

namespace zaharov
{

  bool safeSquare(long long val, long long& result)
  {
    if (val == 0 || val == 1 || val == -1)
    {
      result = val * val;
      return true;
    }

    if (val == LLONG_MIN)
    {
      return false;
    }

    const long long abs_val = (val < 0) ? -val : val;
    if (abs_val > LLONG_MAX / abs_val)
    {
      return false;
    }

    result = val * val;
    return true;
  }

  bool isPythagorean(long long a, long long b, long long c)
  {
    long long a2 = 0;
    long long b2 = 0;
    long long c2 = 0;

    if (!safeSquare(a, a2) || !safeSquare(b, b2) || !safeSquare(c, c2))
    {
      return false;
    }

    if (a2 > LLONG_MAX - b2)
    {
      return false;
    }

    return a2 + b2 == c2;
  }

  int run()
  {
    size_t max_equal = 1;
    size_t cur_equal = 1;
    size_t pyth_count = 0;
    size_t total_elements = 0;
    long long first = 0;
    long long second = 0;
    long long third = 0;
    long long prev = 0;
    long long cur = 0;

    while (std::cin >> cur && cur != 0)
    {
      ++total_elements;

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
      }

      first = second;
      second = third;
      third = cur;

      if (total_elements >= 3)
      {
        if (isPythagorean(first, second, third))
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

    if (total_elements == 0)
    {
      std::cout << 0 << '\n';
      std::cerr << "Error: cannot compute PTH-TRP characteristic\n";
      return 2;
    }

    if (total_elements < 3)
    {
      std::cout << max_equal << "\n";
      std::cerr << "Error: cannot compute PTH-TRP characteristic\n";
      return 2;
    }

    std::cout << pyth_count << "\n";
    std::cout << max_equal << '\n';
    return 0;
  }

}

int main()
{
  return zaharov::run();
}
