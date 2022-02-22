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

	explicit Drawable(const std::vector<glm::vec3>&verts, const std::vector<glm::vec3>&norms);

    virtual void draw(glm::mat4 viewmat, glm::mat4 projectmat, GLuint shader, glm::vec3 camPos);

	static bool loadOBJ(const char* obj_filepath, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals);

    void setPos(glm::vec3 pos);
    void setRot(glm::quat angles);
    void setScl(glm::vec3 scl);
    void setVN(const std::vector<glm::vec3>&v, const std::vector<glm::vec3>&n);
    void setClr(glm::vec3 clr);

    glm::vec3 getPosition(){return positionvar;}
    glm::quat getRotation(){return rotationvar;}
    glm::vec3 getScale(){return scalevar;}
    std::vector<glm::vec3> getVerts(){return verticies;}
    std::vector<glm::vec3> getNorms(){return normals;}

    virtual ~Drawable();
};

#endif