#ifndef RUBBER_HPP
#define RUBBER_HPP

#include "shape.hpp"

namespace zaharov
{
  class Rubber: public Shape
  {
  public:
    Rubber(double small_radius, double big_radius, p_t pos, p_t big_pos);

    virtual double getArea() const override;
    virtual rec_t getFrameRect() const override;
    virtual void move(p_t p) override;
    virtual void move(double dx, double dy) override;
    virtual void scale(double k) override;

  private:
    double small_radius_;
    double big_radius_;
    p_t pos_;
    p_t big_pos_;
  };
}

#endif
