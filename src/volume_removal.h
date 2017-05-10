#pragma once

#include "sparse_octree.h"

namespace sot {

  template<typename T>
  void remove_contained_volume_convex(const T& sweeper, sparse_octree& volume) {
    volume.remove_contained_volume_convex(sweeper);
  }

  template<typename T>
  void sweep_away_path(const T& sweeping_volume,
		       sparse_octree& volume) {
    
  }

}
