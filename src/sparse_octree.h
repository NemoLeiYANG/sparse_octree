#pragma once

#include <cassert>
#include <iostream>
#include <memory>
#include <vector>

#include "box_3.h"

namespace sot {

  enum voxel_occupied { VOXEL_OCCUPIED, VOXEL_EMPTY, VOXEL_MIXED};

  template<typename T>
  int contained_extreme_points(const T& convex_volume, const box_3& bb) {
    vec_3 m0(bb.x_min, bb.y_min, bb.z_min);
    vec_3 m1(bb.x_min, bb.y_min, bb.z_max);
    vec_3 m2(bb.x_min, bb.y_max, bb.z_min);
    vec_3 m3(bb.x_min, bb.y_max, bb.z_max);

    vec_3 m4(bb.x_max, bb.y_min, bb.z_min);
    vec_3 m5(bb.x_max, bb.y_min, bb.z_max);
    vec_3 m6(bb.x_max, bb.y_max, bb.z_min);
    vec_3 m7(bb.x_max, bb.y_max, bb.z_max);
    std::vector<vec_3> extreme_pts{m0, m1, m2, m3, m4, m5, m6, m7};

    int num_contained = 0;
    for (auto pt : extreme_pts) {
      if ( convex_volume.contains_point(pt) ) {
	num_contained++;
      }
    }

    return num_contained;
  }

  class sp_tree {
    voxel_occupied is_occupied;

    std::vector<sp_tree*> children;

  public:
    sp_tree() : is_occupied(VOXEL_EMPTY) {
      for (unsigned i = 0; i < 8; i++) {
	children.push_back(nullptr);
      }
    }

    box_3 octant_box(const int octant_number, const box_3 box) const {

      switch (octant_number) {
      case 0:
	return {box.x_min, box.x_mid(),
	    box.y_min, box.y_mid(),
	    box.z_min, box.z_mid()};

      case 1:

	return {box.x_min, box.x_mid(),
	    box.y_min, box.y_mid(),
	    box.z_mid(), box.z_max};

      case 2:
	return {box.x_min, box.x_mid(),
	    box.y_mid(), box.y_max,
	    box.z_min, box.z_mid()};

      case 3:
	return {box.x_min, box.x_mid(),
	    box.y_mid(), box.y_max,
	    box.z_mid(), box.z_max};

      case 4:
	return {box.x_mid(), box.x_max,
	    box.y_min, box.y_mid(),
	    box.z_min, box.z_mid()};

      case 5:
	return {box.x_mid(), box.x_max,
	    box.y_min, box.y_mid(),
	    box.z_mid(), box.z_max};

      case 6:
	return {box.x_mid(), box.x_max,
	    box.y_mid(), box.y_max,
	    box.z_min, box.z_mid()};

      case 7:
	return {box.x_mid(), box.x_max,
	    box.y_mid(), box.y_max,
	    box.z_mid(), box.z_max};

      default:
	assert(false);
      }
    }

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

