#include "catch.hpp"

#include "cylinder.h"
#include "sparse_octree.h"

namespace sot {

  TEST_CASE("Cylinder contains entire volume") {
    sparse_octree so( vec_3( 3.0, -6.0, 3.0 ), 1.0, 4 );

    cylinder c( vec_3( 3.0, -6.0, -1.0 ), 20, 10);
  }

}
