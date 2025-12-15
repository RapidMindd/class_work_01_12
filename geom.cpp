#include "geom.hpp"

bool top::operator==(p_t a, p_t b)
  {
    return a.x == b.x && a.y == b.y;
  }

bool top::operator!=(p_t a, p_t b)
  {
    return !(a == b);
  }
size_t top::rows(frame_t fr)
  {
    return (fr.bb.y - fr.aa.y + 1);
  }

size_t top::cols(frame_t fr)
  {
    return (fr.bb.x - fr.aa.x + 1);
  }
