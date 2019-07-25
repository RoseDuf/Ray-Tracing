#include "Scene.h"

//object loader 
#include "objloaderIndex.h"

Scene::Scene() {
	file = "";
	totalNumberOfObjects = 0;
}
Scene::Scene(string _file) {
	file = _file;
	ReadSceneFile(file);
}

Scene::~Scene() {}

void Scene::ReadSceneFile(string file) {
	string line;
	string line2;

	ifstream input(file);

	if (input.fail()) {
		cout << "File does not exist" << endl;
		cout << "Exit program" << endl;
		exit(1);
	}

	while (getline(input, line)) {

		if (line == "") {
		}

		else if (line == "camera"){
			cam = new Camera();
			float number;
			string attribute;

			float camposx, camposy, camposz;
			input >> attribute >> camposx >> camposy >> camposz;
			glm::vec3 pos = glm::vec3(camposx, camposy, camposz);
			cam->setPosition(pos);

			input >> attribute >> number;
			cam->setFieldOfView(number);

			input >> attribute >> number;
			cam->setFocalLength(number);

			input >> attribute >> number;
			cam->setAspectRatio(number);
		}
		else if (line == "plane") {
			shared_ptr<Plane> newplane(new Plane());
			float number;
			string attribute;

			float planeposx, planeposy, planeposz;
			input >> attribute >> planeposx >> planeposy >> planeposz;
			glm::vec3 nor = glm::vec3(planeposx, planeposy, planeposz);
			newplane->setNormal(nor);

			input >> attribute >> planeposx >> planeposy >> planeposz;
			glm::vec3 pos = glm::vec3(planeposx, planeposy, planeposz);
			newplane->setPosition(pos);

			input >> attribute >> planeposx >> planeposy >> planeposz;
			glm::vec3 amb = glm::vec3(planeposx, planeposy, planeposz);
			newplane->setAmb(amb);

			input >> attribute >> planeposx >> planeposy >> planeposz;
			glm::vec3 dif = glm::vec3(planeposx, planeposy, planeposz);
			newplane->setDif(dif);

			input >> attribute >> planeposx >> planeposy >> planeposz;
			glm::vec3 spe = glm::vec3(planeposx, planeposy, planeposz);
			newplane->setSpe(spe);

			input >> attribute >> number;
			newplane->setShi(number);

			plane.push_back(newplane);
		}
		else if (line == "sphere") {
			shared_ptr<Sphere> newsphere(new Sphere());
			float number;
			string attribute;

			float sphereposx, sphereposy, sphereposz;
			input >> attribute >> sphereposx >> sphereposy >> sphereposz;
			glm::vec3 pos = glm::vec3(sphereposx, sphereposy, sphereposz);
			newsphere->setPosition(pos);

			input >> attribute >> number;
			newsphere->setRadius(number);

			input >> attribute >> sphereposx >> sphereposy >> sphereposz;
			glm::vec3 amb = glm::vec3(sphereposx, sphereposy, sphereposz);
			newsphere->setAmb(amb);

			input >> attribute >> sphereposx >> sphereposy >> sphereposz;
			glm::vec3 dif = glm::vec3(sphereposx, sphereposy, sphereposz);
			newsphere->setDif(dif);

			input >> attribute >> sphereposx >> sphereposy >> sphereposz;
			glm::vec3 spe = glm::vec3(sphereposx, sphereposy, sphereposz);
			newsphere->setSpe(spe);

			input >> attribute >> number;
			newsphere->setShi(number);

			sphere.push_back(newsphere);
		}
		else if (line == "mesh") {
			shared_ptr<Mesh> newmesh(new Mesh());
			float number;
			string attribute;
			string filename;

			float meshposx, meshposy, meshposz;

			input >> attribute >> filename;
			newmesh->setFile(filename);
			//const char * file2 = filename.c_str(); //NOTE: don't convert before everything. Do it last!
			//newmesh->setFile(file2); //NOTE: don't convert before everything. Do it last!

			std::vector<int> indices;
			std::vector<glm::vec3> vertices;
			std::vector<glm::vec3> normals;
			std::vector<glm::vec2> UVs;

			loadOBJ(newmesh->getFile(), indices, vertices, normals, UVs);

			newmesh->setIndices(indices);
			newmesh->setVertices(vertices);
			newmesh->setNormals(normals);
			newmesh->setUVs(UVs);

			input >> attribute >> meshposx >> meshposy >> meshposz;
			glm::vec3 amb = glm::vec3(meshposx, meshposy, meshposz);
			newmesh->setAmb(amb);

			input >> attribute >> meshposx >> meshposy >> meshposz;
			glm::vec3 dif = glm::vec3(meshposx, meshposy, meshposz);
			newmesh->setDif(dif);

			input >> attribute >> meshposx >> meshposy >> meshposz;
			glm::vec3 spe = glm::vec3(meshposx, meshposy, meshposz);
			newmesh->setSpe(spe);

			input >> attribute >> number;
			newmesh->setShi(number);

			mesh.push_back(newmesh);
		}
		else if (line == "light") {
			Light newlight = Light();
			float number;
			string attribute;

			float lightposx, lightposy, lightposz;
			input >> attribute >> lightposx >> lightposy >> lightposz;
			glm::vec3 pos = glm::vec3(lightposx, lightposy, lightposz);
			newlight.setPosition(pos);

			input >> attribute >> lightposx >> lightposy >> lightposz;
			glm::vec3 dif = glm::vec3(lightposx, lightposy, lightposz);
			newlight.setDif(dif);

			input >> attribute >> lightposx >> lightposy >> lightposz;
			glm::vec3 spe = glm::vec3(lightposx, lightposy, lightposz);
			newlight.setSpe(spe);

			light.push_back(newlight);
		}
		else
			totalNumberOfObjects = stoi(line);
	}
	input.close();
}

int Scene::getTotalNumberOfObjects() {
	return totalNumberOfObjects;
}
void Scene::setTotalNumberOfObjects(int tot) {
	totalNumberOfObjects = tot;
}

Camera * Scene::getCamera() {
	return cam;
}
void Scene::setCamera(Camera * _cam) {
	cam = _cam;
}

vector<shared_ptr<Plane>> Scene::getPlane() {
	return plane;
}
void Scene::setPlane(vector<shared_ptr<Plane>> _plane) {
	plane = _plane;
}

vector<shared_ptr<Sphere>> Scene::getSphere() {
	return sphere;
}
void Scene::setSphere(vector<shared_ptr<Sphere>> _sphere) {
	sphere = _sphere;
}

vector<shared_ptr<Mesh>> Scene::getMesh() {
	return mesh;
}
void Scene::setMesh(vector<shared_ptr<Mesh>> _mesh) {
	mesh = _mesh;
}

vector<Light> Scene::getLight() {
	return light;
}
void Scene::setLight(vector<Light> _light) {
	light = _light;
}