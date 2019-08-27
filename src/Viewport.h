#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
//#include <glm/gtx/matrix_operation.hpp>

#include "Drawable.h"
#include "Camera.h"
#include "Molecule.h"
#include "Button.h"

class Viewport{
private:
	Camera camera;
	GLFWwindow *window;
	int width, height;
	GLuint programID, textID, VertexArrayID;
	Drawable test;
public:
	Viewport(Camera c, GLFWwindow *w, int wdth, int hght, GLuint shaders);

	void draw(Molecule &molecule);

	bool obbCheck(Drawable *d);
	Camera getCamera(){return camera;}

	static GLuint loadShaders(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
	static GLuint loadBMP(const char* imagepath);
};

#endif