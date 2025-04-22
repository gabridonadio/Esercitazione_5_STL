#pragma once

#include <iostream>
#include "PolygonalMesh.hpp"

using namespace std;

namespace PolygonalLibrary
{
bool MarkerTest0D(PolygonalMesh& mesh);
bool MarkerTest1D(PolygonalMesh& mesh);
bool MarkerTest2D(PolygonalMesh& mesh);
bool SegmentsTest(PolygonalMesh& mesh, const double& tol);
bool AreaTest(PolygonalMesh& mesh, const double& tol);
}