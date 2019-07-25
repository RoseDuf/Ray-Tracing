#include "Plane.h"

Plane::Plane() {
	nor = glm::vec3(0, 0, 0);
}
Plane::Plane(glm::vec3 _nor) {
	nor = _nor;
}
Plane::~Plane() {}

//plane normal given
glm::vec3 Plane::getNormal(glm::vec3 phit) {
	return nor;
}
void Plane::setNormal(glm::vec3 _nor) {
	nor = _nor;
}

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