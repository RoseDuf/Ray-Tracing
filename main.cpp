
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <memory>

//include glm stuff
#include "glm.hpp"
#include "gtx/transform.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Camera.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Mesh.h"
#include "Light.h"
#include "Scene.h"

//object loader stuff
#include "objloaderIndex.h"

//include Cimg library header
#include "CImg.h"
using namespace cimg_library;

using namespace std;

#define M_PI 3.141592653589793
#define INFINITY 1e8 

//Phong calculation
glm::vec3 ComputePointLight(Light &light, glm::vec3 &norm, glm::vec3 &fragment_pos, glm::vec3 &view_dir, glm::vec3 &lightDirection, shared_ptr<Object> &object) {

	//Specular
	//glm::vec3 reflect_light_direction = glm::reflect(-lightDirection, normalize(norm));
	glm::vec3 reflect_light_direction = glm::normalize(norm * 2.0f*glm::dot(norm, lightDirection) - lightDirection);

	//computing lights
	glm::vec3 ambient = object->getAmb();
	glm::vec3 diffuse = glm::max(glm::dot(norm, lightDirection), 0.0f) * object->getDif() * light.getDif();
	glm::vec3 specular = glm::pow(glm::max(glm::dot(reflect_light_direction, view_dir), 0.0f), (float)object->getShi()) * object->getSpe() * light.getSpe();
	glm::vec3 color = (specular + diffuse + ambient);

	return color;
}

//trace but for mesh, unfinished
bool traceMesh(glm::vec3 &orig, glm::vec3 &dir,
	vector<shared_ptr<Mesh>> &meshes,
	float &tNear, int &index, glm::vec2 &uv, shared_ptr<Mesh> &hitObject){

	for (int k = 0; k < meshes.size(); k++) {
		float tNearTriangle = INFINITY;
		int indexTriangle;
		glm::vec2 uvTriangle;
		if (meshes[k]->intersect(orig, dir, tNearTriangle, indexTriangle, uvTriangle) && tNearTriangle < tNear) {
			hitObject = meshes[k];
			tNear = tNearTriangle;
			index = indexTriangle;
			uv = uvTriangle;
		}
	}

	return (hitObject != nullptr);
}

//assigns the minimum point of intersection
bool trace(glm::vec3 origin, glm::vec3 direction, vector<shared_ptr<Object>> objects, float &tmin, shared_ptr<Object> &object) {
	tmin = INFINITY;
	for (int i = 0; i < objects.size(); i++) {
		float t = INFINITY;
		if (objects[i]->intersect(origin, direction, t) && t<tmin) {
			object = objects[i];
			tmin = t;
		}
	}
	return (object != nullptr);
}

//method that computes color of objects depending on whether or not there is intersection with ray
glm::vec3 cast_ray(glm::vec3 rayorig, glm::vec3 &raydir, 
	vector<shared_ptr<Object>> objects, 
	vector<shared_ptr<Mesh>> meshes,
	vector<Light> &lights, Camera *cam) {
	
	glm::vec3 surfaceColor = glm::vec3(0);
	shared_ptr<Object> object = nullptr; //target object
	shared_ptr<Mesh> mesh = nullptr; //target mesh
	glm::vec2 uv;
	int index = 0;

	float tmin; //the closest point of intersection from ray origin to object

	//computing the colors produced by the ray on an object (with light)
	if (trace(rayorig, raydir, objects, tmin, object)) {
		//itterate through all the lights
		for (int i = 0; i < lights.size(); i++) {

			glm::vec3 phit = rayorig + raydir * tmin; //point hit in parametric form (p0 +dt)
			glm::vec3 nhit = glm::normalize(object->getNormal(phit)); //normal of the point hit (normal calculation is different between planes and spheres)
			glm::vec3 view_direction = glm::normalize(cam->getPosition() - phit); //camera view direction
			glm::vec3 lightDirection = glm::normalize(lights[i].getPosition() - phit); //light direction vector
			
			//computing shadows (similar calculation of trace)
			float tshadow = INFINITY;
			float bias = 1e-8; //add bias
			shared_ptr<Object> objectShadow = nullptr;
			
			//if object is not in shadow, compute surface color normally using Phong
			if ((!trace(phit + nhit * bias, -lightDirection, objects, tshadow, objectShadow)) || (object == objectShadow)) {
				
				surfaceColor += ComputePointLight(lights[i], nhit, phit, view_direction, lightDirection, object);

			}
			else //just the ambient color of an object if object IS in shadow
				surfaceColor += object->getAmb();
		}
	}

	//attempted raycasting of the mesh, unfortunalety it is unfinished
	else if (traceMesh(rayorig, raydir, meshes, tmin, index, uv, mesh)) {
		glm::vec3 phit = rayorig + raydir * tmin;
		glm::vec3 nhit = glm::normalize(object->getNormal(phit));
		glm::vec2 hitTexCoordinates;
		mesh->getSurfaceProperties(phit, raydir, index, uv, nhit, hitTexCoordinates);
		float NdotView = std::max(0.f, glm::dot(-raydir, nhit));
		const int M = 10;
		float checker = (fmod(hitTexCoordinates.x * M, 1.0) > 0.5) ^ (fmod(hitTexCoordinates.y * M, 1.0) < 0.5);
		float c = 0.3 * (1 - checker) + 0.7 * checker;

		surfaceColor = glm::vec3(c * NdotView);
	}

	//resulting color
	return surfaceColor;
}

