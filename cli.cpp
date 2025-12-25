#include <iostream>

void hi()
{
  std::cout << "HI!\n";
}

std::istream& getword(std::istream& is, char* word, size_t k, bool(*c)(char))
{

}

bool is_space(char c)
{
  return std::isspace(c);
}

size_t match(const char* word, const char* const* words, size_t k)
{

}

int main()
{
  constexpr size_t cmds_count = 1;
  void(*cmds[1])() = {hi};
  const char* const cmds_text[] = {"hi"};
  constexpr size_t b_size = 255;
  char word[b_size + 1] = {};
  size_t i = 0;
  while (!(getword(std::cin, word, b_size, is_space).eof()))
  {
    if (std::cin.fail())
    {
      std::cerr << "INVALID COMMAND\n";
      return 1;
    }
    else if (size_t i = match(word, cmds_text, cmds_count); i < cmds_count)
    {
      cmds[i]();
    }
    else
    {
      std::cerr << "UNKNOWN COMMAND\n";
    }
  }
}