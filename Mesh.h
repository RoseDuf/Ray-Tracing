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

	glm::vec3 getNormal();
	void setNormal(glm::vec3 _nor);

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

	bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &tNear, int index, glm::vec2 UV);

	bool rayTriangleIntersect(
		const glm::vec3 &orig, const glm::vec3 &dir,
		const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2,
		float &t, float &u, float &v);

	//bool rayTriangleIntersect(const glm::vec3 &rayorig, const glm::vec3 &raydir,
	//	const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2,
	//	float &t, float &u, float &v);

private:
	string file; //where filename.obj is the OBJ file containing the mesh
	//const char * file; //where filename.obj is the OBJ file containing the mesh
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;
	glm::vec3 nor;
};

#endif
