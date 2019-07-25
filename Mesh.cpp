#include "Mesh.h"

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