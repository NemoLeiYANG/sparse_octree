#pragma once

#include <cmath>

namespace sot {

  class vec_3 {
    double xc, yc, zc;

  public:
    vec_3(const double p_x, const double p_y, const double p_z)
      : xc(p_x), yc(p_y), zc(p_z) {}

    inline double x() const { return xc; }
    inline double y() const { return yc; }
    inline double z() const { return zc; }

  };

  inline vec_3 operator-(const vec_3 l, const vec_3 r) {
    return vec_3( l.x() - r.x(), l.y() - r.y(), l.z() - r.z() );
  }

  inline double len(const vec_3 v) {
    return sqrt( v.x()*v.x() + v.y()*v.y() + v.z()*v.z() );
  }

}
