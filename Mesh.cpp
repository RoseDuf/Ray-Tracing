#include "Mesh.h"

#define INFINITY 1e8

Mesh::Mesh() {
	file = "";
	vertices = {};
	normals = {};
	UVs = {};
}
Mesh::Mesh(string _file,
	std::vector<int> _indices,
	std::vector<glm::vec3> _vertices,
	std::vector<glm::vec3> _normals,
	std::vector<glm::vec2> _UVs) {

	file = _file;
	indices = _indices;
	vertices = _vertices;
	normals = _normals;
	UVs = _UVs;
}

Mesh::~Mesh() {}

const char * Mesh::getFile() {
	return file.c_str(); //need to do conversion inside this function or else pointer will lose information on the string
	//very weird
}
void Mesh::setFile(string _file) {
	file = _file;
}

void Mesh::setIndices(std::vector<int> _indices) {
	indices = _indices;
}
std::vector<int> Mesh::getIndices() {
	return indices;
}

void Mesh::setVertices(std::vector<glm::vec3> _vertices) {
	vertices = _vertices;
}
std::vector<glm::vec3> Mesh::getVertices() {
	return vertices;
}

void Mesh::setNormals(std::vector<glm::vec3> _normals) {
	normals = _normals;
}
std::vector<glm::vec3> Mesh::getNormals() {
	return normals;
}

void Mesh::setUVs(std::vector<glm::vec2> _UVs) {
	UVs = _UVs;
}
std::vector<glm::vec2> Mesh::getUVs() {
	return UVs;
}

//decifer this
bool Mesh::intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &tNear, int index, glm::vec2 UV) {
	int j = 0;
	bool isect = false;
	for (uint32_t i = 0; i < indices.size()/3; ++i) {
		const glm::vec3 &v0 = vertices[indices[j]];
		const glm::vec3 &v1 = vertices[indices[j + 1]];
		const glm::vec3 &v2 = vertices[indices[j + 2]];
		float t = INFINITY;
		float u;
		float v;
		if (rayTriangleIntersect(rayorig, raydir, v0, v1, v2, t, u, v) && t < tNear) {
			tNear = t;
			UV.x = u;
			UV.y = v;
			index = i;
			isect = true;
		}
		j += 3;
	}

	return isect;
}


//Möller-Trumbore algorithm
bool Mesh::rayTriangleIntersect(const glm::vec3 &rayorig, const glm::vec3 &raydir,
	const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2,
	float &t, float &u, float &v) {
	
	// compute plane's (triangle's) normal
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 normalVec = glm::cross(raydir, v0v2); //check if cross is in right order if errors
	float determinant = glm::dot(v0v1, normalVec);

	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (determinant < 1e-6) return false;

	// ray and triangle are parallel if deterteminant is close to 0 
	if (fabs(determinant) < 1e-6) 
		return false;

	float invDet = 1 / determinant;

	glm::vec3 tvec = rayorig - v0; // t is distance from the ray origin O to P
	u = glm::dot(tvec, normalVec) * invDet;

	if (u < 0 || u > 1) 
		return false;

	glm::vec3 qvec = glm::cross(tvec, v0v1); //check if cross is in right order if errors
	v = glm::dot(raydir, qvec) * invDet; 

	if (v < 0 || u + v > 1)
		return false;

	t = glm::dot(v0v2, qvec) * invDet; 

	return true;
}