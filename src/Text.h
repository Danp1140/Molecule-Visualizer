//
// Created by Daniel Paavola on 2019-04-11.
//

#ifndef MOLECULE_VISUALIZER_TEXT_H
#define MOLECULE_VISUALIZER_TEXT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <iostream>

class Text{
private:
	std::vector<char> message;
	int size, dispwidth, dispheight, maxLineWidth, lines;
	FT_Face face;
	glm::vec2 position;
	glm::vec4 textColor;
public:
	Text();
	Text(std::string m, int s, const char*fontfilepath, FT_Library library, int dw, int dh, glm::vec2 pos);

	void draw(GLuint shader);

	void setPosition(glm::vec2 p){position=p;}
	void setTextColor(glm::vec4 c){textColor=c;}
	void setMessage(std::string m);

	std::vector<char> getMessage(){return message;}
	int getSize(){return size;}
	int getMaxLineWidth(){return maxLineWidth;}
	int getLines(){return lines;}
	glm::vec2 getPosition(){return position;}
	int getWidth(){return dispwidth;}
	int getHeight(){return dispheight;}
};


#endif //MOLECULE_VISUALIZER_TEXT_H
