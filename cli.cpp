#include <iostream>

void hi()
{
  std::cout << "HI!\n";
}

int main()
{
  size_t i = 0;
  while (!(std::cin >> i).eof())
  {
    if (std::cin.fail())
    {
      std::cerr << "UNKNOWN COMMAND\n";
      return 1;
    }
    else if (i == 0)
    {
      hi();
    }
    else
    {
      std::cerr << "INVALID COMMAND\n";
    }
  }
}