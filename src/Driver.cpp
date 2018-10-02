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

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	width/=2;
	height/=2;

	Molecule m=Molecule();

//	===| | = x
//	====== = z
//	=====> = y
		//Hydrogen
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Water
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(1)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Methyl
	m.addAtom(new Atom(6, 0));
	m.addAtom(new Atom(1, 0));
	m.addAtom(new Atom(1, 0));
	m.addAtom(new Atom(1, 0));
	m.addAtom(new Atom(1, 0));
	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
	m.branch(new Atom());
	m.setPos(glm::vec3(0,0,0));
		//Ammonia
//	m.addAtom(new Atom(7, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Sulpher Dioxide
//	m.addAtom(new Atom(16, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addConnection(new Connection(2, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(2, m.getAtom(0), m.getAtom(2)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Boron Trifluoride
//	m.addAtom(new Atom(5, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Glycine
//	for(int x=0;x<5;x++){
//		m.addAtom(new Atom(1, 0));
//	}
//	m.addAtom(new Atom(7, 0));
//	m.addAtom(new Atom(6, 0));
//	m.addAtom(new Atom(6, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addConnection(new Connection(1, m.getAtom(5), m.getAtom(0)));
//	m.addConnection(new Connection(1, m.getAtom(5), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(5)));
//	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(7), m.getAtom(6)));
//	m.addConnection(new Connection(2, m.getAtom(7), m.getAtom(8)));
//	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(7)));
//	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(3)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Lysine
//	for(int x=0;x<14;x++){
//		m.addAtom(new Atom(1, 0));
//	}
//	m.addAtom(new Atom(7, 0));
//	m.addAtom(new Atom(7, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(8, 0));
//	for(int x=0;x<6;x++){
//		m.addAtom(new Atom(6, 0));
//	}
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(14)));
//	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(14)));
//	m.addConnection(new Connection(1, m.getAtom(18), m.getAtom(14)));
//	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(18)));
//	m.addConnection(new Connection(1, m.getAtom(13), m.getAtom(18)));
//	m.addConnection(new Connection(1, m.getAtom(19), m.getAtom(18)));
//	m.addConnection(new Connection(1, m.getAtom(3), m.getAtom(19)));
//	m.addConnection(new Connection(1, m.getAtom(12), m.getAtom(19)));
//	m.addConnection(new Connection(1, m.getAtom(20), m.getAtom(19)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(20)));
//	m.addConnection(new Connection(1, m.getAtom(11), m.getAtom(20)));
//	m.addConnection(new Connection(1, m.getAtom(21), m.getAtom(20)));
//	m.addConnection(new Connection(1, m.getAtom(5), m.getAtom(21)));
//	m.addConnection(new Connection(1, m.getAtom(10), m.getAtom(21)));
//	m.addConnection(new Connection(1, m.getAtom(22), m.getAtom(21)));
//	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(22)));
//	m.addConnection(new Connection(1, m.getAtom(15), m.getAtom(22)));
//	m.addConnection(new Connection(1, m.getAtom(23), m.getAtom(22)));
//	m.addConnection(new Connection(1, m.getAtom(8), m.getAtom(15)));
//	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(15)));
//	m.addConnection(new Connection(2, m.getAtom(16), m.getAtom(23)));
//	m.addConnection(new Connection(1, m.getAtom(7), m.getAtom(17)));
//	m.addConnection(new Connection(1, m.getAtom(17), m.getAtom(23)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Benzene Ring
//	for(int x=0;x<6;x++){
//		m.addAtom(new Atom(6, 0));
//		m.addAtom(new Atom(1, 0));
//	}
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(5)));
//	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(7)));
//	m.addConnection(new Connection(1, m.getAtom(8), m.getAtom(9)));
//	m.addConnection(new Connection(1, m.getAtom(10), m.getAtom(11)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(2, m.getAtom(2), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(6)));
//	m.addConnection(new Connection(2, m.getAtom(6), m.getAtom(8)));
//	m.addConnection(new Connection(1, m.getAtom(8), m.getAtom(10)));
//	m.addConnection(new Connection(1, m.getAtom(10), m.getAtom(0)));
//	m.branch(new Atom());

	Camera c=Camera(window, glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), FLY_CONTROLS);
	//fix orbital camera
	Viewport v=Viewport(c, window, width, height, Viewport::loadShaders("resources/shaders/VertexShader.glsl",
	                                                                    "resources/shaders/FragmentShader.glsl"));

	glClearColor(0, 0, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);


	do{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

		m.getAtom(1)->Atom::setRot(m.getAtom(1)->Atom::getRotation()+glm::vec2(glm::radians(1.0), glm::radians(1.0)));
		m.branch(new Atom());
//		m.setPos(glm::vec3(0,0,0));

		v.draw(m);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS);


	return 0;
}