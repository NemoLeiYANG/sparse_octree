#pragma once

#include <vtkActor.h>
#include <vtkPlane.h>
#include <vtkPolyData.h>
#include <vtkPlaneSource.h>
#include <vtkSmartPointer.h>

#include "sparse_octree.h"

namespace sot {

  void visualize_actors(const std::vector<vtkSmartPointer<vtkActor> >& pds);
  void visualize_polydatas(const std::vector<vtkSmartPointer<vtkPolyData> >& actors);

  void vtk_debug_sparse_octree(const sparse_octree& tree);

}
