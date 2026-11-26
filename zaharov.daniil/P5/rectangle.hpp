#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace zaharov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, p_t pos);

    virtual double getArea() const override;
    virtual rec_t getFrameRect() const override;
    virtual void move(p_t p) override;
    virtual void move(double dx, double dy) override;
    virtual void scale(double k) override;

  private:
    double width_;
    double height_;
    p_t pos_;
  };
}

#endif
