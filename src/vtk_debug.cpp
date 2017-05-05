#include "vtk_debug.h"

#include <vtkCellData.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkPoints.h>
#include <vtkFeatureEdges.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkClipPolyData.h>
#include <vtkProperty.h>
#include <vtkCellArray.h>
#include <vtkPolyDataNormals.h>
#include <vtkVertex.h>

#include <vtkAxesActor.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>

namespace sot {

  vtkSmartPointer<vtkActor> polydata_actor(vtkSmartPointer<vtkPolyData> polyData)
  {
    vtkSmartPointer<vtkPolyDataMapper> mapper =
      vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputData(polyData);
 
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    return actor;
  }
  
  void
  visualize_polydatas(const std::vector<vtkSmartPointer<vtkPolyData> >& pds) {
    std::vector<vtkSmartPointer<vtkActor> > actors;

    for (auto& pd : pds) {
      actors.push_back(polydata_actor(pd));
    }

    visualize_actors(actors);
  }
  
  void visualize_actors(const std::vector<vtkSmartPointer<vtkActor> >& actors)
  {
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    // Create axes
    vtkSmartPointer<vtkAxesActor> axes =
      vtkSmartPointer<vtkAxesActor>::New();

    renderer->AddActor(axes);
    for (auto actor : actors) {
      renderer->AddActor(actor);
    }
    renderer->SetBackground(0.0, 0.0, 0.0); //1.0, 1.0, 1.0); //0.0, 0.0, 0.0); //.1, .2, .3);

    vtkSmartPointer<vtkRenderWindow> renderWindow =
      vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
      vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    renderWindow->Render();
    renderWindowInteractor->Start();
  }

  vtkSmartPointer<vtkPolyData>
  polydata_for_sparse_octree(const sparse_octree& df) {
    vtkSmartPointer<vtkPoints> points =
      vtkSmartPointer<vtkPoints>::New();
 
    vtkSmartPointer<vtkCellArray> vertices =
      vtkSmartPointer<vtkCellArray>::New();
    
    // for (int i = 0; i < df.num_x_elems; i++) {
    //   for (int j = 0; j < df.num_y_elems; j++) {

    // 	auto id = points->InsertNextPoint(df.x_center(i),
    // 					  df.y_center(j),
    // 					  df.column_height(i, j));
    // 	vtkSmartPointer<vtkVertex> vertex = 
    // 	  vtkSmartPointer<vtkVertex>::New();

    // 	vertex->GetPointIds()->SetId(0, id);
    // 	vertices->InsertNextCell(vertex);
    //   }
    // }
 
    vtkSmartPointer<vtkPolyData> polydata =
      vtkSmartPointer<vtkPolyData>::New();
    polydata->SetPoints(points);
    polydata->SetVerts(vertices);

    return polydata;
  }
  
}
