#include "catch.hpp"

#include "cylinder.h"
#include "sparse_octree.h"
#include "volume_removal.h"

namespace sot {

  TEST_CASE("Cylinder contains entire volume") {
    sparse_octree so( vec_3( 3.0, -6.0, 3.0 ), 2.0, 4 );
    vec_3 test_pt( 3.0, -7.0, 3.0 );
    so.set_occupied( test_pt );

    cylinder c( vec_3( 3.0, -6.0, -1.0 ), 20, 10);

    remove_contained_volume_convex( c, so );

    REQUIRE( so.empty( test_pt ) );
  }

}
