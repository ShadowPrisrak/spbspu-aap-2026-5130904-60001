#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace zaharov
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, p_t pos);

    virtual double getArea() const override;
    virtual rec_t getFrameRect() const override;
    virtual void move(point_t p) override;
    virtual void move(double dx, double dy) override;
    virtual void scale(double k) override;

  private:
    double radius_;
    p_t pos_;
  };
}

#endif