    void set_empty(const int depth,
		   const int max_depth,
		   const vec_3 location,
		   const box_3 box) {
      assert( in_box( location, box ) );

      assert( in_box( location, box ) );

      assert(children.size() == 8);

      if (depth == max_depth) {
	is_occupied = VOXEL_EMPTY;
	return;
      }

      // std::cout << "Depth = " << depth << std::endl;
      // std::cout << "Max depth = " << max_depth << std::endl;

      is_occupied = VOXEL_MIXED;

      std::pair<box_3, int> next_octant = find_octant(location, box);

      if (children[next_octant.second] == nullptr) {
	children[next_octant.second] = new sp_tree();
      }

      children[next_octant.second]->set_empty(depth + 1, max_depth, location, next_octant.first);
      
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

    bool empty(const vec_3 location,
	       const box_3 box) const {
      return !occupied(location, box);
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

      //box_3 next_box = next_octant.first;
      // std::cout << "Next box = " << std::endl;
      // std::cout << next_box.x_min << ", " << next_box.x_max << std::endl;
      // std::cout << next_box.y_min << ", " << next_box.y_max << std::endl;
      // std::cout << next_box.z_min << ", " << next_box.z_max << std::endl;
      
      return (children[next_octant.second])->occupied(location, next_octant.first);
    }

    int total_nodes() const {
      int nodes = 1;

      for (sp_tree* child : children) {
	if (child != nullptr) {
	  nodes += child->total_nodes();
	}
      }

      return nodes;
    }

    ~sp_tree() {

      for (sp_tree* c : children) {
	delete c;
      }
    }

    void print_tree() const {
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

    void reset_children() {
      for (sp_tree* child : children) {
	delete child;
      }

      for (unsigned i = 0; i < 8; i++) {
	children[i] = nullptr;
      }
    }

    void compress_nodes() {
      if (is_occupied == VOXEL_MIXED) {
	bool all_occupied = true;
	for (sp_tree* child : children) {
	  if (child != nullptr && (child->is_occupied != VOXEL_OCCUPIED)) {
	    all_occupied = false;
	    break;
	  }
	}

	if (all_occupied) {
	  reset_children();

	  this->is_occupied = VOXEL_OCCUPIED;

	  return;
	}

	bool all_empty = true;
	for (sp_tree* child : children) {
	  if (child != nullptr && (child->is_occupied != VOXEL_EMPTY)) {
	    all_empty = false;
	    break;
	  }
	}

	if (all_empty) {
	  reset_children();

	  this->is_occupied = VOXEL_EMPTY;

	  return;
	}

      }

      for (sp_tree* child : children) {
	if (child != nullptr) {
	  child->compress_nodes();
	}
      }

    }

    std::vector<vec_3> centroids(const box_3 bb) const {
      std::vector<vec_3> pts;

      if (is_occupied == VOXEL_OCCUPIED) {
	vec_3 m0(bb.x_min, bb.y_min, bb.z_min);
	vec_3 m1(bb.x_min, bb.y_min, bb.z_max);
	vec_3 m2(bb.x_min, bb.y_max, bb.z_min);
	vec_3 m3(bb.x_min, bb.y_max, bb.z_max);

	vec_3 m4(bb.x_max, bb.y_min, bb.z_min);
	vec_3 m5(bb.x_max, bb.y_min, bb.z_max);
	vec_3 m6(bb.x_max, bb.y_max, bb.z_min);
	vec_3 m7(bb.x_max, bb.y_max, bb.z_max);

	pts = {m0, m1, m2, m3, m4, m5, m6, m7};
      }

      if (is_occupied == VOXEL_MIXED) {
	for (int i = 0; i < 8; i++) {
	  sp_tree* child = children[i];

	  if (child != nullptr) {
	    box_3 child_bb = octant_box(i, bb);
	    for (auto pt : child->centroids(child_bb)) {
	      pts.push_back(pt);
	    }
	  }
	}
      }
      
      return pts;
    }

    template<typename T>
    void remove_contained_volume_convex(const T& convex_volume,
					const int depth,
					const int max_depth,
					const box_3 bounding_box) {

      assert(depth <= max_depth);

      if (depth == max_depth) {
	// Sweep box away if anything is contained
	if ( contained_extreme_points( convex_volume, bounding_box ) > 0 ) {
	  is_occupied = VOXEL_EMPTY;
	  return;
	}

	is_occupied = VOXEL_OCCUPIED;

	return;
      }

      // Test whether sub-boxes are contained
      std::vector<int> fully_contained;
      std::vector<int> not_contained;
      std::vector<int> partially_contained;

      for (int i = 0; i < 8; i++) {
	box_3 child_box = octant_box(i, bounding_box);
	int num_contained_points =
	  contained_extreme_points(convex_volume, child_box);

	assert(num_contained_points <= 8);

	if (num_contained_points == 0) {
	  not_contained.push_back(i);
	} else if (num_contained_points == 8) {
	  fully_contained.push_back(i);
	} else {
	  partially_contained.push_back(i);
	}
      }

      if (fully_contained.size() == 8) {
	reset_children();
	is_occupied = VOXEL_EMPTY;
	return;
      }

      if (not_contained.size() == 8) {
	std::cout << "None contained" << std::endl;
	return;
      }

      for (auto& f : fully_contained) {
	partially_contained.push_back(f);
      }

      // std::cout << "# partially contained = " << partially_contained.size() <<
      // 	std::endl;

      // If the voxel was previously fully occupied break it
      // down to its occupied children
      if (is_occupied == VOXEL_OCCUPIED) {
	//std::cout << "Setting children occupied" << std::endl;
	initialize_children_occupied();
	is_occupied = VOXEL_MIXED;
      }

      for (auto child_index : partially_contained) {

	//std::cout << "Next index = " << child_index << std::endl;

	if (children[child_index] != nullptr) {

	  //std::cout << "Removing volume for child box " << child_index << std::endl;

	  box_3 child_box = octant_box(child_index, bounding_box);
	  children[child_index]->remove_contained_volume_convex(convex_volume,
								depth + 1,
								max_depth,
								child_box);
	}
	
      }

    }

    void initialize_children_occupied() {
      reset_children();

      for (int i = 0; i < 8; i++) {
	children[i] = new sp_tree();
	children[i]->is_occupied = VOXEL_OCCUPIED;
      }

    }

    void set_all_occupied() {
      reset_children();
      is_occupied = VOXEL_OCCUPIED;
    }

  };

  class sparse_octree {
  protected:
    vec_3 center;
    double len;
    int max_depth;

    std::unique_ptr<sp_tree> tree;

  public:
    sparse_octree(const vec_3 p_center,
		  const double p_len,
		  const int max_depth) :
      center(p_center), len(p_len), max_depth(max_depth) {

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

    bool empty(const vec_3 location) const {
      assert( in_box( location, bounding_box() ) );

      return tree->empty(location, bounding_box());
    }

    bool empty(const double x, const double y, const double z) const {
      vec_3 location(x, y, z);
      return empty(location);
    }
    
    void set_occupied(const vec_3 location) {
      assert( in_box( location, bounding_box() ) );

      tree->set_occupied(1, max_depth, location, bounding_box());
    }

    void set_empty(const vec_3 location) {
      assert( in_box( location, bounding_box() ) );

      tree->set_empty(1, max_depth, location, bounding_box());
    }
    

    void set_occupied(const double x, const double y, const double z) {
      vec_3 location(x, y, z);
      set_occupied(location);
    }

    void set_empty(const double x, const double y, const double z) {
      vec_3 location(x, y, z);
      set_empty(location);
    }
    
    int total_nodes() const {
      return tree->total_nodes();
    }

    void print_tree() const {
      std::cout << "levels = " << max_depth << std::endl;
      tree->print_tree();
    }


    void compress_nodes() {
      tree->compress_nodes();
    }

    std::vector<vec_3> centroids() const {
      return tree->centroids(bounding_box());
    }

    void set_all_occupied() {
      tree->set_all_occupied();
    }

    template<typename T>
    void remove_contained_volume_convex(const T& sweeper) {
      box_3 bb = bounding_box();
      tree->remove_contained_volume_convex(sweeper, 1, max_depth, bb);
    }

  };

}
