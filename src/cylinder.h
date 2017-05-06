#pragma once

#include "vec_3.h"

namespace sot {

  class cylinder {
  protected:
    vec_3 base_pt;
    double height, diameter;

  public:
    cylinder(const vec_3 base, const double p_height, const double p_diameter) :
      base_pt(base), height(p_height), diameter(p_diameter)
    {}

    bool contains_point(const vec_3 pt) const {
      return false;
    }

  };

}
