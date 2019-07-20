#ifndef SCENE_HPP_
#define SCENE_HPP_

#include<iostream>
#include<cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"
#include "Plane.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Light.h"

using namespace std;

class Scene {

public:
	Scene();
	Scene(string file);
	~Scene();
	void ReadSceneFile(string file);

	int getTotalNumberOfObjects();
	void setTotalNumberOfObjects(int tot);

	Camera * getCamera();
	void setCamera(Camera * cam);

	vector<shared_ptr<Plane>> getPlane();
	void setPlane(vector<shared_ptr<Plane>> plane);

	vector<shared_ptr<Sphere>> getSphere();
	void setSphere(vector<shared_ptr<Sphere>> sphere);

	vector<shared_ptr<Mesh>> getMesh();
	void setMesh(vector<shared_ptr<Mesh>> mesh);

	vector<Light> getLight();
	void setLight(vector<Light> light);

private:
	string file;
	int totalNumberOfObjects;
	Camera * cam;
	vector<shared_ptr<Plane>> plane;
	vector<shared_ptr<Sphere>> sphere;
	vector<shared_ptr<Mesh>> mesh;
	vector<Light> light;
};

#endif
