#define CATCH_CONFIG_MAIN

#include "catch.hpp"

#include "sparse_octree.h"

using namespace std;

namespace sot {

  TEST_CASE("Empty octree") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 0.5, 1);

    REQUIRE( !so.occupied(vec_3(0.0, 0.0, 0.1)) );
  }

  TEST_CASE("Occupied octree") {
    sparse_octree so(vec_3(1.0, 2.0, 3.0), 1.0, 1);

    so.set_occupied(vec_3(1.0, 2.1, 3.0));

    SECTION("Set cell is occupied") {
      REQUIRE( so.occupied(vec_3(1.0, 2.1, 3.0)) );
    }

    SECTION("Set occupied then empty") {
      so.set_empty(1.0, 2.1, 3.0);

      REQUIRE(so.empty(1.0, 2.1, 3.0));
    }
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

  TEST_CASE("max x, max y, min z quadrant only one occupied") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 2.0, 2);

    so.set_occupied(vec_3(0.5, 0.5, -0.5));

    SECTION("target is occupied") {
      REQUIRE( so.occupied(vec_3(1.0, 1.0, -1.0)) );
    }

    SECTION("other section is not occupied") {
      REQUIRE( !so.occupied(vec_3(-1.0, 0.0, 1.0)) );
    }
    
  }

  TEST_CASE("max x, min y, max z quadrant only one occupied") {
    sparse_octree so(vec_3(0.0, 0.0, 0.0), 2.0, 4);

    so.set_occupied(vec_3(0.2, -0.25, 1.0));

    SECTION("target is occupied") {
      REQUIRE( so.occupied(vec_3(0.23, -0.24, 0.9)) );
    }

    SECTION("other section is not occupied") {
      REQUIRE( !so.occupied(vec_3(1.0, -0.01, -1.0)) );
    }
    
  }

  TEST_CASE("Testing octree compression") {
    sparse_octree so( vec_3(0.0, 0.0, 0.0), 2.0, 2 );

    cout << "# of nodes = " << so.total_nodes() << endl;
    
    so.set_occupied(-0.5, -0.5, -0.5);
    so.set_occupied(-0.5, -0.5, 0.5);
    so.set_occupied(-0.5, 0.5, -0.5);
    so.set_occupied(-0.5, 0.5, 0.5);

    so.set_occupied(0.5, -0.5, -0.5);
    so.set_occupied(0.5, -0.5, 0.5);
    so.set_occupied(0.5, 0.5, -0.5);
    so.set_occupied(0.5, 0.5, 0.5);

    cout << "# of nodes = " << so.total_nodes() << endl;

    so.compress_nodes();

    cout << "After compression" << endl;

    SECTION("Compress full tree") {
      REQUIRE(so.total_nodes() == 1);
    }

    SECTION("Compress empty tree") {
      so.set_empty(-0.5, -0.5, -0.5);
      so.set_empty(-0.5, -0.5, 0.5);
      so.set_empty(-0.5, 0.5, -0.5);
      so.set_empty(-0.5, 0.5, 0.5);

      so.set_empty(0.5, -0.5, -0.5);
      so.set_empty(0.5, -0.5, 0.5);
      so.set_empty(0.5, 0.5, -0.5);
      so.set_empty(0.5, 0.5, 0.5);

      so.compress_nodes();

      REQUIRE(so.total_nodes() == 1);
      
    }
  }

  
}
