#ifndef IDRAW_HPP
#define IDRAW_HPP
#include "geom.hpp"
namespace top
{
  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
    virtual ~IDraw() = default;
  };
  void get_points(const IDraw & b, p_t ** pts, size_t & s);
}
#endif