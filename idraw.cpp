#include "idraw.hpp"
#include <cstddef>

void extend(top::p_t ** pts, size_t s, top::p_t p)
  {
    using namespace top;
    p_t * res = new p_t [s + 1];
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*pts)[i];
    }
    res[s] = p;
    delete [] *pts;
    *pts = res;
  }

void top::get_points(const IDraw & b, p_t ** pts, size_t & s)
  {
    p_t p = b.begin();
    extend(pts, s, p);
    size_t delta = 1;
    while (b.next(p) != b.begin())
    {
      p = b.next(p);
      extend(pts, s + delta, p);
      ++delta;
    }
    s = s + delta;
    // достать точки
    // обновить массив
    // размер!
  }