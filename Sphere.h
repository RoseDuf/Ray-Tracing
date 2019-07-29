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
	Sphere(int rad);
	~Sphere();

	float getRadius();
	void setRadius(float rad);

	glm::vec3 getNormal(glm::vec3 phit);

	bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t, int &index);

private:
	float rad; //where r is the radius of the sphere
	glm::vec3 nor;
};

#endif
