#include <iostream>
#include "PolygonalMesh.hpp"
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include "Test_Utils.hpp"

using namespace std;
using namespace Eigen;
using namespace PolygonalLibrary;

int main()
{
    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        cerr << "file not found" << endl;
        return 1;
    }
	
	
	/// TEST su corretta memorizzazione dei marker
	
	MarkerTest0D(mesh);
	MarkerTest1D(mesh);
	MarkerTest2D(mesh);
	
	double tol = 1e-8; 
	
	/// TEST su lunghezza "non nulla" di segmenti e area "non nulla"
	
	SegmentsTest(mesh, tol);
	AreaTest(mesh, tol);
	
	/// TEST visivo sulla mesh effettuato con Kitware Glance
	
	
    Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates);

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema);
	
	
    return 0;
}