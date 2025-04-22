#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace PolygonalLibrary
{
	


bool ImportMesh(PolygonalMesh& mesh)
{
    
    if(!ImportCell0Ds(mesh))
        return false;

    if(!ImportCell1Ds(mesh))
        return false;

    if(!ImportCell2Ds(mesh))
        return false;

    return true;
	
}




// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
	string FilePathInput = "./Cell0Ds.csv";
	ifstream file(FilePathInput);
	list<string> listLines;

	if(file.fail()) {
		return false;
	}
	
	string line;
	while (getline(file, line))
		listLines.push_back(line);
	
	file.close();

	// remove header
	listLines.pop_front();

	mesh.NumCell0Ds = listLines.size();

	
	if (mesh.NumCell0Ds == 0)
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
    mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);

    for (string& line : listLines)
    {
		replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;

        converter >> id >> marker >> mesh.Cell0DsCoordinates(0, id) >> mesh.Cell0DsCoordinates(1, id);
        mesh.Cell0DsId.push_back(id);

		// memorizza i marker
		if(marker!=0)
		{
			auto it = mesh.MarkerCell0Ds.find(marker);
			if(it!=mesh.MarkerCell0Ds.end())
			{
				//mesh.MarkerCell0Ds[marker].push_back(id);
				((*it).second).push_back(id);
			}
			else {
				mesh.MarkerCell0Ds.insert({marker, {id}});
			}
		}

    }
	
    return true;
}





bool ImportCell1Ds(PolygonalMesh& mesh)
{
	string FilePathInput = "./Cell1Ds.csv";
	ifstream file(FilePathInput);
	list<string> listLines;

    if(file.fail())
        return false;
	
	else
	{
		string line;
		while (getline(file, line))
			listLines.push_back(line);

		// remove header
		listLines.pop_front();

		mesh.NumCell1Ds = listLines.size();
		file.close();
	}
	
	if (mesh.NumCell1Ds == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DsId.reserve(mesh.NumCell1Ds);
    mesh.Cell1DsExtrema = Eigen::MatrixXi(2, mesh.NumCell1Ds);

    for (string& line : listLines)
    {
		replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;

        converter >> id >> marker >> mesh.Cell1DsExtrema(0, id) >>  mesh.Cell1DsExtrema(1, id);
        mesh.Cell1DsId.push_back(id);

        //memorizza i marker
		if(marker!=0)
		{
			auto it = mesh.MarkerCell1Ds.find(marker);
			if(it != mesh.MarkerCell1Ds.end())
			{
				mesh.MarkerCell1Ds[marker].push_back(id);
				// (*it).second.push_back(id);
			}
			else
				mesh.MarkerCell1Ds.insert({marker, {id}});
		}
    }

    return true;
	
}






// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
	string FilePathInput = "./Cell2Ds.csv";
	ifstream file(FilePathInput);
	list<string> listLines;

    if(file.fail())
        return false;
	
	else
	{
		string line;
		while (getline(file, line))
			listLines.push_back(line);

		// remove header
		listLines.pop_front();

		mesh.NumCell2Ds = listLines.size();
		file.close();
	}
	
	if (mesh.NumCell2Ds == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DsId.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsVertices.reserve(mesh.NumCell2Ds);
    mesh.Cell2DsEdges.reserve(mesh.NumCell2Ds);

    for (string& line : listLines)
    {
		replace(line.begin(), line.end(), ';', ' ');
        istringstream converter(line);

        unsigned int id;
		unsigned int marker;
		unsigned int NumVertices;
		unsigned int NumEdges;
        vector<unsigned int> vertices;
        vector<unsigned int> edges;

        converter >> id >> marker >> NumVertices;
		
		if(NumVertices < 3) {
			cerr << "Not enough vertices to make a non-degenerate polygon" << endl;
			return false;
		}
		
		vertices.resize(NumVertices);
        for(unsigned int i = 0; i < NumVertices; i++) {
            converter >> vertices[i];
		}
		
		converter >> NumEdges;
		
		if(NumEdges < 3) {
			cerr << "Not enough edges to make a non-degenerate polygon" << endl;
			return false;
		}
		
		edges.resize(NumEdges);
        for(unsigned int i = 0; i < NumEdges; i++)
            converter >> edges[i];

        mesh.Cell2DsId.push_back(id);
        mesh.Cell2DsVertices.push_back(vertices);
        mesh.Cell2DsEdges.push_back(edges);
		
		//memorizza i marker
		if(marker!=0)
		{
			auto it = mesh.MarkerCell2Ds.find(marker);
			if(it != mesh.MarkerCell2Ds.end())
			{
				mesh.MarkerCell2Ds[marker].push_back(id);
				// (*it).second.push_back(id);
			}
			else
				mesh.MarkerCell2Ds.insert({marker, {id}});
		}
    }
	
	return true;
}

}