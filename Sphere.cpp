
#include "Sphere.h"

Sphere::Sphere() {
	rad = 0;
}
Sphere::Sphere(int _rad) {
	rad = _rad;
}
Sphere::~Sphere() {}

 float Sphere::getRadius() {
	return rad;
}
void Sphere::setRadius(float _rad) {
	rad = _rad;
}

//normal of circle needs a little calculation
glm::vec3 Sphere::getNormal(glm::vec3 phit, int triIndex) {
	return glm::normalize((phit - this->getPosition()) / rad);
}

//computes if there is a point of intersection with the ray

bool Sphere::intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t, int &index)
{
	glm::vec3 o = rayorig;
	glm::vec3 d = raydir;

	glm::vec3 originToCenter = o - this->getPosition();

	//circle variables
	float a = 1; //always 1
	float b = 2 * glm::dot(d, originToCenter);
	float c = glm::dot(originToCenter, originToCenter) - rad * rad;

	float inner_quadratic = b * b - 4 * a* c; // if this is smaller than 0, 

	if (inner_quadratic < 0)
		return false;

	//finish quadratic formula
	inner_quadratic = sqrt(inner_quadratic);
	float t0 = (-b - inner_quadratic) / (2 * a);
	float t1 = (-b + inner_quadratic) / (2 * a);

	//assign minimum intersection distance
	t = (t0 < t1) ? t0 : t1;

	return true;
}