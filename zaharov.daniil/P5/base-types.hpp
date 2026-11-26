#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace zaharov
{
  struct p_t
  {
    double x;
    double y;
  };

  struct rec_t
  {
    double width;
    double height;
    p_t pos;
  };
}

#endif
