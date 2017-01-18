#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "sparse_octree.h"

namespace sot {

  TEST_CASE("Empty octree") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 0.5);

    REQUIRE(!so.occupied(vec_3(0.0, 0.0, 0.1)));
  }

}
