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
	cout << "Get OBJ Info for " << value << endl;

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
void GetOBJData(string file, float** positions, float** texels, float** normals, int** faces, Model model)
{
	cout << "Get OBJ data for " << file << endl;

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

        if(type.compare("v ") == 0 && positions != NULL && pCount < model.positions)
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

        else if(type.compare("vt") == 0 && texels != NULL && tCount < model.texels)
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

        else if(type.compare("vn") == 0 && normals != NULL && nCount < model.normals)
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

        else if(type.compare("f ") == 0 && faces != NULL && fCount < model.faces)
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

    bool isPositions, isTexels, isNormals, isFaces = false;

    //AFib1 arrays
    float** AFib1_Positions;
    float** AFib1_Texels; 
    float** AFib1_Normals;
    int** AFib1_Faces;

    //AFib2 Arrays
    float** AFib2_Positions;
    float** AFib2_Texels;
    float** AFib2_Normals;
    int** AFib2_Faces;

    //AFib3 Arrays
    float** AFib3_Positions;
    float** AFib3_Texels;
    float** AFib3_Normals;
    int** AFib3_Faces;
     

    //Creating file setup
    string sourceNames[] = {"AFib1", "AFib2", "AFib3"};
    string name, fileOBJPath;

    while(fileCounter < 3)
    {
        name = sourceNames[fileCounter];
        fileOBJPath = "source/" + name + ".obj";

        Model model = GetOBJInfo(fileOBJPath);

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
            isPositions, isTexels, isNormals, isFaces = true;

        	cout << "Got all data \n" << endl;

            float** positions = new float*[model.positions]; //each coordinate in XYZ space
            for(int i = 0; i < model.positions; i++)
            {
                positions[i] = new float[3];
                for(int j = 0; j < 3; j++)
                {
                    positions[i][j] = rand() % (9 - 0 + 1) + 0;
                }

            }

            float** texels = new float*[model.texels]; //UV coordinates
            for(int i = 0; i < model.texels; i++)
            {
                texels[i] = new float[2];
                for(int j = 0; j < 2; j++)
                {
                    texels[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

            float** normals = new float*[model.normals]; //normal vector
            for(int i = 0; i < model.normals; i++)
            {
                normals[i] = new float[3];
                for(int j = 0; j < 3; j++)
                {
                    normals[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

            int** faces = new int*[model.faces];
            for(int i = 0; i < model.faces; i++)
            {
                faces[i] = new int[6];
                for(int j = 0; j < 6; j++)
                {
                    faces[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

        	GetOBJData(fileOBJPath, positions, texels, normals, faces, model); 

            //Check to see correctness of the data -- Checking the first entry
            cout << "Model Data" << endl;
            cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
            cout << "Texels: " << texels[0][0] << "u " << texels[0][1] << "v " << endl;
            cout << "Normals: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << endl;
            cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
            cout <<"\n" <<endl;

            //Assign values to the global arrays to compute average coordinates
            if(name == "AFib1")
            {
                AFib1_Positions = positions;
                AFib1_Texels = texels;
                AFib1_Normals = normals;
                AFib1_Faces = faces;
            }
            else if(name == "AFib2")
            {
                AFib2_Positions = positions;
                AFib2_Texels = texels;
                AFib2_Normals = normals;
                AFib2_Faces = faces;
            }
            else if(name == "AFib3")
            {
                AFib3_Positions = positions;
                AFib3_Texels = texels;
                AFib3_Normals = normals;
                AFib3_Faces = faces;
            }

            //Deallocate the memory spaces
            for(int i = 0; i < model.positions; i++)
            {
                delete[] positions[i];
            }
            delete[] positions;

            for(int i = 0; i < model.texels; i++)
            {
                delete[] texels[i];
            }
            delete[] texels;

            for(int i = 0; i < model.normals; i++)
            {
                delete[] normals[i];
            }
            delete[] normals;

            for(int i = 0; i < model.faces; i++)
            {
                delete[] faces[i];
            }
            delete[] faces;
        }
        else if(model.positions != 0 && model.texels != 0 && model.faces != 0)
        {
            isPositions, isTexels, isFaces = true;

        	cout << "Missing normals \n" << endl;

            float** positions = new float*[model.positions]; //each coordinate in XYZ space
            for(int i = 0; i < model.positions; i++)
            {
                positions[i] = new float[3];
                for(int j = 0; j < 3; j++)
                {
                    positions[i][j] = rand() % (9 - 0 + 1) + 0;
                }

            }

        	float** texels = new float*[model.texels]; //UV coordinates
            for(int i = 0; i < model.texels; i++)
            {
                texels[i] = new float[2];
                for(int j = 0; j < 2; j++)
                {
                    texels[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

        	int** faces = new int*[model.faces];
            for(int i = 0; i < model.faces; i++)
            {
                faces[i] = new int[6];
                for(int j = 0; j < 6; j++)
                {
                    faces[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

        	GetOBJData(fileOBJPath, positions, texels, NULL, faces, model);

        	//Check to see correctness of the data -- Checking the first entry
    		cout << "Model Data" << endl;
    		cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
    		cout << "Texels: " << texels[0][0] << "u " << texels[0][1] << "v " << endl;
    		cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
    		cout <<"\n" <<endl;

            //Assign values to the global arrays to compute average coordinates
            if(name == "AFib1")
            {
                AFib1_Positions = positions;
                AFib1_Texels = texels;
                AFib1_Faces = faces;
            }
            else if(name == "AFib2")
            {
                AFib2_Positions = positions;
                AFib2_Texels = texels;
                AFib2_Faces = faces;
            }
            else if(name == "AFib3")
            {
                AFib3_Positions = positions;
                AFib3_Texels = texels;
                AFib3_Faces = faces;
            }


            //Deallocate the memory spaces
            for(int i = 0; i < model.positions; i++)
            {
                delete[] positions[i];
            }
            delete[] positions;

            for(int i = 0; i < model.texels; i++)
            {
                delete[] texels[i];
            }
            delete[] texels;

            for(int i = 0; i < model.faces; i++)
            {
                delete[] faces[i];
            }
            delete[] faces;

        }
        else if(model.positions != 0 && model.normals != 0 && model.faces != 0)
        {
            isPositions, isNormals, isFaces = true;

        	cout << "Missing texels \n" << endl;

            float** positions = new float*[model.positions]; //each coordinate in XYZ space
            for(int i = 0; i < model.positions; i++)
            {
                positions[i] = new float[3];
                for(int j = 0; j < 3; j++)
                {
                    positions[i][j] = rand() % (9 - 0 + 1) + 0;
                }

            }

            float** normals = new float*[model.normals]; //normal vector
            for(int i = 0; i < model.normals; i++)
            {
                normals[i] = new float[3];
                for(int j = 0; j < 3; j++)
                {
                    normals[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

            int** faces = new int*[model.faces];
            for(int i = 0; i < model.faces; i++)
            {
                faces[i] = new int[6];
                for(int j = 0; j < 6; j++)
                {
                    faces[i][j] = rand() % (9 - 0 + 1) + 0;
                }
            }

    		GetOBJData(fileOBJPath, positions, NULL, normals, faces, model); 

    		//Check to see correctness of the data -- Checking the first entry
    		cout << "Model Data" << endl;
    		cout << "Position: " << positions[0][0] << "x " << positions[0][1] << "y " << positions[0][2] << "z" << endl;
    		cout << "Normals: " << normals[0][0] << "x " << normals[0][1] << "y " << normals[0][2] << "z" << endl;
    		cout << "Faces: "<< faces[0][0] << "p " << faces[0][1] << "t " << faces[0][2] << "n" << endl;
    		cout <<"\n" <<endl;

            //Assign values to the global arrays to compute average coordinates
            if(name == "AFib1")
            {
                AFib1_Positions = positions;
                AFib1_Normals = normals;
                AFib1_Faces = faces;
            }
            else if(name == "AFib2")
            {
                AFib2_Positions = positions;
                AFib2_Normals = normals;
                AFib2_Faces = faces;
            }
            else if(name == "AFib3")
            {
                AFib3_Positions = positions;
                AFib3_Normals = normals;
                AFib3_Faces = faces;
            }

            //Deallocate the memory spaces
            for(int i = 0; i < model.positions; i++)
            {
                delete[] positions[i];
            }
            delete[] positions;

            for(int i = 0; i < model.normals; i++)
            {
                delete[] normals[i];
            }
            delete[] normals;

            for(int i = 0; i < model.faces; i++)
            {
                delete[] faces[i];
            }
            delete[] faces;
        }
        fileCounter++;
    }

    return 0;
}

