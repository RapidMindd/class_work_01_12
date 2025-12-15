#ifndef GEOM_HPP
#define GEOM_HPP
#include <cstddef>

namespace top
{
  struct p_t
  {
    int x, y;
  };
  bool operator==(p_t a, p_t b);
  bool operator!=(p_t a, p_t b);
  struct frame_t
  {
    p_t aa, bb;
  };
  size_t rows(frame_t fr);
  size_t cols(frame_t fr);
  frame_t build_frame(const p_t * pts, size_t s);
}
#endif