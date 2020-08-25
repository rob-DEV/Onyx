#include "onyxpch.h"
#include "ModelLoader.h"

#include <Onyx/Core/FileIO.h>

#include <fstream>
#include <sstream>
#include <map>

namespace Onyx {


	Model* ModelLoader::LoadFromFile(const std::string& path)
	{
		//Determine model type to load

		std::string ext = FileIO::GetFileExtension(path);

		if (ext == "obj")
			return LoadObjFromFile(path);
		if (ext == "fbx")
			return LoadFbxFromFile(path);


		assert(false, "Unsupported model format!");
		return nullptr;
	}

	Model* ModelLoader::LoadObjFromFile(const std::string& path)
	{
		//Load obj - objects can models have multiple meshes
		Model* model = new Model();
		
		std::vector<InternalMesh>* internalMeshes = new std::vector<InternalMesh>();
	
		std::ifstream fileStream(path);
		std::string line = "";
		std::stringstream ss;

		InternalMesh* currentMesh = nullptr;

		if (fileStream.is_open()) {

			while (std::getline(fileStream, line)) {

				ss.clear();
				ss.str(line);
				//get "o" prefix for current mesh
				std::string prefix;
				ss >> prefix;

				//Mesh found add to model meshes
				if (prefix == "o") {
					internalMeshes->push_back(InternalMesh());
					currentMesh = &internalMeshes->back();
				}

				if (prefix == "v") {
					glm::vec3 vertex;
					ss >> vertex.x >> vertex.y >> vertex.z;
					currentMesh->vertices.push_back(vertex);
				}

				if (prefix == "vt") {
					glm::vec2 textureCoord;
					ss >> textureCoord.x >> textureCoord.y;
					currentMesh->texCoord.push_back(textureCoord);
				}

				if (prefix == "vn") {
					glm::vec3 normal;
					ss >> normal.x >> normal.y >> normal.z;
					currentMesh->normals.push_back(normal);
				}


				if (prefix == "f") {
					//f 5/1/1 3/2/1 1/3/1   - obj data
					//  v/t/n v/t/n v/t/n   - type of data
					//  0/1/2               - counter
					uint32_t temp = -1;
					uint32_t counter = 0;
					while (ss >> temp) {

						if (counter == 0)
							currentMesh->vertexIndices.push_back(temp);
						else if (counter == 1)
							currentMesh->texCoordIndices.push_back(temp);
						else if (counter == 2)
							currentMesh->normalIndices.push_back(temp);

						if (ss.peek() == '/') {
							++counter;
							ss.ignore(1, '/');
						}
						else if (ss.peek() == ' ') {
							++counter;
							ss.ignore(1, ' ');
						}

						if (counter > 2)
							counter = 0;
					}


				}




			}

			///POST IMPORT PROCESSING
			//For each internal mesh convert to an optimized renderer friendly version

		
			



		}
		else {
			printf("Failed to open OBJ file!\n");
			return nullptr;
		}

		

		return model;
	}

	Model* ModelLoader::LoadFbxFromFile(const std::string& path)
	{
		return nullptr;
	}

}