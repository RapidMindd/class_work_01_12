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
    p_t left_bot;
    p_t right_top;
  };

  void make_f(IDraw ** b, size_t k)
  {
    b[0] = new Dot(0, 0);
    b[1] = new Dot(-1, -5);
    b[2] = new Dot(1, 7);
  }
  void get_points(IDraw * b, p_t ** ps, size_t & s)
  {
    p_t a = b->begin();
    // достать точки
    // обновить массив
    // размер!
  }
  frame_t build_frame(const p_t * ps, size_t s)
  {
    // min/max x,y -> frame_t
  }
  char * build_canvas(frame_t f)
  {
    // посчитать на основе фрейм, сколько строк и столбцов будет на экране
    // из макс вычесть мин и добавить 1
  }
  void paint_canvas(char * cnv, frame_t fr, const p_t * ps, size_t k, char f)
  {
    // что-то сделать с координатами (инвертировать, привести к правильному виду)
  }
  void print_canvas(const char * cnv, frame_t fr)
  {
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
    make_f(f, 3);
    for (size_t i = 0; i < 3; ++i)
    {
      get_points(f[i], &p, s);
    }
    frame_t fr = build_frame(p, s);
    cnv = build_canvas(fr);
    paint_canvas(cnv, fr, p, s, '#');
    print_canvas(cnv, fr);
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