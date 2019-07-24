
#include "Mesh.h"

Mesh::Mesh() {
	file = "";
	vertices = {};
	normals = {};
	UVs = {};
}
Mesh::Mesh(const char * _file, int nfaces,
	unique_ptr<int[]> &faceIndex,
	unique_ptr<int[]> &vertsIndex,
	std::vector<glm::vec3> _vertices,
	std::vector<glm::vec3> _normals,
	std::vector<glm::vec2> _UVs) :
	numTris(0) {

	file = _file;
	std::vector<glm::vec3> vertices = _vertices;
	std::vector<glm::vec3> normals = _normals;
	std::vector<glm::vec2> UVs = UVs;

	//source: http://www.scratchapixel.com/code.php?id=11&origin=/lessons/3d-basic-rendering/ray-tracing-polygon-mesh
	int k = 0, maxVertIndex = 0;
	// find out how many triangles we need to create for this mesh
	for (int i = 0; i < nfaces; i++) {
		numTris += faceIndex[i] - 2;
		for (int j = 0; j < faceIndex[i]; ++j)
			if (vertsIndex[k + j] > maxVertIndex)
				maxVertIndex = vertsIndex[k + j];
		k += faceIndex[i];
	}
	maxVertIndex += 1;

	// allocate memory to store the position of the mesh vertices
	P = unique_ptr<glm::vec3[]>(new glm::vec3[maxVertIndex]);
	for (int i = 0; i < maxVertIndex; ++i) {
		P[i] = vertices[i];
	}

	// allocate memory to store triangle indices
	trisIndex = unique_ptr<int[]>(new int[numTris * 3]);
	int l = 0;

	N = unique_ptr<glm::vec3[]>(new glm::vec3[numTris * 3]);
	texCoordinates = unique_ptr<glm::vec2[]>(new glm::vec2[numTris * 3]);
	for (uint32_t i = 0, k = 0; i < nfaces; ++i) { // for each face
		for (uint32_t j = 0; j < faceIndex[i] - 2; ++j) { // for each triangle in the face
			trisIndex[l] = vertsIndex[k];
			trisIndex[l + 1] = vertsIndex[k + j + 1];
			trisIndex[l + 2] = vertsIndex[k + j + 2];
			N[l] = normals[k];
			N[l + 1] = normals[k + j + 1];
			N[l + 2] = normals[k + j + 2];
			texCoordinates[l] = UVs[k];
			texCoordinates[l + 1] = UVs[k + j + 1];
			texCoordinates[l + 2] = UVs[k + j + 2];
			l += 3;
		}
		k += faceIndex[i];
	}
	// you can use move if the input geometry is already triangulated
	//N = std::move(normals); // transfer ownership
	//sts = std::move(st); // transfer ownership
}

Mesh::~Mesh() {}

const char * Mesh::getFile() {
	return file.c_str(); //need to do conversion inside this function or else pointer will lose information on the string
	//very weird
}
void Mesh::setFile(string _file) {
	file = _file;
}

//not sure what the normal is yet
glm::vec3 Mesh::getNormal(glm::vec3 phit) {
	return normals[0];
}

//glm::vec3 Mesh::getAmb() {
//	return amb;
//}
//void Mesh::setAmb(glm::vec3 _amb) {
//	amb = _amb;
//}
//
//glm::vec3 Mesh::getDif() {
//	return dif;
//}
//void Mesh::setDif(glm::vec3 _dif) {
//	dif = _dif;
//}
//
//glm::vec3 Mesh::getSpe() {
//	return spe;
//}
//void Mesh::setSpe(glm::vec3 _spe) {
//	spe = _spe;
//}
//
//float Mesh::getShi() {
//	return shi;
//}
//void Mesh::setShi(float _shi) {
//	shi = _shi;
//}