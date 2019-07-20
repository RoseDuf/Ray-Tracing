Rose Dufresne
(I.D.# 40030476)

****Important notice****
I did not have time to finish implementing the Mesh ray tracing calculations.
I sourced the website I was trying to follow to do this but did not have time to finish.

As for what is done:

To change a file simply change the following at line 198 of the code:
Scene * scene = new Scene("scenes/name_of_file.txt");

replace "name_of_file" with the file you wish to run.

Parses properly scene files of the given format
Will print the contents of said files to the console to check if values are correct

Renders properly any scene of the right dimensions depending on the camera attributes given
Renders Sphere and Plane objects properly

Computes lighting properly, handles multiple lights

Computes shadows properly, handles multiple shadows from multiple lights

Key methods:

ComputePointLight -> used Phong model of light calculations
trace -> assigns the minimum point of intersection
cast_ray -> method that computes color of objects depending on whether or not there is intersection with ray
intersect -> computes whether or not there is an intersection with the ray and an object

Program uses Cimg library to display images
renders images into a file called: render.bmp