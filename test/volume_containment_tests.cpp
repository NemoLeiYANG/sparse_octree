#include "catch.hpp"

#include "cylinder.h"
#include "sparse_octree.h"
#include "sphere.h"
#include "volume_removal.h"
#include "vtk_debug.h"

using namespace std;

namespace sot {

  TEST_CASE("Cylinder contains entire volume") {
    sparse_octree so( vec_3( 3.0, -6.0, 3.0 ), 2.0, 4 );
    vec_3 test_pt( 3.0, -7.0, 3.0 );
    so.set_occupied( test_pt );

    cylinder c( vec_3( 3.0, -6.0, -1.0 ), 20, 10);

    remove_contained_volume_convex( c, so );

    REQUIRE( so.empty( test_pt ) );
  }

  TEST_CASE("Cylinder contains none of the volume") {

    sparse_octree so( vec_3( 3.0, -6.0, 3.0 ), 2.0, 4 );
    vec_3 test_pt( 3.0, -7.0, 3.0 );
    so.set_occupied( test_pt );

    cylinder c( vec_3( 30.0, -60.0, -10.0 ), 2, 0.5);

    remove_contained_volume_convex( c, so );

    REQUIRE( so.occupied( test_pt ) );

  }

  TEST_CASE("Cylinder contains part of the volume") {
    sparse_octree so( vec_3( 1.0, 1.0, 1.0 ), 0.5, 6 );
    so.set_all_occupied();

    vec_3 test_pt_outside( 1.49, 1.0, 1.1 );

    //cout << "Total nodes = " << so.total_nodes() << endl;

    cylinder c( vec_3(2.0, 1.0, 1.00), 2.0, 1.5);

    remove_contained_volume_convex( c, so );

    // cout << "Total nodes = " << so.total_nodes() << endl;
    //vtk_debug_sparse_octree( so );

    REQUIRE( !so.occupied( test_pt_outside ) );
  }

  TEST_CASE("Smaller cylinder with out of range point") {
    sparse_octree so( vec_3( 1.0, 1.0, 1.0 ), 0.5, 6 );
    so.set_all_occupied();

    vec_3 test_pt_outside( 1.49, 1.2, 1.1 );

    cout << "Total nodes = " << so.total_nodes() << endl;

    cylinder c( vec_3(1.5, 1.0, 1.0), 2.0, 0.1);

    remove_contained_volume_convex( c, so );

    cout << "Total nodes = " << so.total_nodes() << endl;
    //vtk_debug_sparse_octree( so );

    REQUIRE( so.occupied( test_pt_outside ) );
  }

  TEST_CASE("Cylinder removes volume") {
    sparse_octree so( vec_3(-1.0, -2.0, 0.0), 1.5, 7 );
    so.set_all_occupied();

    sphere s( vec_3( -1.0, -2.0, 1.5 ), 0.5 );

    remove_contained_volume_convex( s, so );

    //vtk_debug_sparse_octree( so );

    vec_3 test_pt_inside_sphere( -1.0, -2.0, 1.2 );

    REQUIRE( !so.occupied( test_pt_inside_sphere ) );
  }

  TEST_CASE("Multipoint path") {
    double x = 0.0;
    double y = 0.0;

    vector<vec_3> points;
    points.push_back( vec_3( 0.0, 0.0, 0.0 ) );
    points.push_back( vec_3( 0.0, 0.0, 0.0 ) );

    
  }
  
}
