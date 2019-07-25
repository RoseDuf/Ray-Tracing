#ifndef MESH_HPP_
#define MESH_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include <memory>
#include "Object.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Mesh : public Object {

public:

	Mesh();
	Mesh(string file, 
		std::vector<int> indices,
		std::vector<glm::vec3> vertices,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> UVs);
	~Mesh();

	const char * getFile();
	void setFile(string file);

	void setIndices(std::vector<int> indices);
	std::vector<int> getIndices();

	void setVertices(std::vector<glm::vec3> vertices);
	std::vector<glm::vec3> getVertices();

	void setNormals(std::vector<glm::vec3> normals);
	std::vector<glm::vec3> getNormals();

	void setUVs(std::vector<glm::vec2> UVs);
	std::vector<glm::vec2> getUVs();

private:
	string file; //where filename.obj is the OBJ file containing the mesh
	//const char * file; //where filename.obj is the OBJ file containing the mesh
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
};

#endif
