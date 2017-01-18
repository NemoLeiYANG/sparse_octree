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
  
}
