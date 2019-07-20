#include "Camera.h"

Camera::Camera() {
	pos = glm::vec3(0, 0, 0);
	fov = 0;
	f = 0;
	a = 0;
}
Camera::Camera(glm::vec3 _pos, float _fov, float _f, float _a) {
	pos = _pos;
	fov = _fov;
	f = _f;
	a = _a;
}
Camera::~Camera() {}

glm::vec3 Camera::getPosition() {
	return pos;
}
void Camera::setPosition(glm::vec3 _pos) {
	pos = _pos;
}

float Camera::getFieldOfView() {
	return fov;
}
void Camera::setFieldOfView(float _fov) {
	fov = _fov;
}

float Camera::getFocalLength() {
	return f;
}
void Camera::setFocalLength(float _f) {
	f = _f;
}

float Camera::getAspectRatio() {
	return a;
}
void Camera::setAspectRatio(float _a) {
	a = _a;
}