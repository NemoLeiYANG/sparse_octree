#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "box_3.h"

namespace sot {

  enum voxel_occupied { VOXEL_OCCUPIED, VOXEL_EMPTY, VOXEL_MIXED};

  class sp_tree {
    voxel_occupied is_occupied;

    std::vector<sp_tree*> children;

    // std::unique_ptr<sp_tree> x_max_y_max_z_max;
    // std::unique_ptr<sp_tree> x_max_y_max_z_min;
    // std::unique_ptr<sp_tree> x_max_y_min_z_max;
    // std::unique_ptr<sp_tree> x_max_y_min_z_min;

    // std::unique_ptr<sp_tree> x_min_y_max_z_max;
    // std::unique_ptr<sp_tree> x_min_y_max_z_min;
    // std::unique_ptr<sp_tree> x_min_y_min_z_max;
    // std::unique_ptr<sp_tree> x_min_y_min_z_min;
    
  public:
    sp_tree() : is_occupied(VOXEL_EMPTY) {
      for (unsigned i = 0; i < 8; i++) {
	children.push_back(nullptr);
      }
    }
		// x_max_y_max_z_max(nullptr),
		// x_max_y_max_z_min(nullptr),
		// x_max_y_min_z_max(nullptr),
		// x_max_y_min_z_min(nullptr),
		// x_min_y_max_z_max(nullptr),
		// x_min_y_max_z_min(nullptr),
		// x_min_y_min_z_max(nullptr),
		// x_min_y_min_z_min(nullptr) {}
		

    std::pair<box_3, int> find_octant(const vec_3 location,
				      const box_3 box) const {
      assert( in_box( location, box ) );

      // In x min
      if (in_interval(location.x(), box.x_min, box.x_mid())) {
	// In y min
	if (in_interval(location.y(), box.y_min, box.y_mid())) {
	  // In z min
	  if (in_interval(location.z(), box.z_min, box.z_mid())) {

	    box_3 b{box.x_min, box.x_mid(),
		box.y_min, box.y_mid(),
		box.z_min, box.z_mid()};

	    return std::make_pair(b, 0); //x_min_y_min_z_min.get());
	  }
	  // In z max
	  else {
	    box_3 b{box.x_min, box.x_mid(),
		box.y_min, box.y_mid(),
		box.z_mid(), box.z_max};

	    return std::make_pair(b, 1); //x_min_y_min_z_max.get());
	  }
	}
	// In y max
	else {
	  // In z min
	  if (in_interval(location.z(), box.z_min, box.z_mid())) {
	    box_3 b{box.x_min, box.x_mid(),
		box.y_mid(), box.y_max,
		box.z_min, box.z_mid()};

	    return std::make_pair(b, 2); //x_min_y_max_z_min.get());
	    
	  }
	  // In z max
	  else {
	    box_3 b{box.x_min, box.x_mid(),
		box.y_mid(), box.y_max,
		box.z_mid(), box.z_max};

	    return std::make_pair(b, 3); //x_min_y_max_z_max.get());
	    
	  }
	}
      }
      // In x max
      else {
	// In y min
	if (in_interval(location.y(), box.y_min, box.y_mid())) {
	  // In z min
	  if (in_interval(location.z(), box.z_min, box.z_mid())) {

	    box_3 b{box.x_mid(), box.x_max,
		box.y_min, box.y_mid(),
		box.z_min, box.z_mid()};

	    return std::make_pair(b, 4); //x_max_y_min_z_min.get());
	  }
	  // In z max
	  else {
	    box_3 b{box.x_mid(), box.x_max,
		box.y_min, box.y_mid(),
		box.z_mid(), box.z_max};

	    return std::make_pair(b, 5); //x_max_y_min_z_max.get());
	  }
	}
	// In y max
	else {
	  // In z min
	  if (in_interval(location.z(), box.z_min, box.z_mid())) {
	    box_3 b{box.x_mid(), box.x_max,
		box.y_mid(), box.y_max,
		box.z_min, box.z_mid()};

	    return std::make_pair(b, 6); //x_max_y_max_z_min.get());
	    
	  }
	  // In z max
	  else {
	    box_3 b{box.x_mid(), box.x_max,
		box.y_mid(), box.y_max,
		box.z_mid(), box.z_max};

	    return std::make_pair(b, 7); //x_max_y_max_z_max.get());
	    
	  }
	}
	
      }
    }

    void set_occupied(const int depth,
		      const int max_depth,
		      const vec_3 location,
		      const box_3 box) {

      assert( in_box( location, box ) );

      assert(children.size() == 8);

      if (depth == max_depth) {
	is_occupied = VOXEL_OCCUPIED;
	return;
      }

      // std::cout << "Depth = " << depth << std::endl;
      // std::cout << "Max depth = " << max_depth << std::endl;

      is_occupied = VOXEL_MIXED;

      std::pair<box_3, int> next_octant = find_octant(location, box);

      if (children[next_octant.second] == nullptr) {
	children[next_octant.second] = new sp_tree();
      }

      children[next_octant.second]->set_occupied(depth + 1, max_depth, location, next_octant.first);
      
    }

    bool occupied(const vec_3 location,
		  const box_3 box) const {

      assert( in_box( location, box ) );

      assert(children.size() == 8);


      // std::cout << "octant box" << std::endl;
      // std::cout << box.x_min << ", " << box.x_max << std::endl;
      // std::cout << box.y_min << ", " << box.y_max << std::endl;
      // std::cout << box.z_min << ", " << box.z_max << std::endl;
      
      if (is_occupied != VOXEL_MIXED) {

	assert((is_occupied == VOXEL_OCCUPIED) ||
	       (is_occupied == VOXEL_EMPTY));

	//std::cout << "DONE" << std::endl;

	return is_occupied == VOXEL_OCCUPIED;
      }

      std::pair<box_3, int> next_octant = find_octant(location, box);

      //std::cout << "Next octant index = " << next_octant.second << std::endl;

      if (children[next_octant.second] == nullptr) {
	//std::cout << "NULL BOX" << std::endl;
	return false;
      }

      box_3 next_box = next_octant.first;
      // std::cout << "Next box = " << std::endl;
      // std::cout << next_box.x_min << ", " << next_box.x_max << std::endl;
      // std::cout << next_box.y_min << ", " << next_box.y_max << std::endl;
      // std::cout << next_box.z_min << ", " << next_box.z_max << std::endl;
      
      return (children[next_octant.second])->occupied(location, next_octant.first);
    }

    ~sp_tree() {

      for (sp_tree* c : children) {
	delete c;
      }
    }

    void print_tree() {
      std::cout << "OCCUPIED = " << is_occupied << std::endl;

      for (auto c : children) {
	if (c != nullptr) {
	  std::cout << "-- NEXT" << std::endl;
	  c->print_tree();
	  std::cout << "-- DONE" << std::endl;
	} else {
	  std::cout << "NULL CHILD" << std::endl;
	}
      }

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

    void print_tree() {
      std::cout << "levels = " << max_depth << std::endl;
      tree->print_tree();
    }



  };

}
