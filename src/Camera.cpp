#include <iostream>

#include "Camera.h"

Camera::Camera(GLFWwindow*w, glm::vec3 p, glm::vec3 f, int c)
		:window(w), position(p), focus(f), controls(c), horizvelocity(0),
		 nearclip(0.1f), farclip(1000.0f), up(glm::vec3(0, 1, 0)), mousesense(0.2), dtime(0), ltime(0){
	if(controls==FLY_CONTROLS){
//		if(position.x==0){position.x=0.01;}
//		if(position.y==0){position.y=0.01;}
//		if(position.z==0){position.z=0.01;}
		horizangle=atan((position.x-focus.x)/(position.z-focus.z));
		vertangle=atan((position.y-focus.y)/(position.z-focus.z))-3.14;
		focus=glm::vec3(cos(vertangle)*sin(horizangle), sin(vertangle), cos(vertangle)*cos(horizangle));
		movespeed=0.5;
	}else{
		float r=sqrt(pow(position.x-focus.x, 2)+pow(position.z-focus.z, 2)+pow(position.y-focus.y, 2));
		horizangle=atan2(position.z, position.x);
//		vertangle=atan2(position.y, position.z);
		vertangle=acos(position.y/r);
		movespeed=0.5;
	}
	glfwGetFramebufferSize(window, &width, &height);
	width/=2;
	height/=2;
}

void Camera::updatePos(){
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);
	dxpos=lxpos-xpos;
	dypos=lypos-ypos;
	dtime=glfwGetTime()-ltime;
	ltime=glfwGetTime();
	glfwGetCursorPos(window, &lxpos, &lypos);
	//std::cout<<dxpos<<' '<<dypos<<'\n';
	if(controls==FLY_CONTROLS){
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_FALSE);
//			std::cout<<dtime<<'\n';
			horizangle+=mousesense*dxpos*dtime;
			vertangle+=mousesense*-dypos*dtime;
//			std::cout << "horiz: " << horizangle << " vert: " << vertangle << '\n';
			focus=glm::vec3(cos(vertangle)*sin(horizangle), sin(vertangle), cos(vertangle)*cos(horizangle));
			right=glm::vec3(sin(horizangle+3.14f/2.0f), 0, cos(horizangle+3.14f/2.0f));
			up=glm::vec3(glm::cross(right, focus));
//			std::cout<<focus.x<<' '<<focus.y<<' '<<focus.z<<'\n';

			if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){position+=focus*movespeed;}
			if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){position-=focus*movespeed;}
			if(glfwGetKey(window, GLFW_KEY_D)==GLFW_PRESS){position+=right*movespeed;}
			if(glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){position-=right*movespeed;}
			if(glfwGetKey(window, GLFW_KEY_SPACE)==GLFW_PRESS){position+=glm::vec3(0, 1, 0)*movespeed;}
			if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)==GLFW_PRESS){position+=glm::vec3(0, -1, 0)*movespeed;}
		}else{glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);}
	}else if(controls==ROTATE_CONTROLS){
		float r=sqrt(pow(position.x-focus.x, 2)+pow(position.z-focus.z, 2)+pow(position.y-focus.y, 2));
		horizangle+=horizvelocity;
		vertangle+=vertvelocity;

		position=glm::vec3(r*cos(horizangle)*sin(vertangle),
		                   r*cos(vertangle),
		                   r*sin(vertangle)*sin(horizangle));
		if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT)==GLFW_PRESS){
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			horizvelocity+=dxpos*dtime*mousesense;
			vertvelocity+=dypos*dtime*mousesense*0.75;
//			if(vertangle<0.05||vertangle>3.09){vertvelocity+=0.01;}
			if(glfwGetKey(window, GLFW_KEY_W)==GLFW_PRESS){position-=glm::vec3(0.05, 0.05, 0.05)*glm::vec3(r*cos(horizangle)*sin(vertangle), r*cos(vertangle), r*sin(horizangle)*sin(vertangle));}
			if(glfwGetKey(window, GLFW_KEY_S)==GLFW_PRESS){position+=glm::vec3(0.05, 0.05, 0.05)*glm::vec3(r*cos(horizangle)*sin(vertangle), r*cos(vertangle), r*sin(horizangle)*sin(vertangle));}
		}
		else{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			if(horizvelocity>0){horizvelocity*=0.95;}
			else if(horizvelocity<0){horizvelocity*=0.95;}
			if(vertvelocity>0){vertvelocity*=0.95;}
			else if(vertvelocity<0){vertvelocity*=0.95;}
//			if(vertangle<0.05||vertangle>3.09){vertvelocity*=0.05;}
		}



//		std::cout<<vertangle<<'\n';

//		if(vertangle<0){up=glm::vec3(0, -1, 0);}
//		if(vertangle>0){up=glm::vec3(0, 1, 0);}
//		if(vertangle>3.14){up=glm::vec3(0, 1, 0);}
//		std::cout<<position.x<<"   "<<position.y<<"   "<<position.z<<'\n';




	}
}

glm::mat4 Camera::getPerspective(){
//	std::cout<<"Width: "<<width<<" Height: "<<height<<'\n';
	return glm::mat4(glm::perspective(glm::radians(45.0f), (float)width/(float)height, nearclip, farclip));
//	return glm::mat4(glm::ortho(0.0f, (float)width, 0.0f, (float)height, nearclip, farclip));
}

glm::mat4 Camera::getView(){
//	std::cout<<"Position x: "<<position.x<<" Position y: "<<position.y<<" Position z: "<<position.z/*r<<"\nFocus x: " <<focus.x<<" Focus y: "
//									 <<focus.y<<" Focus z: "<<focus.z*/<<'\n';
	//x=-5.65, y=5.65
//	std::cout<<"Up: ("<<up.x<<", "<<up.y<<", "<<up.z<<")\n";
	if(controls==FLY_CONTROLS){return glm::mat4(glm::lookAt(position, focus+position, up));}
	return glm::mat4(glm::lookAt(position, focus, up));
}