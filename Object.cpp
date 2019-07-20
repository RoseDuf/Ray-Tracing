#include "Object.h"

Object::Object() {
	pos = glm::vec3(0, 0, 0);
	amb = glm::vec3(0, 0, 0);
	dif = glm::vec3(0, 0, 0);
	spe = glm::vec3(0, 0, 0);
	shi = 0;
}
Object::Object(glm::vec3 _pos, glm::vec3 _amb, glm::vec3 _dif, glm::vec3 _spe, float _shi) {
	pos = _pos;
	amb = _amb;
	dif = _dif;
	spe = _spe;
	shi = _shi;
}
Object::~Object() {}

glm::vec3 Object::getPosition() {
	return pos;
}
void Object::setPosition(glm::vec3 _pos) {
	pos = _pos;
}

glm::vec3 Object::getAmb() {
	return amb;
}
void Object::setAmb(glm::vec3 _amb) {
	amb = _amb;
}

glm::vec3 Object::getDif() {
	return dif;
}
void Object::setDif(glm::vec3 _dif) {
	dif = _dif;
}

glm::vec3 Object::getSpe() {
	return spe;
}
void Object::setSpe(glm::vec3 _spe) {
	spe = _spe;
}

float Object::getShi() {
	return shi;
}
void Object::setShi(float _shi) {
	shi = _shi;
}