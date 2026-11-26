#include "rectangle.hpp"
#include <stdexcept>

namespace zaharov
{
  Rectangle::Rectangle(double width, double height, p_t pos):
    width_(width),
    height_(height),
    pos_(pos)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Width and height must be positive");
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rec_t Rectangle::getFrameRect() const
  {
    return {width_, height_, pos_};
  }

  void Rectangle::move(p_t p)
  {
    pos_ = p;
  }

  void Rectangle::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }

  void Rectangle::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    width_ *= k;
    height_ *= k;
  }
}
