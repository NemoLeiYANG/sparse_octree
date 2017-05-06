#include "catch.hpp"

#include "cylinder.h"

namespace sot {

  TEST_CASE("Circle containment") {
    vec_3 pt(2.0, 0.0, 0.0);

    vec_3 center(1.0, 0.0, 0.0);
    double radius(0.25);

    REQUIRE( !in_circle_2D( pt, center, radius ) );
  }

}
