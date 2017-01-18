#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "sparse_octree.h"

namespace sot {

  TEST_CASE("Empty octree") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 0.5, 1);

    REQUIRE( !so.occupied(vec_3(0.0, 0.0, 0.1)) );
  }

  TEST_CASE("Occupied octree") {
    sparse_octree so(vec_3(1.0, 2.0, 3.0), 1.0, 1);

    so.set_occupied(vec_3(1.0, 2.1, 3.0));

    REQUIRE( so.occupied(vec_3(1.0, 2.1, 3.0)) );
  }

  TEST_CASE("max x, max y, max z quadrant only one occupied") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 2.0, 2);

    so.set_occupied(vec_3(0.5, 0.5, 0.5));
    
    SECTION("target is occupied") {
      REQUIRE( so.occupied(vec_3(1.0, 1.0, 1.0)) );
    }

    SECTION("other section is not occupied") {
      REQUIRE( !so.occupied(vec_3(-1.0, -1.0, 1.0)) );
    }
    
  }
  
}
