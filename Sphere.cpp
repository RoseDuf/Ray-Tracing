
#include "Sphere.h"

Sphere::Sphere() {
	rad = 0;
	/*pos = glm::vec3(0, 0, 0);
	amb = glm::vec3(0, 0, 0);
	dif = glm::vec3(0, 0, 0);
	spe = glm::vec3(0, 0, 0);
	shi = 0;*/
}
Sphere::Sphere(/*glm::vec3 _pos, */int _rad/*, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spe, int _shi*/) {
	rad = _rad;
	/*pos = _pos;
	amb = _amb;
	dif = _dif;
	spe = _spe;
	shi = _shi;*/
}
Sphere::~Sphere() {}

 float Sphere::getRadius() {
	return rad;
}
void Sphere::setRadius(float _rad) {
	rad = _rad;
}

//normal of circle needs a little calculation
glm::vec3 Sphere::getNormal(glm::vec3 phit) {
	return glm::normalize((phit - this->getPosition()) / rad);
}

//
//glm::vec3 Sphere::getPosition() {
//	return pos;
//}
//void Sphere::setPosition(glm::vec3 _pos) {
//	pos = _pos;
//}
//
//glm::vec3 Sphere::getAmb() {
//	return amb;
//}
//void Sphere::setAmb(glm::vec3 _amb) {
//	amb = _amb;
//}
//
//glm::vec3 Sphere::getDif() {
//	return dif;
//}
//void Sphere::setDif(glm::vec3 _dif) {
//	dif = _dif;
//}
//
//glm::vec3 Sphere::getSpe() {
//	return spe;
//}
//void Sphere::setSpe(glm::vec3 _spe) {
//	spe = _spe;
//}
//
//float Sphere::getShi() {
//	return shi;
//}
//void Sphere::setShi(float _shi) {
//	shi = _shi;
//}

//computes if there is a point of intersection with the ray

bool Sphere::intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t)
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