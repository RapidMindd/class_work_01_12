#include <iostream>

namespace top
{
  struct p_t
  {
    int x, y;
  };

  bool operator!=(p_t a, p_t b)
  {
    return a.x != b.x || a.y || b.y;
  }

  bool operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
  };

  struct Dot:IDraw
  {
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t o;
    Dot(int x, int y);

  };

  top::Dot::Dot(int x, int y):
    IDraw(),
    o{x, y}
  {}

  top::p_t top::Dot::begin() const 
  {
    return o;
  }

  top::p_t top::Dot::next(p_t) const
  {
    return begin();
  }

  size_t count(IDraw & d)
  {
    size_t k = 0;
    p_t p = d.begin();
    while(d.next(p) == d.begin())
    {
      k++;
      p = d.next(p);
    }
    return k;
  }
}

int main()
{
  using namespace top;
}