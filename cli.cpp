#include <cctype>
#include <iostream>
#include <iomanip>
#include <cassert>

void hi(std::istream& is)
{
  unsigned int i = 0;
  is >> i;
  if (!is)
  {
    throw std::runtime_error("hi excpects unsigned int in param");
  }
  std::cout << "HI!\n";
}

void hello(std::istream&)
{
  std::cout << "Hello!\n";
}

std::istream& getword(std::istream& is, char* word, size_t k, size_t& size, bool(*c)(char))
{
  assert(k > 0 && "k must be greater than 0");
  if (!k || !word)
  {
    throw std::logic_error("bad buffer");
  }
  is >> std::noskipws;
  size_t i = 0;
  for (char next = 0; is && !c(next) && (i < k - 1); ++i)
  {
    is >> next;
    word[i] = next;
  }
  if (i == k)
  {
    is.clear(is.rdstate() | std::ios::failbit);
  }
  size = i;
  word[k] = '\0';
  return is >> std::skipws;
}

bool is_space(char c)
{
  return std::isspace(c);
}

size_t match(const char* word, const char* const* words, size_t k)
{
  for (size_t i = 0; i < k; ++i)
  {
    bool matching = std::strlen(word) == std::strlen(words[i]);
    matching = matching && std::strcmp(word, words[i]);
    if (matching)
    {
      return i;
    }
  }
  return k;
}

struct Cmd
{
  virtual const char * name() const = 0;
  virtual const char * help() const = 0;
  virtual const char * desc() const = 0;
  virtual void invoke() const = 0;
};

int main()
{
  constexpr size_t cmds_count = 2;
  using cmd_t = void(*)(std::istream&);
  cmd_t cmds[cmds_count] = {hi, hello};
  const char* const cmds_text[] = {"hi", "hello"};
  constexpr size_t b_capacity = 255;
  char word[b_capacity + 1] = {};
  size_t size = 0;
  while (!(getword(std::cin, word, b_capacity, size, is_space).eof()))
  {
    if (std::cin.fail())
    {
      std::cerr << "INVALID COMMAND\n";
      return 1;
    }
    else
    {
      word[size-1] = '\0';
      if (size_t i = match(word, cmds_text, cmds_count); i < cmds_count)
      {
        try
        {
          cmds[i](std::cin);
        }
        catch (const std::exception &e)
        {
          std::cerr << "INVALID COMMAND: " << e.what() << "\n";
          if (std::cin.fail())
          {
            std::cin.clear(std::cin.rdstate() ^ std::ios::failbit);
          }
          using lim_t = std::numeric_limits<std::streamsize>;
          std::cin.ignore(lim_t::max(), '\n');
        }
      }
      else
      {
        std::cerr << "UNKNOWN COMMAND\n";
      }
    }
  }
}