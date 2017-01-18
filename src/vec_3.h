#pragma once

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

}