void render(vector<shared_ptr<Object>> &objects, vector<shared_ptr<Mesh>> &meshes, vector<Light> &lights, Camera *camera) {

	float fov = camera->getFieldOfView();
	float f = 3*camera->getFocalLength();
	float aspectratio = camera->getAspectRatio();
	float angle = glm::radians(fov * 0.5);

	//relative height and width depending on the camera attributes
	//calculation from our notes
	int height = 2 * (tan(glm::radians(fov) / 2)) * f;
	int width = aspectratio * height;

	CImg<unsigned char> image(width, height, 1, 3, 0);  // Define a 640x400 color image with 8 bits per color component.
	
	glm::vec3 pixel_color;
	float invWidth = 1 / float(width), invHeight = 1 / float(height);
	
	//just to confirm the scene is rendering by counting the pixels in the y coordinate
	int count = 0;

	// Trace rays
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			
			//relative x and y of the ray going across the screen
			int yy = height / 2 - y;
			int xx = x + width/ -2;

			glm::vec3 raydir = glm::normalize(glm::vec3(xx, yy, f * -1) - camera->getPosition());

			pixel_color = cast_ray(camera->getPosition(), raydir, objects, meshes, lights, camera);
			
			//don't forget to clamp to avoid weird colors
			pixel_color = glm::clamp(pixel_color, 0.0f, 1.0f);

			//pixel colors
			image(x, y, 0) = pixel_color[0] * 255.0f; //red
			image(x, y, 1) = pixel_color[1] * 255.0f; //green
			image(x, y, 2) = pixel_color[2] * 255.0f; //blue
		}
		count++;
		cout << count << endl;
	}

	//Save out the image in BMP format. Pixel values must be in the range [0,255]
	image.save("render.bmp");
	//Display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) {
		main_disp.wait();
	}
}

int main() {

	//read scene file
	Scene * scene = new Scene("scenes/mesh_scene1.txt");

	//create objects
	Camera * cam = new Camera();
	vector<shared_ptr<Plane>> plane;
	vector<shared_ptr<Sphere>> sphere;
	vector<shared_ptr<Mesh>> mesh;
	vector<Light> light;
	
	//assign object information to objects
	cam = scene->getCamera();
	plane = scene->getPlane();
	sphere = scene->getSphere();
	mesh = scene->getMesh(); //unfinished
	light = scene->getLight();

	//create an object vector with all the objects of the scene (spheres and planes)
	vector<shared_ptr<Object>> objects;

	for (int i = 0; i < sphere.size(); i++) {
		objects.push_back(sphere[i]);
	}
	for (int i = 0; i < plane.size(); i++) {
		objects.push_back(plane[i]);
	}

	//RENDER SCENE
	//render(objects, mesh, light, cam);

	//To show that scene was properly rendered with the right values
	cout << "number of objects" << endl;
	cout << scene->getTotalNumberOfObjects() << endl;

	cout << "camera info" << endl;
		cout << cam->getPosition().x << " " << cam->getPosition().y << " " << cam->getPosition().z << endl;
		cout << cam->getFieldOfView() << endl;
		cout << cam->getFocalLength() << endl;
		cout << cam->getAspectRatio() << endl;
	for (int i = sphere.size(); i < (sphere.size()+plane.size()); i++) {
		cout << "plane info" << endl;
		cout << objects[i]->getPosition().x << " " << objects[i]->getPosition().y << " " << objects[i]->getPosition().z << endl;
		cout << objects[i]->getNormal(glm::vec3(1)).x << " " << objects[i]->getNormal(glm::vec3(1)).y << " " << objects[i]->getNormal(glm::vec3(1)).z << endl;
		cout << objects[i]->getAmb().x << " " << objects[i]->getAmb().y << " " << objects[i]->getAmb().z << endl;
		cout << objects[i]->getDif().x << " " << objects[i]->getDif().y << " " << objects[i]->getDif().z << endl;
		cout << objects[i]->getSpe().x << " " << objects[i]->getSpe().y << " " << objects[i]->getSpe().z << endl;
		cout << objects[i]->getShi() << endl;
	}
	for (int i = 0; i < sphere.size(); i++) {
		cout << "sphere info" << endl;
		cout << objects[i]->getPosition().x << " " << objects[i]->getPosition().y << " " << objects[i]->getPosition().z << endl;
		cout << sphere[i]->getRadius() << endl;
		cout << objects[i]->getAmb().x << " " << objects[i]->getAmb().y << " " << objects[i]->getAmb().z << endl;
		cout << objects[i]->getDif().x << " " << objects[i]->getDif().y << " " << objects[i]->getDif().z << endl;
		cout << objects[i]->getSpe().x << " " << objects[i]->getSpe().y << " " << objects[i]->getSpe().z << endl;
		cout << objects[i]->getShi() << endl;
	}
	for (int i = 0; i < mesh.size(); i++) {
		cout << "mesh info" << endl;
		cout << mesh[i]->getFile() << endl;
		cout << mesh[i]->getAmb().x << " " << mesh[i]->getAmb().y << " " << mesh[i]->getAmb().z << endl;
		cout << mesh[i]->getDif().x << " " << mesh[i]->getDif().y << " " << mesh[i]->getDif().z << endl;
		cout << mesh[i]->getSpe().x << " " << mesh[i]->getSpe().y << " " << mesh[i]->getSpe().z << endl;
		cout << mesh[i]->getShi() << endl;
	}
	for (int i = 0; i < light.size(); i++) {
		cout << "light info" << endl;
		cout << light[i].getPosition().x << " " << light[i].getPosition().y << " " << light[i].getPosition().z << endl;
		cout << light[i].getDif().x << " " << light[i].getDif().y << " " << light[i].getDif().z << endl;
		cout << light[i].getSpe().x << " " << light[i].getSpe().y << " " << light[i].getSpe().z << endl;
	}
	
	return 0;
}
