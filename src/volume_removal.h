#pragma once

#include "sparse_octree.h"

namespace sot {

  template<typename T>
  void remove_contained_volume_convex(const T& sweeper, sparse_octree& volume) {
    volume.remove_contained_volume_convex(sweeper);
  }

  template<typename T>
  void sweep_away_path(const T& sweeping_volume,
		       const std::vector<vec_3>& positions,
		       sparse_octree& volume) {
    for (auto& position : positions) {
      auto at_pos = build_at_position( position, sweeping_volume );
      remove_contained_volume_convex( at_pos, volume );
    }
  }

}
