#include <iostream>

namespace top
{
  struct p_t
  {
    int x, y;
  };

 bool operator==(p_t a, p_t b)
{
  return a.x == b.x && a.y == b.y;
}

bool operator!=(p_t a, p_t b)
{
  return !(a == b);
}

  struct IDraw
  {
    virtual p_t begin() const = 0;
    virtual p_t next(p_t) const = 0;
    virtual ~IDraw() = default;
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

  struct frame_t
  {
    p_t aa;
    p_t bb;
  };

  void extend(p_t ** pts, size_t s, p_t p)
  {
    p_t * res = new p_t [s + 1];
    for (size_t i = 0; i < s; ++i)
    {
      res[i] = (*pts)[i];
    }
    res[s] = p;
    delete [] *pts;
    *pts = res;
  }

  void get_points(const IDraw & b, p_t ** pts, size_t & s)
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
  frame_t build_frame(const p_t * pts, size_t s)
  {
    if (!s)
    {
      throw std::logic_error("bad_size");
    }
    int minx = pts[0].x, maxx = minx;
    int miny = pts[0].y, maxy = miny;
    for (size_t i = 1; i < s; ++i)
    {
      minx = std::min(minx, pts[i].x);
      maxx = std::max(maxx, pts[i].x);
      miny = std::min(miny, pts[i].y);
      maxy = std::max(maxy, pts[i].y);
    }
    p_t aa{minx, miny};
    p_t bb{maxx, maxy};
    return {aa, bb};
    // min/max x,y -> frame_t
  }

  size_t rows(frame_t fr)
  {
    return (fr.bb.y - fr.aa.y + 1);
  }

  size_t cols(frame_t fr)
  {
    return (fr.bb.x - fr.aa.x + 1);
  }

  char * build_canvas(frame_t fr, char fill)
  {
    char * cnv = new char[rows(fr) * cols(fr)];
    for (size_t i = 0; i < rows(fr) * cols(fr); ++i)
    {
      cnv[i] = fill;
    }
    return cnv;
    // посчитать на основе фрейм, сколько строк и столбцов будет на экране
    // из макс вычесть мин и добавить 1
  }
  void paint_canvas(char * cnv, frame_t fr, p_t p, char fill)
  {
    int dx = p.x - fr.aa.x;
    int dy = fr.bb.y - p.y;
    cnv[dy * cols(fr) + dx] = fill;
    // что-то сделать с координатами (инвертировать, привести к правильному виду)
  }
  void print_canvas(std::ostream & os, const char * cnv, frame_t fr)
  {
    for (size_t i = 0; i < rows(fr); ++i)
    {
      for (size_t j = 0; j < cols(fr); ++j)
      {
        os << cnv[i * cols(fr) + j];
      }
      os << '\n';
    }
    // не выводить лишний пробел!
  }

  struct VSeg:IDraw
  {
    VSeg(p_t start, size_t length);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t start;
    size_t length;
  };
  struct HSeg:IDraw
  {
    HSeg(p_t start, size_t length);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t start;
    size_t length;
  };

  struct InclinedSeg:IDraw
  {
    InclinedSeg(p_t start, size_t length);
    p_t begin() const override;
    p_t next(p_t) const override;
    p_t start;
    size_t length;
  };

  top::InclinedSeg::InclinedSeg(p_t s, size_t len):
    IDraw(),
    start{s.x, s.y},
    length(len)
  {
    if (!len)
    {
      throw std::invalid_argument("length must be positive");
    }
  }

  top::p_t top::InclinedSeg::begin() const
  {
    return start;
  }

  top::p_t top::InclinedSeg::next(p_t point) const
  {
    if (point.x == start.x + (length - 1))
    {
      return begin();
    }
    return p_t{point.x + 1, point.y + 1};
  }

  top::VSeg::VSeg(p_t s, size_t len):
    IDraw(),
    start{s.x, s.y},
    length(len)
  {
    if (!len)
    {
      throw std::invalid_argument("length must be positive");
    }
  }

