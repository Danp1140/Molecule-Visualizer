#include "Molecule.h"
#include "PeriodicTable.h"
#include "Viewport.h"

int main(){
	//Init
	if(!glfwInit()){
		std::cout<<"GLFW Failure ("<<stderr<<")\n";
		return -1;
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	const GLFWvidmode*mode=glfwGetVideoMode(glfwGetPrimaryMonitor());
	GLFWwindow*window=glfwCreateWindow(mode->width, mode->height, "Molecule Visualizer", glfwGetPrimaryMonitor(),
	                                   nullptr);
	if(window==nullptr){
		std::cout<<"Window Failure ("<<stderr<<")\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	if(glewInit()!=GLEW_OK){
		std::cout<<"GLEW Failure ("<<stderr<<")\n";
		return -1;
	}
	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<"\n";
	std::cout<<"GLSL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<"\n";
	std::cout<<"GLFW version: "<<glfwGetVersionString()<<'\n';

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	width/=2;
	height/=2;


	Camera c=Camera(window, glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), ROTATE_CONTROLS);
	Viewport v=Viewport(c, window, width, height, Viewport::loadShaders("resources/shaders/VertexShader.glsl",
	                                                                    "resources/shaders/FragmentShader.glsl"));
//	Drawable test=Drawable("resources/models/atomsmooth.obj");
//	Drawable test2=Drawable("resources/models/atomsmooth.obj");
//	test2.setPos(glm::vec3(1,1,1));
//	Drawable test=Drawable("resources/models/atomsmooth.obj");
//	v.addDrawable(&test);
//	v.addDrawable(&test2);

	Atom a1=Atom(7, 0);
	a1.setPos(glm::vec3(0,0,-2));
	Atom a2=Atom(8, 0);
	a2.setPos(glm::vec3(0,0,2));
	Connection c1=Connection(2, &a1, &a2);


	Molecule m=Molecule();
	m.addAtom(a1);
	m.addAtom(a2);
	m.addConnection(c1);

//	v.addDrawable(&a1);
//	v.addDrawable(&a2);
//	v.addDrawable(&c1);
		v.addDrawable(&m);

	glClearColor(0, 0, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	//Main loop
	do{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);



		//Investigate depth buffer bit

		v.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS);

	return 0;
}