#ifndef PLANE_HPP_
#define PLANE_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include "Object.h"
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Plane : public Object{

public:
	Plane();
	Plane(glm::vec3 nor);
	~Plane();

	glm::vec3 getNormal(glm::vec3 phit);
	void setNormal(glm::vec3 nor);

	bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t, int &index);
	
private:
	glm::vec3 nor; 
};

#endif