  top::p_t top::VSeg::begin() const
  {
    return start;
  }

  top::p_t top::VSeg::next(p_t point) const
  {
    if (point.y == start.y + (length - 1))
    {
      return begin();
    }
    return p_t{start.x, point.y + 1};
  }

  top::HSeg::HSeg(p_t s, size_t len):
    IDraw(),
    start{s.x, s.y},
    length(len)
  {
    if (!len)
    {
      throw std::invalid_argument("length must be positive");
    }
  }

  top::p_t top::HSeg::begin() const
  {
    return start;
  }

  top::p_t top::HSeg::next(p_t point) const
  {
    if (point.x == start.x + (length - 1))
    {
      return begin();
    }
    return p_t{point.x + 1, start.y};
  }

  p_t next_point_in_rec(p_t point, frame_t frame)
  {
    if (point.x == frame.aa.x && point.y < frame.bb.y)
    {
      return {point.x, point.y + 1};
    }
    if (point.y == frame.bb.y && point.x < frame.bb.x)
    {
      return {point.x + 1, point.y};
    }
    if (point.x == frame.bb.x && point.y > frame.aa.y)
    {
      return {point.x, point.y - 1};
    }
    if (point.y == frame.aa.y && point.x > frame.aa.x)
    {
      return {point.x - 1, point.y};
    }
    return frame.aa;
  }

  struct Rectangle:IDraw
  {
    Rectangle(p_t start, size_t width, size_t height);
    p_t begin() const override;
    p_t next(p_t) const override;
    frame_t frame;
  };

  top::Rectangle::Rectangle(p_t start, size_t width, size_t height):
    IDraw(),
    frame({start, {static_cast<int>(start.x + (width - 1)), static_cast<int>(start.y + (height - 1))}})
  {
  }

  top::p_t top::Rectangle::begin() const
  {
    return frame.aa;
  }

  top::p_t top::Rectangle::next(p_t point) const
  {
    return next_point_in_rec(point, frame);
  }

  struct Square:IDraw
  {
    Square(p_t start, size_t size);
    p_t begin() const override;
    p_t next(p_t) const override;
    frame_t frame;
  };

  top::Square::Square(p_t start, size_t size):
    IDraw(),
    frame({start, {static_cast<int>(start.x + (size - 1)), static_cast<int>(start.y + (size - 1))}})
  {
  }

  top::p_t top::Square::begin() const
  {
    return frame.aa;
  }

  top::p_t top::Square::next(p_t point) const
  {
    return next_point_in_rec(point, frame);
  }

  void make_f(IDraw ** b, size_t &k)
  {
    b[0] = new Dot(0, 0);
    b[1] = new Dot(-2, -5);
    b[2] = new Dot(7, 7);
    b[3] = new VSeg({2, 1}, 5);
    b[4] = new HSeg({3, 0}, 9);
    b[5] = new InclinedSeg({2, 0}, 5);
    b[6] = new Rectangle({0, -3}, 4, 3);
    b[7] = new Square({20, 3}, 3);
    k = 8;
  }
}

int main()
{
  int err = 0;
  using namespace top;
  IDraw * f[8] = {};
  p_t * p = nullptr;
  size_t s = 0;
  char * cnv = nullptr;
  try
  {
    size_t size = 0;
    make_f(f, size);
    for (size_t i = 0; i < size; ++i)
    {
      get_points(*f[i], &p, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr, '.');
    for (size_t i = 0; i < s; ++i)
    {
      paint_canvas(cnv, fr, p[i], '#');
    }
    paint_canvas(cnv, fr, *p, '#');
    print_canvas(std::cout, cnv, fr);
  }
  catch(...)
  {
    err = 1;
  }
  for (size_t i = 0; i < 3; ++i)
  {
    delete f[i];
  }
  delete[] p;
  delete[] cnv;
  return err;
}