#ifndef DRAWABLE_H_
#define DRAWABLE_H_

#include <vector>
#include <iostream>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>

class Drawable{
protected:
    std::vector<glm::vec3> verticies, normals;
    glm::vec3 positionvar, scalevar, color;
    glm::quat rotationvar;
    GLuint vertexbuffer, normalbuffer;
public:
    Drawable();
//    Drawable(std::vector<glm::vec3> v, std::vector<glm::vec3> n, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, glm::vec3 clr);
	Drawable(const char* modelfilepath);

    virtual void draw(glm::mat4 viewmat, glm::mat4 projectmat, GLuint shader, glm::vec3 camPos);

    void setPos(glm::vec3 pos);
    void setRot(glm::vec3 angles);
    void setScl(glm::vec3 scl);
    void setVN(std::vector<glm::vec3> v, std::vector<glm::vec3> n);
    void setClr(glm::vec3 clr);

    glm::vec3 getPosition(){return positionvar;}
    glm::vec3 getRotation(){return glm::eulerAngles(rotationvar);}
    glm::vec3 getScale(){return scalevar;}

    virtual ~Drawable();
};

#endif