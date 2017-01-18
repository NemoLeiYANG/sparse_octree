#pragma once

#include "vec_3.h"

namespace sot {

  struct box_3 {
    double x_min, x_max,
      y_min, y_max,
      z_min, z_max;
  };

  bool in_interval(const double p, const double min, const double max) {
    return (min <= p) && (p <= max);
  }

  bool in_box(const vec_3 pt, const box_3 b) {
    return in_interval(pt.x(), b.x_min, b.x_max) &&
      in_interval(pt.y(), b.y_min, b.y_max) &&
      in_interval(pt.z(), b.z_min, b.z_max);
  }

}
