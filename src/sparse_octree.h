#pragma once

#include "vec_3.h"

namespace sot {

  class sparse_octree {
  public:
    sparse_octree(const vec_3 p_center,
		  const double p_diam) {}

    bool occupied(const vec_3 point) { return false; }

  };

}
