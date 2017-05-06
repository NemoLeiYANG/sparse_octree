#pragma once

#include "sparse_octree.h"

namespace sot {

  template<typename T>
  void remove_contained_volume_convex(const T& sweeper, sparse_octree& volume) {
    volume.remove_contained_volume_convex(sweeper);
  }

}
