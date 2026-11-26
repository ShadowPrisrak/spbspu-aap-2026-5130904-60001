#include <iostream>
#include <stdexcept>
#include "rectangle.hpp"
#include "circle.hpp"
#include "rubber.hpp"

void printShape(const zaharov::Shape* shape, const char* name)
{
  const zaharov::rectangle_t frame = shape->getFrameRect();
  std::cout << name << ": area = " << shape->getArea()
            << ", frame = (" << frame.pos.x << ", " << frame.pos.y
            << ", " << frame.width << ", " << frame.height << ")\n";
}

int main()
{
  const size_t count = 3;
  zaharov::Shape* shapes[count];

  try
  {
    shapes[0] = new zaharov::Rectangle(4.0, 2.0, {0.0, 0.0});
    shapes[1] = new zaharov::Circle(3.0, {5.0, 5.0});
    shapes[2] = new zaharov::Rubber(1.0, 3.0, {10.0, 10.0}, {11.0, 11.0});
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error creating shapes: " << e.what() << '\n';
    for (size_t i = 0; i < count; ++i)
    {
      delete shapes[i];
    }
    return 1;
  }

  std::cout << "Before scaling:\n";
  for (size_t i = 0; i < count; ++i)
  {
    printShape(shapes[i], "Shape");
  }

  double px = 0.0, py = 0.0, k = 0.0;
  std::cout << "Enter center point (x y) and scale factor k: ";
  if (!(std::cin >> px >> py >> k))
  {
    std::cerr << "Error: invalid input\n";
    for (size_t i = 0; i < count; ++i) delete shapes[i];
    return 1;
  }

  if (k <= 0)
  {
    std::cerr << "Error: scale factor must be positive\n";
    for (size_t i = 0; i < count; ++i) delete shapes[i];
    return 1;
  }

  const zaharov::point_t center = {px, py};

  for (size_t i = 0; i < count; ++i)
  {
    const zaharov::rectangle_t frame = shapes[i]->getFrameRect();
    const double dx = frame.pos.x - center.x;
    const double dy = frame.pos.y - center.y;

    shapes[i]->move(center.x, center.y);
    shapes[i]->scale(k);
    shapes[i]->move(center.x + dx * k, center.y + dy * k);
  }

  std::cout << "\nAfter scaling:\n";
  double total_area = 0.0;
  for (size_t i = 0; i < count; ++i)
  {
    printShape(shapes[i], "Shape");
    total_area += shapes[i]->getArea();
    delete shapes[i];
  }

  std::cout << "Total area: " << total_area << '\n';

  return 0;
}
