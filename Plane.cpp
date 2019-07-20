#include "Plane.h"

Plane::Plane() {
	nor = glm::vec3(0, 0, 0);
	/*pos = glm::vec3(0, 0, 0);
	amb = glm::vec3(0, 0, 0);
	dif = glm::vec3(0, 0, 0);
	spe = glm::vec3(0, 0, 0);
	shi = 0;*/
}
Plane::Plane(glm::vec3 _nor/*, glm::vec3 _pos, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spe, float _shi*/) {
	nor = _nor;
	/*pos = _pos;
	amb = _amb;
	dif = _dif;
	spe = _spe;
	shi = _shi;*/
}
Plane::~Plane() {}

//plane normal given
glm::vec3 Plane::getNormal(glm::vec3 phit) {
	return nor;
}
void Plane::setNormal(glm::vec3 _nor) {
	nor = _nor;
}
//
//glm::vec3 Plane::getPosition() {
//	return pos;
//}
//void Plane::setPosition(glm::vec3 _pos) {
//	pos = _pos;
//}
//
//glm::vec3 Plane::getAmb() {
//	return amb;
//}
//void Plane::setAmb(glm::vec3 _amb) {
//	amb = _amb;
//}
//
//glm::vec3 Plane::getDif() {
//	return dif;
//}
//void Plane::setDif(glm::vec3 _dif) {
//	dif = _dif;
//}
//
//glm::vec3 Plane::getSpe() {
//	return spe;
//}
//void Plane::setSpe(glm::vec3 _spe) {
//	spe = _spe;
//}
//
//float Plane::getShi() {
//	return shi;
//}
//void Plane::setShi(float _shi) {
//	shi = _shi;
//}

//compute if there is intersection with the plane
bool Plane::intersect(const glm::vec3 &rayorig, const glm::vec3 &raydir, float &t) {

	float denom = glm::dot(this->nor, raydir);
	if (abs(denom) > 1e-6) {
		glm::vec3 p0l0 = this->getPosition() - rayorig;
		t = glm::dot(p0l0, this->nor) / denom;
		return (t >= 0);
	}

	return false;
}