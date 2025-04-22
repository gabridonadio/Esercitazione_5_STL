#include <iostream>
#include <Test_Utils.hpp>
#include <fstream>
#include <sstream>

using namespace std;

namespace PolygonalLibrary
{
	bool MarkerTest0D(PolygonalMesh& mesh)
	{
		string FilePathInput = "./Cell0Ds.csv";
		ifstream file(FilePathInput);
		list<string> listLines0D;
		list<unsigned int> listMarker0D;
		string line; 
		
		while (getline(file, line))
			listLines0D.push_back(line);

		file.close();

		// remove header
		listLines0D.pop_front();
		
		for (string& line : listLines0D)
		{
			replace(line.begin(), line.end(), ';', ' ');
			istringstream converter(line);

			unsigned int id;
			unsigned int marker;

			converter >> id >> marker;

			if(marker!=0)
				listMarker0D.push_back(marker);
			
		}
		
		// Controllare che il numero di marker nulli coincide secondo quanto
		// salvato in MarkerCell0Ds
		unsigned int num = 0;
		for(auto i : mesh.MarkerCell0Ds) {
			num+=(i.second).size();
		}
		
		if(listMarker0D.size() != num)
		{
			cerr << "The number of markers stored for the 0D cells is not correct" << endl;
			return false;
		}
		else
			cout << "The number of markers stored for the 0D cells is correct" << endl;
		
		// Controllare che tutti i marker non nulli siano memorizzati
		// in MarkerCell0Ds
		
		for(unsigned int& m : listMarker0D) {
			auto it = mesh.MarkerCell0Ds.find(m);
			if(it == mesh.MarkerCell0Ds.end())
			{
				cerr << "There is at least one marker for the 0D cells that is not correctly stored" << endl;
				return false;
			}
		}
		
		cout << "All markers for the 0D cells are correctly stored" << endl;
		
		return true;
	}



	bool MarkerTest1D(PolygonalMesh& mesh)
	{
		string FilePathInput = "./Cell1Ds.csv";
		ifstream file(FilePathInput);
		list<string> listLines1D;
		list<unsigned int> listMarker1D;
		string line; 
		
		while (getline(file, line))
			listLines1D.push_back(line);

		file.close();

		// remove header
		listLines1D.pop_front();
		
		for (string& line : listLines1D)
		{
			replace(line.begin(), line.end(), ';', ' ');
			istringstream converter(line);

			unsigned int id;
			unsigned int marker;

			converter >> id >> marker;

			if(marker!=0)
				listMarker1D.push_back(marker);
			
		}
		
		// Controllare che il numero di marker nulli coincide secondo quanto
		// salvato in MarkerCell1Ds
		unsigned int num = 0;
		for(auto i : mesh.MarkerCell1Ds) {
			num+=(i.second).size();
		}
		
		if(listMarker1D.size() != num)
		{
			cerr << "The number of markers stored for the 1D cells is not correct" << endl;
			return false;
		}
		else
			cout << "The number of markers stored for the 1D cells is correct" << endl;
		
		// Controllare che tutti i marker non nulli siano memorizzati
		// in MarkerCell1Ds
		
		for(unsigned int& m : listMarker1D) {
			auto it = mesh.MarkerCell1Ds.find(m);
			if(it == mesh.MarkerCell1Ds.end())
			{
				cerr << "There is at least one marker for the 1D cells that is not correctly stored" << endl;
				return false;
			}
		}
		
		cout << "All markers for the 1D cells are correctly stored" << endl;
		
		return true;
	}
	
	
	
	
	bool MarkerTest2D(PolygonalMesh& mesh)
	{
		string FilePathInput = "./Cell2Ds.csv";
		ifstream file(FilePathInput);
		list<string> listLines2D;
		list<unsigned int> listMarker2D;
		string line; 
		
		while (getline(file, line))
			listLines2D.push_back(line);

		file.close();

		// remove header
		listLines2D.pop_front();
		
		for (string& line : listLines2D)
		{
			replace(line.begin(), line.end(), ';', ' ');
			istringstream converter(line);

			unsigned int id;
			unsigned int marker;

			converter >> id >> marker;

			if(marker!=0)
				listMarker2D.push_back(marker);
			
		}
		
		// Controllare che il numero di marker nulli coincide secondo quanto
		// salvato in MarkerCell2Ds
		unsigned int num = 0;
		for(auto i : mesh.MarkerCell2Ds) {
			num+=(i.second).size();
		}
		
		if(listMarker2D.size() != num)
		{
			cerr << "The number of markers stored for the 2D cells is not correct" << endl;
			return false;
		}
		else
			cout << "The number of markers stored for the 2D cells is correct" << endl;
		
		// Controllare che tutti i marker non nulli siano memorizzati
		// in MarkerCell2Ds
		
		for(unsigned int& m : listMarker2D) {
			auto it = mesh.MarkerCell2Ds.find(m);
			if(it == mesh.MarkerCell2Ds.end())
			{
				cerr << "There is at least one marker for the 2D cells that is not correctly stored" << endl;
				return false;
			}
		}
		
		cout << "All markers for the 2D cells are correctly stored" << endl;
		
		return true;
	}
	
	
	
	
	
