#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Drawable.h"
#include "Camera.h"

class Viewport{
private:
	Camera camera;
	GLFWwindow *window;
	int width, height;
	std::vector<Drawable*> objects;
	GLuint programID, VertexArrayID;;
public:
	Viewport(Camera c, GLFWwindow *w, int wdth, int hght, GLuint shaders);

	void draw();

	void addDrawable(Drawable* object);

	static bool loadOBJ(const char* obj_filepath, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals);
	static GLuint loadShaders(const char* vertex_shader_filepath, const char* fragment_shader_filepath);
};

#endif