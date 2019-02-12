#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include <glm/gtx/vector_angle.hpp>
#include <GL/glew.h>

#include "Viewport.h"

class Text{
private:
	std::string message, texture;
	int x, y, size;
	std::vector<glm::vec2> UVs;
	std::vector<glm::vec3> vertices;
	GLuint vertexbuffer, uvbuffer;
public:
	Text();
	Text(std::string m, std::string tex, int xpos, int ypos, int s);

	static GLuint loadBMP(const char*imagepath);

	void init();
	void draw(GLuint shader);

};

#endif
