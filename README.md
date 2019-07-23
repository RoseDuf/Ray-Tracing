# Ray-Tracing
Computer Graphics (COMP 371) final project

> GLM library and Cimg needed: ..\CImg_latest\CImg-2.5.5;..\glm;%(AdditionalIncludeDirectories)

## Instructions

To change a file simply change the following at line 198 of the code:

> Scene * scene = new Scene("scenes/name_of_file.txt");

Replace "name_of_file" with the file you wish to run.

## Does it work?
Parses properly scene files of the given format.
### 
Will print the contents of said files to the console to check if values are correct.
### 
Renders properly any scene of the right dimensions depending on the camera attributes given.
### 
Renders Sphere and Plane objects properly.
### 
Computes lighting properly, handles multiple lights.
### 
Computes shadows properly, handles multiple shadows from multiple lights.

## Key methods:

* ComputePointLight -> used Phong model of light calculations.
* trace -> assigns the minimum point of intersection.
* cast_ray -> method that computes color of objects depending on whether or not there is intersection with ray.
* intersect -> computes whether or not there is an intersection with the ray and an object.

## Notes
Program uses Cimg library to display images.
### 
Renders images into a file called: render.bmp.
 
