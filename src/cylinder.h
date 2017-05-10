#pragma once

#include <cmath>

#include "vec_3.h"

namespace sot {

  inline bool in_circle_2D(const vec_3 pt, const vec_3 center, const double radius) {
    double x_diff = pt.x() - center.x();
    double x_diff_sq = x_diff*x_diff;

    double y_diff = pt.y() - center.y();
    double y_diff_sq = y_diff*y_diff;

    double dist = sqrt( x_diff_sq + y_diff_sq );
    
    return dist < radius;
  }

  class cylinder {
  protected:
    vec_3 base_pt;
    double h, diam;

  public:
    cylinder(const vec_3 base, const double p_height, const double p_diameter) :
      base_pt(base), h(p_height), diam(p_diameter)
    {}

    double height() const { return h; }
    double diameter() const { return diam; }
    double radius() const { return diameter() / 2.0; }

    bool contains_point(const vec_3 pt) const {
      if ( in_circle_2D( pt, base_pt, radius() ) ) {
	double z_min = base_pt.z();
	double z_max = z_min + height();
	return z_min <= pt.z() && pt.z() <= z_max;
      }

      return false;
    }

  };

  cylinder build_at_position(const vec_3 position, const cylinder c);

}
