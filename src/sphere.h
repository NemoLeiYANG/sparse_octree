#pragma once

#include "vec_3.h"

namespace sot {

  class sphere {
  protected:
    vec_3 center;
    double radius;

  public:
    sphere(const vec_3 p_center, const double p_radius) :
      center(p_center), radius(p_radius) {}

    inline bool contains_point(const vec_3 pt) const {
      return len(pt - center) < radius;
    }

  };

}
