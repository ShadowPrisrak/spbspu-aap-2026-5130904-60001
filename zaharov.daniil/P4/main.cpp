#include <iostream>
#include <cstddef>
#include <cstring>

namespace zaharov
{
  const int ascii_size = 256;
  const size_t initial_capacity = 100;

  char *removeLatinLetters(const char *src, char *dest)
  {
    size_t j = 0;
    for (size_t i = 0; src[i] != '\0'; ++i)
    {
      const char c = src[i];
      const bool isLatin = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');

      if (!isLatin)
      {
        dest[j] = c;
        ++j;
      }
    }
    dest[j] = '\0';
    return dest;
  }

  int hasRepeatingChars(const char *str)
  {
    int counts[ascii_size] = {0};
    for (size_t i = 0; str[i] != '\0'; ++i)
    {
      const unsigned char c = static_cast< unsigned char >(str[i]);
      counts[c]++;
      if (counts[c] > 1)
      {
        return 1;
      }
    }
    return 0;
  }
}

int main()
{
  size_t capacity = zaharov::initial_capacity;
  size_t size = 0;
  char *buffer = new char[capacity];

  char c = 0;

  while (std::cin.get(c))
  {
    if (c == '\n')
    {
      break;
    }

    if (size + 1 >= capacity)
    {
      capacity *= 2;
      char *const new_buffer = new char[capacity];
      for (size_t i = 0; i < size; ++i)
      {
        new_buffer[i] = buffer[i];
      }
      delete[] buffer;
      buffer = new_buffer;
    }
    buffer[size] = c;
    ++size;
  }
  buffer[size] = '\0';

  if (size == 0 && std::cin.eof())
  {
    delete[] buffer;
    std::cerr << "Error: empty input\n";
    return 1;
  }

  char *const res = new char[size + 1];

  zaharov::removeLatinLetters(buffer, res);
  std::cout << res << '\n';

  const int hasRep = zaharov::hasRepeatingChars(buffer);
  std::cout << hasRep << '\n';

  delete[] buffer;
  delete[] res;

  return 0;
}
