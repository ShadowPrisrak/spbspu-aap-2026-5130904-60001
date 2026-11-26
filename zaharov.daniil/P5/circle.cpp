#include "circle.hpp"
#include <stdexcept>

namespace zaharov
{
  Circle::Circle(double radius, p_t pos):
    radius_(radius),
    pos_(pos)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Radius must be positive");
    }
  }

  double Circle::getArea() const
  {
    const double pi = 3.14;
    return pi * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return {radius_ * 2.0, radius_ * 2.0, pos_};
  }

  void Circle::move(p_t p)
  {
    pos_ = p;
  }

  void Circle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Circle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    radius_ *= k;
  }
}
