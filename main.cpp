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

  void make_f(IDraw ** b, size_t &k)
  {
    b[0] = new Dot(0, 0);
    b[1] = new Dot(-2, -5);
    b[2] = new Dot(3, 7);
    k = 3;
  }

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

  struct VSeg;
  struct HSeg;
}

int main()
{
  int err = 0;
  using namespace top;
  IDraw * f[3] = {};
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