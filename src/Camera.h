#ifndef CAMERA_H_
#define CAMERA_H_

#define ROTATE_CONTROLS 0
#define FLY_CONTROLS 1

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
private:
	GLFWwindow *window;
	glm::vec3 position, focus, direction, right, up;
	int width, height, controls;
	double dtime, ltime, dxpos, dypos, lxpos, lypos;
	float nearclip, farclip, horizangle, vertangle, movespeed, mousesense, horizvelocity, vertvelocity;
public:
	Camera(GLFWwindow *w, glm::vec3 p, glm::vec3 f, int c);

	void updatePos();

	glm::mat4 getView();
	glm::mat4 getPerspective();
	glm::vec3 getPosition(){return position; }
	glm::vec3 getFocus(){return focus;}
	glm::vec3 getUp(){return up;}
	float getNClip(){return nearclip;}
	float getFClip(){return farclip;}
};

#endif