#include "catch.hpp"

#include "cylinder.h"

namespace sot {

  TEST_CASE("2D circle containment") {

    vec_3 center(1.0, 0.0, 0.0);
    double radius(0.25);

    SECTION("Point outside circle") {
      vec_3 pt(2.0, 0.0, 0.0);

      REQUIRE( !in_circle_2D( pt, center, radius ) );
    }

    SECTION("Point inside circle") {
      vec_3 pt(1.1, -0.05, 10.0);

      REQUIRE( in_circle_2D( pt, center, radius ) );
    }

  }

}
