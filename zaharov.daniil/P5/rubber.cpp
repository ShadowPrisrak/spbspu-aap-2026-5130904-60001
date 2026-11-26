#include "rubber.hpp"
#include <stdexcept>
#include <algorithm>

namespace zaharov
{
  Rubber::Rubber(double small_radius, double big_radius, p_t pos, p_t big_pos):
    small_radius_(small_radius),
    big_radius_(big_radius),
    pos_(pos),
    big_pos_(big_pos)
  {
    if (small_radius <= 0 || big_radius <= 0)
    {
      throw std::invalid_argument("Radius must be positive");
    }

    const double dist_sqr = (big_pos_.x - pos_.x) * (big_pos_.x - pos_.x) +
                            (big_pos_.y - pos_.y) * (big_pos_.y - pos_.y);
    const double r_diff = big_radius_ - small_radius_;
    if (r_diff <= 0 || dist_sqr >= r_diff * r_diff)
    {
      throw std::invalid_argument("Small circle must be inside big circle");
    }
  }

  double Rubber::getArea() const
  {
    const double pi = 3.14;
    return pi * (big_radius_ * big_radius_ - small_radius_ * small_radius_);
  }

  rec_t Rubber::getFrameRect() const
  {
    double min_x = pos_.x - small_radius_;
    double max_x = pos_.x + small_radius_;
    double min_y = pos_.y - small_radius_;
    double max_y = pos_.y + small_radius_;

    min_x = std::min(min_x, big_pos_.x - big_radius_);
    max_x = std::max(max_x, big_pos_.x + big_radius_);
    min_y = std::min(min_y, big_pos_.y - big_radius_);
    max_y = std::max(max_y, big_pos_.y + big_radius_);

    const double width = max_x - min_x;
    const double height = max_y - min_y;
    const p_t center = {(min-x + max_x) / 2.0, (min_y + max_y) / 2.0};

    return {width, height, center};
  }

  void Rubber::move(p_t p)
  {
    const double dx = p.x - pos_.x;
    const double dy = p.y - pos_.y;
    move(dx, dy);
  }

  void Rubber::move(double dx, double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
    big_pos_.x += dx;
    big_pos_.y += dy;
  }

  void Rubber::scale(double k)
  {
    if (k <= 0)
    {
      throw std::invalid_argument("Scale factor must be positive");
    }
    small_radius_ *= k;
    big_radius_ *= k;
    big_pos_.x = pos_.x + (big_pos_.x - pos_.x) * k;
    big_pos_.y = pos_.y + (big_pos_.y - pos_.y) * k;
  }
}
