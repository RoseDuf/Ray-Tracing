
#include "Light.h"

Light::Light() {
	pos = glm::vec3(0, 0, 0);
	dif = glm::vec3(0, 0, 0);
	spe = glm::vec3(0, 0, 0);
}
Light::Light(glm::vec3 _pos, glm::vec3 _dif, glm::vec3 _spe) {
	pos = _pos;
	dif = _dif;
	spe = _spe;
}
Light::~Light() {}

glm::vec3 Light::getPosition() {
	return pos;
}
void Light::setPosition(glm::vec3 _pos) {
	pos = _pos;
}

glm::vec3 Light::getDif() {
	return dif;
}
void Light::setDif(glm::vec3 _dif) {
	dif = _dif;
}

glm::vec3 Light::getSpe() {
	return spe;
}
void Light::setSpe(glm::vec3 _spe) {
	spe = _spe;
}