#ifndef OBJECT_HPP_
#define OBJECT_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

//parent class for Plane, Spheres and Mesh
class Object {

public:

	Object();
	Object(glm::vec3 pos, glm::vec3 amb, glm::vec3 dif, glm::vec3 spe, float shi);
	~Object();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);

	glm::vec3 getAmb();
	void setAmb(glm::vec3 amb);

	glm::vec3 getDif();
	void setDif(glm::vec3 dif);

	glm::vec3 getSpe();
	void setSpe(glm::vec3 spe);

	float getShi();
	void setShi(float shi);

	virtual glm::vec3 getNormal(glm::vec3 phit) {return glm::vec3(0);}

	virtual bool intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t, int &index) { return false; }

private:
	glm::vec3 nor;
	glm::vec3 pos; 
	glm::vec3 amb; 
	glm::vec3 dif; 
	glm::vec3 spe; 
	float shi; 
};

#endif
