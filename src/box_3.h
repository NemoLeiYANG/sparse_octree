#pragma once

#include "vec_3.h"

namespace sot {

  struct box_3 {
    double x_min, x_max,
      y_min, y_max,
      z_min, z_max;

    inline double x_mid() const { return (x_max + x_min) / 2.0; }
    inline double y_mid() const { return (y_max + y_min) / 2.0; }
    inline double z_mid() const { return (z_max + z_min) / 2.0; }
  };

  inline bool in_interval(const double p, const double min, const double max) {
    return (min <= p) && (p <= max);
  }

  inline bool in_box(const vec_3 pt, const box_3 b) {
    return in_interval(pt.x(), b.x_min, b.x_max) &&
      in_interval(pt.y(), b.y_min, b.y_max) &&
      in_interval(pt.z(), b.z_min, b.z_max);
  }

}
