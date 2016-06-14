//============================================================================
// Name        : VR.cpp
// Author      : Ramesh
// Version     :
// Copyright   : Your copyright notice
// Description : C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

//Model structure
typedef struct Model
{
    int verticies;
    int positions;
    int texels;
    int normals;
    int faces;

    Model()
    {
    	verticies = 0;
    	positions = 0;
    	texels = 0;
    	normals = 0;
    	faces = 0;
    }
}Model;

//Get the OBJ info
Model GetOBJInfo(string value)
{
	cout << "Get OBJ Info \n" << endl;

    Model model;

    //input stream to open the file
    ifstream stream;
    stream.open(value);

    //Check whether the file is corrupt or not
    if(!stream.good())
    {
        cout << "File is corrupt or some error opening the OBJ file";
        exit(1);
    }

    //Parse through the file and get the number of vertices, normals, faces and so on
    while(!stream.eof())
    {
        string line;
        getline(stream, line);
        string type = line.substr(0, 2);

        if(type.compare("v ") == 0)
            model.positions++;
        else if(type.compare("vt") == 0)
            model.texels++;
        else if(type.compare("vn") == 0)
            model.normals++;
        else if(type.compare("f ") == 0)
            model.faces++;
    }

    model.verticies = model.faces * 3;

    stream.close();

    return model;
}

//Get the obj Data
void GetOBJData(string file, float positions[][3], float texels[][2], float normals[][3], int faces[][6])
{
	cout << "Get OBJ data \n" << endl;

    int pCount, tCount, nCount, fCount = 0;

    ifstream stream;
    stream.open(file);

    if(!stream.good())
    {
        cout << "File is corrupt or some error opening the OBJ file";
        exit(1);
    }

    //Parse through the file and get the number of vertices, normals, faces and so on
    while(!stream.eof())
    {
        string line;
        getline(stream, line);
        string type = line.substr(0, 2);

        if(type.compare("v ") == 0 && positions != NULL)
        {
            //Copy the entire line
            char* l = new char[line.size() + 1];
            memcpy(l, line.c_str(), line.size() + 1);

            strtok(l, " ");
            for(int i = 0; i < 3; i++)
                positions[pCount][i] = atof(strtok(NULL, " "));

            //deallocate the memory
            delete[] l;
            pCount++;
        }

        else if(type.compare("vt") == 0 && texels != NULL)
        {
        	//Copy the entire line
			char* l = new char[line.size() + 1];
			memcpy(l, line.c_str(), line.size() + 1);

			strtok(l, " ");
			for(int i = 0; i < 2; i++)
				texels[tCount][i] = atof(strtok(NULL, " "));

			//deallocate the memory
			delete[] l;
			tCount++;
        }

        else if(type.compare("vn") == 0 && normals != NULL)
        {
            //Copy the entire line
            char* l = new char[line.size() + 1];
            memcpy(l, line.c_str(), line.size() + 1);

            strtok(l, " ");
            for(int i = 0; i < 3; i++)
                normals[nCount][i] = atof(strtok(NULL, " "));

            //deallocate the memory
            delete[] l;
            nCount++;
        }

        else if(type.compare("f ") == 0 && faces != NULL)
        {
            //Copy the entire line
            char* l = new char[line.size() + 1];
            memcpy(l, line.c_str(), line.size() + 1);

            strtok(l, " ");
            for(int i = 0; i < 6; i++)
                faces[fCount][i] = atof(strtok(NULL, " //"));

            //deallocate the memory
            delete[] l;
            fCount++;
        }
    }

    stream.close();

}

int main(int argc, const char * argv[])
{
    int fileCounter = 0;

    // insert code here...
    cout << "Hello, World!\n";
    cout << argc << endl;
    cout << argv[0] << endl; //Inline argument for file path
    cout << argv[1] << endl; //Inline argument for file name
    cout <<"\n" <<endl;

    //Creating file setup
    string name = argv[1];
    string fileOBJPath = "source/" + name + ".obj";
    string fileHeaderPath = "product/" + name + ".h";
    string fileClassPath = "product/" + name + ".c";

    Model model = GetOBJInfo(fileOBJPath);
    Model tempModel;
    fileCounter++;

    //check to see the numbers
    cout << "OBJ Info" << endl;
    cout << "Positions: " << model.positions << endl;
    cout << "Texels: " << model.texels << endl;
    cout << "Normals: " << model.normals << endl;
    cout << "Faces: " << model.faces << endl;
    cout << "Vertices: " << model.verticies << endl;
    cout <<"\n" <<endl;

    //delcare the arrary based on the model data
    if(model.positions != 0 && model.texels != 0 && model.normals != 0 && model.faces != 0 && model.verticies != 0)
    {
    	cout << "Got all data \n" << endl;

    	float positions[model.positions][3]; //each coordinate in XYZ space
    	float texels[model.texels][2]; //UV coordinates
    	float normals[model.normals][3]; //normal vector
    	int faces[model.faces][6];

    	GetOBJData(fileOBJPath, positions, texels, normals, faces);

        //Check to see correctness of the data -- Checking the first entry
        cout << "Model Data" << endl;
        cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
        cout << "Texels: " << texels[0][0] << "u " << texels[0][1] << "v " << endl;
        cout << "Normals: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << endl;
        cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
        cout <<"\n" <<endl;
    }
    else if(model.positions != 0 && model.texels != 0 && model.faces != 0)
    {
    	cout << "Missing normals \n" << endl;

    	float positions[model.positions][3]; //each coordinate in XYZ space
    	float texels[model.texels][2]; //UV coordinates
    	int faces[model.faces][6];

    	GetOBJData(fileOBJPath, positions, texels, NULL, faces);

    	//Check to see correctness of the data -- Checking the first entry
		cout << "Model Data" << endl;
		cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
		cout << "Texels: " << texels[0][0] << "u " << texels[0][1] << "v " << endl;
		cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
		cout <<"\n" <<endl;
    }
    else if(model.positions != 0 && model.normals != 0 && model.faces != 0)
    {
    	cout << "Missing texels \n" << endl;

    	float positions[model.positions][3]; //each coordinate in XYZ space
		float normals[model.normals][3]; //normal vector
		int faces[model.faces][6]; //faces

		GetOBJData(fileOBJPath, positions, NULL, normals, faces);

		//Check to see correctness of the data -- Checking the first entry
		cout << "Model Data" << endl;
		cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
		cout << "Normals: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << endl;
		cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
		cout <<"\n" <<endl;
    }

    return 0;
}