	bool SegmentsTest(PolygonalMesh& mesh, const double& tol)
	{
		for(unsigned int id = 0; id < mesh.NumCell1Ds; id++)
		{
			int E1 = mesh.Cell1DsExtrema(0, id);
			int E2 = mesh.Cell1DsExtrema(1, id);
			double x1 = mesh.Cell0DsCoordinates(0, E1);
			double y1 = mesh.Cell0DsCoordinates(1, E1);
			double x2 = mesh.Cell0DsCoordinates(0, E2);
			double y2 = mesh.Cell0DsCoordinates(1, E2);
			double dist = sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
			if(dist < tol) {
				cerr << "There is at least one segment with a lower length than " << tol << endl;
				return false;
			}			
		}
		
		cout << "All segments have a greater length than " << tol << endl;
		return true;
	}
	
	
	
	
	bool AreaTest(PolygonalMesh& mesh, const double& tol)
	{
		// area del triangolo equilatero con l = tol
		double tol_2D = tol*tol*sqrt(3)/4;
		unsigned int NumVertices;
		vector<unsigned int> vertices;
		double xi;
		double yi;
		double xii;
		double yii;
		for(unsigned int id = 0; id < mesh.NumCell2Ds; id++)
		{
			double area = 0;
			double sum = 0;
			NumVertices = mesh.Cell2DsVertices[id].size();
			vertices.resize(NumVertices);
			vertices = mesh.Cell2DsVertices[id];
			
			for(unsigned int i = 0; i < NumVertices-1; i++)
			{
				xi = mesh.Cell0DsCoordinates(0, vertices[i]);
				yi = mesh.Cell0DsCoordinates(1, vertices[i]);
				xii = mesh.Cell0DsCoordinates(0, vertices[i+1]);
				yii = mesh.Cell0DsCoordinates(1, vertices[i+1]);
				sum += (xi*yii - xii*yi);
			}
			
			xi = mesh.Cell0DsCoordinates(0, vertices[NumVertices-1]);
			yi = mesh.Cell0DsCoordinates(1, vertices[NumVertices-1]);
			xii = mesh.Cell0DsCoordinates(0, vertices[0]);
			yii = mesh.Cell0DsCoordinates(1, vertices[0]);
			sum += (xi*yii - xii*yi);
			area = 0.5*abs(sum);
			
			if(area < tol_2D) {
				cerr << "There is at least one polygon with a lower area than " << area << endl;
				return false;
			}
			
		}
		
		cout << "All polygons have a greater area than " << tol_2D << endl;
		return true;
		
	}
	
}