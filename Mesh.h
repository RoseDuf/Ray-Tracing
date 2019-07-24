#ifndef MESH_HPP_
#define MESH_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include <memory>
#include "objloaderIndex.h"
#include "Object.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Mesh : public Object {

public:

	Mesh();
	Mesh(const char * faces, int nfaces,
		unique_ptr<int[]> &faceIndex,
		unique_ptr<int[]> &vertsIndex,
		std::vector<glm::vec3> vertices,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> UVs);
	~Mesh();

	const char * getFile();
	void setFile(string file);

	/*glm::vec3 getAmb();
	void setAmb(glm::vec3 amb);

	glm::vec3 getDif();
	void setDif(glm::vec3 dif);

	glm::vec3 getSpe();
	void setSpe(glm::vec3 spe);

	float getShi();
	void setShi(float shi);*/

	glm::vec3 getNormal(glm::vec3 phit);

	/*float objectLoaded(char * file) {
		std::vector<int> indices;
		std::vector<glm::vec3> vertices;
		std::vector<glm::vec3> normals;
		std::vector<glm::vec2> UVs;
		loadOBJ(file, indices, vertices, normals, UVs);
	}*/


	//ATTEMPTED computation of mesh intersections and trace
	//source: http://www.scratchapixel.com/code.php?id=11&origin=/lessons/3d-basic-rendering/ray-tracing-polygon-mesh
	void getSurfaceProperties(
		const glm::vec3 &hitPoint,
		const glm::vec3 &viewDirection,
		const int &triIndex,
		const glm::vec2 &uv,
		glm::vec3 &hitNormal,
		glm::vec2 &hitTextureCoordinates) const
	{
		// face normal
		const glm::vec3 &v0 = P[trisIndex[triIndex * 3]];
		const glm::vec3 &v1 = P[trisIndex[triIndex * 3 + 1]];
		const glm::vec3 &v2 = P[trisIndex[triIndex * 3 + 2]];
		hitNormal = glm::normalize(glm::cross((v1 - v0), (v2 - v0)));

		// texture coordinates
		const glm::vec2 &st0 = texCoordinates[triIndex * 3];
		const glm::vec2 &st1 = texCoordinates[triIndex * 3 + 1];
		const glm::vec2 &st2 = texCoordinates[triIndex * 3 + 2];
		hitTextureCoordinates = (1 - uv.x - uv.y) * st0 + uv.x * st1 + uv.y * st2;

		// vertex normal
		/*
		const Vec3f &n0 = N[triIndex * 3];
		const Vec3f &n1 = N[triIndex * 3 + 1];
		const Vec3f &n2 = N[triIndex * 3 + 2];
		hitNormal = (1 - uv.x - uv.y) * n0 + uv.x * n1 + uv.y * n2;
		*/
	}

	bool rayTriangleIntersect(glm::vec3 &orig, glm::vec3 &dir,
		const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2,
		float &t, float &u, float &v)
	{
		glm::vec3 v0v1 = v1 - v0;
		glm::vec3 v0v2 = v2 - v0;
		glm::vec3 pvec = glm::cross(dir,v0v2);
		float det = glm::dot(v0v1, pvec);

		// ray and triangle are parallel if det is close to 0
		if (fabs(det) < 1e-8) 
			return false;

		float invDet = 1 / det;

		glm::vec3 tvec = orig - v0;
		u = glm::dot(tvec,pvec) * invDet;
		if (u < 0 || u > 1) return false;

		glm::vec3 qvec = glm::cross(tvec,v0v1);
		v = glm::dot(dir,qvec) * invDet;
		if (v < 0 || u + v > 1) return false;

		t = glm::dot(v0v2,qvec) * invDet;

		return true;
	}

	bool intersect(glm::vec3 &orig, glm::vec3 &dir, float &tNear, int &triIndex, glm::vec2 &uv) 
	{
		int j = 0;
		bool isect = false;
		for (int i = 0; i < numTris; i++) {
			const glm::vec3 &v0 = P[trisIndex[j]];
			const glm::vec3 &v1 = P[trisIndex[j + 1]];
			const glm::vec3 &v2 = P[trisIndex[j + 2]];

			float t = INFINITY, u, v;
			if (rayTriangleIntersect(orig, dir, v0, v1, v2, t, u, v) && t < tNear) {
				tNear = t;
				uv.x = u;
				uv.y = v;
				triIndex = i;
				isect = true;
			}
			j += 3;
		}

		return isect;
	}

private:
	string file; //where filename.obj is the OBJ file containing the mesh
	//const char * file; //where filename.obj is the OBJ file containing the mesh
	std::vector<int> indices;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> UVs;

	//attributes needed according to ScratchaPixel website
	int numTris;
	unique_ptr<glm::vec3[]> P;
	unique_ptr<int[]> trisIndex;
	unique_ptr<glm::vec3[]> N;
	unique_ptr<glm::vec2[]> texCoordinates;
	//glm::vec3 amb; //where (ax, ay, az) is the ambient color of the mesh
	//glm::vec3 dif; //where (dx, dy, dx) is the diffuse color of the mesh
	//glm::vec3 spe; //where (sx, sy, sz) is the specular color of the mesh
	//float shi; //where s is the specular shininess factor
};

#endif
