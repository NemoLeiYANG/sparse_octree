#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "box_3.h"

namespace sot {

  enum voxel_occupied { VOXEL_OCCUPIED, VOXEL_EMPTY, VOXEL_MIXED};

  class sp_tree {
    voxel_occupied is_occupied;

    std::unique_ptr<sp_tree> x_max_y_max_z_max;
    std::unique_ptr<sp_tree> x_max_y_max_z_min;
    std::unique_ptr<sp_tree> x_max_y_min_z_max;
    std::unique_ptr<sp_tree> x_max_y_min_z_min;

    std::unique_ptr<sp_tree> x_min_y_max_z_max;
    std::unique_ptr<sp_tree> x_min_y_max_z_min;
    std::unique_ptr<sp_tree> x_min_y_min_z_max;
    std::unique_ptr<sp_tree> x_min_y_min_z_min;
    
  public:
    sp_tree() : is_occupied(VOXEL_EMPTY),
		x_max_y_max_z_max(nullptr),
		x_max_y_max_z_min(nullptr),
		x_max_y_min_z_max(nullptr),
		x_max_y_min_z_min(nullptr),
		x_min_y_max_z_max(nullptr),
		x_min_y_max_z_min(nullptr),
		x_min_y_min_z_max(nullptr),
		x_min_y_min_z_min(nullptr) {}
		

    void set_occupied(const int depth,
		      const int max_depth,
		      const vec_3 location,
		      const box_3 box) {

      assert( in_box( location, box ) );

      if (depth == max_depth) {
	is_occupied = VOXEL_OCCUPIED;
	return;
      }

      std::cout << "Depth = " << depth << std::endl;
      std::cout << "Max depth = " << max_depth << std::endl;
      assert(false);
    }

    bool occupied(const vec_3 location,
		  const box_3 box) const {

      assert( in_box( location, box ) );

      if (!(is_occupied == VOXEL_MIXED)) {

	assert((is_occupied == VOXEL_OCCUPIED) ||
	       (is_occupied == VOXEL_EMPTY));

	return is_occupied == VOXEL_OCCUPIED;
      }

      assert(false);
    }

  };

  class sparse_octree {
  protected:
    vec_3 center;
    double len;
    // Not needed?
    int depth;
    int max_depth;

    std::unique_ptr<sp_tree> tree;

  public:
    sparse_octree(const vec_3 p_center,
		  const double p_len,
		  const int max_depth) :
      center(p_center), len(p_len), depth(1), max_depth(max_depth) {
      assert( max_depth > 0 );

      tree = std::unique_ptr<sp_tree>(new sp_tree());
    }

    box_3 bounding_box() const {
      double x_min = center.x() - len;
      double x_max = center.x() + len;

      double y_min = center.y() - len;
      double y_max = center.y() + len;

      double z_min = center.z() - len;
      double z_max = center.z() + len;
      
      return {x_min, x_max, y_min, y_max, z_min, z_max};
    }

    bool occupied(const vec_3 location) const {
      assert( in_box( location, bounding_box() ) );

      return tree->occupied(location, bounding_box());
    }

    void set_occupied(const vec_3 location) {
      assert( in_box( location, bounding_box() ) );

      tree->set_occupied(1, max_depth, location, bounding_box());
    }

  };

}
