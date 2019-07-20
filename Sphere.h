#ifndef SPHERE_HPP_
#define SPHERE_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include "Object.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Sphere : public Object {

public:

	Sphere();
	Sphere(/*glm::vec3 pos,*/ int rad/*, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spe, int _shi*/);
	~Sphere();

	float getRadius();
	void setRadius(float rad);

	/*glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);

	glm::vec3 getAmb();
	void setAmb(glm::vec3 amb);

	glm::vec3 getDif();
	void setDif(glm::vec3 dif);

	glm::vec3 getSpe();
	void setSpe(glm::vec3 spe);

	float getShi();
	void setShi(float shi);*/

	glm::vec3 getNormal(glm::vec3 phit);

	bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t);

private:
	float rad; //where r is the radius of the sphere
	glm::vec3 nor;
	//glm::vec3 pos; //where (px, py, pz) is the position of the center of the sphere
	//glm::vec3 amb; //where (ax, ay, az) is the ambient color of the sphere
	//glm::vec3 dif; //where (dx, dy, dx) is the diffuse color of the sphere
	//glm::vec3 spe; //where (sx, sy, sz) is the specular color of the sphere
	//float shi; //where s is the specular shininess factor
};

#endif
