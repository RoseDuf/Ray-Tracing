#ifndef LIGHT_HPP_
#define LIGHT_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include <fstream>
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Light {

public:

	Light();
	Light(glm::vec3 pos, glm::vec3 _dif, glm::vec3 _spe);
	~Light();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);

	glm::vec3 getDif();
	void setDif(glm::vec3 dif);

	glm::vec3 getSpe();
	void setSpe(glm::vec3 spe);

private:
	glm::vec3 pos; //where (px, py, pz) is the position of the light
	glm::vec3 dif; //where (dx, dy, dx) is the diffuse color of the light
	glm::vec3 spe; //where (sx, sy, sz) is the specular color of the light
};

#endif
