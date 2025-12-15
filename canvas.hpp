#ifndef CANVAS_HPP
#define CANVAS_HPP
#include <iosfwd>
#include "geom.hpp"
namespace top
{
  char * build_canvas(frame_t fr, char fill);
  void paint_canvas(char * cnv, frame_t fr, p_t p, char fill);
  void print_canvas(std::ostream & os, const char * cnv, frame_t fr);
}
#endif