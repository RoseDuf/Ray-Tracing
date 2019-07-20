#ifndef CAMERA_HPP_
#define CAMERA_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include <fstream>
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

class Camera {

public:

	Camera();
	Camera(glm::vec3 pos, float fov, float f, float a);
	~Camera();

	glm::vec3 getPosition();
	void setPosition(glm::vec3 pos);

	float getFieldOfView();
	void setFieldOfView(float fov);

	float getFocalLength();
	void setFocalLength(float f);

	float getAspectRatio();
	void setAspectRatio(float a);

private:
	glm::vec3 pos; //where x y z are floating pofloat numbers specifying the location of the camera
	float fov; //where theta is the field-of-view in degrees)
	float f; //where d is the focal length of the camera
	float a; //where a is the aspect ratio of the camera
};

#endif


