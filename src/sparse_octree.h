#pragma once

#include <vector>

#include "vec_3.h"

namespace sot {

  class sparse_octree {
  protected:
    int depth;
    int max_depth;

    std::vector<sparse_octree*> children;

  public:
    sparse_octree(const vec_3 p_center,
		  const double p_diam,
		  const int max_depth) : depth(1), max_depth(max_depth) {
      assert( max_depth > 0 );
    }

    box_3 bounding_box() const {
      
    }

    bool occupied(const vec_3 point) const { return false; }

    void set_occupied(const vec_3 location) {
      assert( in_box( location, bounding_box() ) );

      
    }

    ~sparse_octree() {
      for (auto c : children) {
	delete c;
      }
    }

  };

}
