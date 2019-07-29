#include "Mesh.h"

#define INFINITY 1e8

Mesh::Mesh() {
	file = "";
	indices = {};
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

glm::vec3 Mesh::getNormal(glm::vec3 &, int triIndex)
{

	// face normals
	glm::vec3 &v0 = vertices[indices[triIndex * 3]];
	glm::vec3 &v1 = vertices[indices[triIndex * 3 + 1]];
	glm::vec3 &v2 = vertices[indices[triIndex * 3 + 2]];
	glm::vec3 hitNormal = glm::cross(v1 - v0, v2 - v0);

	return glm::normalize(hitNormal);
}
void Mesh::setNormal(glm::vec3 _nor) {
	nor = _nor;
}

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
bool Mesh::intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &tNear, int index) {
	
	//calculating the intersection of a specific triangle
	int j = 0;
	bool intersect = false;
	int numTris = this->indices.size() / 3;
	for (uint32_t i = 0; i < numTris; ++i) {
		const glm::vec3 &v0 = this->vertices[this->indices[j]];
		const glm::vec3 &v1 = this->vertices[this->indices[j + 1]];
		const glm::vec3 &v2 = this->vertices[this->indices[j + 2]];
		float t = INFINITY;
		float u;
		float v;
		if (rayTriangleIntersect(rayorig, raydir, v0, v1, v2, t) && t < tNear) {
			//if it intersects set the triangles's index to the intersection index 
			//and tNear to the intersection distance
			tNear = t;
			index = i;
			//set intersection to true
			intersect = true;
		}
		j += 3;
	}

	return intersect;
}

//bool Mesh::rayTriangleIntersect(
//	const glm::vec3 &orig, const glm::vec3 &dir,
//	const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, float &t) {
//
//	float u, v;
//
//	// compute plane's normal
//	glm::vec3 v0v1 = v1 - v0;
//	glm::vec3 v0v2 = v2 - v0;
//	// no need to normalize
//	glm::vec3 N = glm::cross(v0v1, v0v2); // N 
//	this->setNormal(N);
//	float denom = glm::dot(N, N);
//
//	// Step 1: finding P
//
//	// check if ray and plane are parallel ?
//	float NdotRayDirection = glm::dot(N, dir);
//	//check if normal is perpendicular to ray
//	if (fabs(NdotRayDirection) < 1e-6) // almost 0 
//		return false; // they are parallel so they don't intersect ! 
//
//	// compute d parameter using equation 2
//	float d = glm::dot(N, v0);
//
//	// compute t (equation 3)
//	t = (glm::dot(N, orig) + d) / NdotRayDirection;
//
//	// check if the triangle is in behind the ray
//	if (t < 0) 
//		return false; // the triangle is behind 
//
//	// compute the intersection point using equation 1
//	glm::vec3 P = orig + t * dir;
//
//	// Step 2: inside-outside test
//	glm::vec3 C; // vector perpendicular to triangle's plane 
//
//	// edge 0
//	glm::vec3 edge0 = v1 - v0;
//	glm::vec3 vp0 = P - v0;
//	C = glm::cross(edge0, vp0);
//	if (glm::dot(N, C) < 0) 
//		return false; // P is on the right side 
//
//	// edge 1
//	glm::vec3 edge1 = v2 - v1;
//	glm::vec3 vp1 = P - v1;
//	C = glm::cross(edge1, vp1);
//	if (glm::dot(N, C) < 0)  
//		return false; // P is on the right side 
//
//	// edge 2
//	glm::vec3 edge2 = v0 - v2;
//	glm::vec3 vp2 = P - v2;
//	C = glm::cross(edge2, vp2);
//	if (glm::dot(N, C) < 0) 
//		return false; // P is on the right side; 
//
//	u /= denom;
//	v /= denom;
//
//	return true; // this ray hits the triangle 
//}

//Möller-Trumbore algorithm
bool Mesh::rayTriangleIntersect(const glm::vec3 &rayorig, const glm::vec3 &raydir,
	const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2, float &t) {
	
	float u, v;
	// compute plane's (triangle's) normal
	glm::vec3 v0v1 = v1 - v0;
	glm::vec3 v0v2 = v2 - v0;
	glm::vec3 perpVec = glm::cross(raydir, v0v2); //check if cross is in right order if errors
	float determinant = glm::dot(v0v1, perpVec);

	//glm::vec3 N = glm::cross(v0v1, v0v2); // N 
	//this->setNormal(N);

	// if the determinant is negative the triangle is backfacing
	// if the determinant is close to 0, the ray misses the triangle
	if (determinant < 1e-8) 
		return false;

	// ray and triangle are parallel if deterteminant is close to 0 
	/*if (fabs(determinant) < 1e-8) 
		return false;*/
	if (glm::dot(raydir, normalize(glm::cross(v0v1, v0v2))) > 0)
		return false;

	float invDet = 1 / determinant;

	glm::vec3 tvec = rayorig - v0; // t is distance from the ray origin O to P
	u = glm::dot(tvec, perpVec) * invDet;

	if (u < 0 || u > 1) 
		return false;

	glm::vec3 qvec = glm::cross(tvec, v0v1); //check if cross is in right order if errors
	v = glm::dot(raydir, qvec) * invDet; 

	if (v < 0 || u + v > 1)
		return false;

	t = glm::dot(v0v2, qvec) * invDet; 

	return true;
}