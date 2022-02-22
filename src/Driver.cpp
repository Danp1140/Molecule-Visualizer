#include "Viewport.h"
#include <chrono>

int main(){
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
	GLFWwindow*window=glfwCreateWindow(mode->width, mode->height, "Molecule Visualizer", nullptr, nullptr);
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
	glClearColor(0, 0, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	width/=2;
	height/=2;

	FT_Library library;
	auto error=FT_Init_FreeType(&library);
	if(error) std::cout<<"FreeType Failure ("<<error<<')'<<std::endl;

	std::vector<Text> labels;
	std::vector<glm::vec3> atomverts, atomnorms, c1verts, c1norms, c2verts, c2norms, c3verts, c3norms;
	Drawable::loadOBJ("../resources/models/atomsmooth.obj", atomverts, atomnorms);
	Drawable::loadOBJ("../resources/models/singlebond.obj", c1verts, c1norms);
	Drawable::loadOBJ("../resources/models/doublebond.obj", c2verts, c2norms);
	Drawable::loadOBJ("../resources/models/triplebond.obj", c3verts, c3norms);

	bool loadpdb, uselabels;
	std::string input;
	std::cout<<"Create molecule (0), or load from PDB (1)?"<<std::endl;
	std::cin>>loadpdb;
	if(loadpdb){
		std::cout<<"Input filepath for pdb"<<std::endl;
		std::cin>>input;
	}
	std::cout<<"Render labels for atoms (yes => 1, no =>0)? (not recommended for proteins)"<<std::endl;
	std::cin>>uselabels;
	const char*pdbfilepath=input.std::string::c_str();
	Molecule m=loadpdb?Molecule(pdbfilepath):Molecule();
	m.setPos(glm::vec3(0, 0, 0));

	// if you would like to hard-code a molecule, add that code here, using m.addAtom(...) and m.addConnection(...)

	// one issue we faced here was that the order of the atoms affected functionality
	// difficult to troubleshoot, would likely require a pretty big rewrite, so tbh
	// we might just wanna leave it as-is for now.

	Camera c=Camera(window, glm::vec3(15, 15, 15), glm::vec3(0, 0, 0), ROTATE_CONTROLS);
	Viewport v=Viewport(c, window, width, height, Viewport::loadShaders("../resources/shaders/VertexShader.glsl",
	                                                                    "../resources/shaders/FragmentShader.glsl"));



	int f=0;
	float t;
	GLuint textShaderID=Viewport::loadShaders("../resources/shaders/2DVertexShader.glsl", "../resources/shaders/2DFragmentShader.glsl");
	std::vector<glm::vec2> vertices, uvs;
	if(uselabels){
		for(int x=0;x<m.getAtoms().size();x++){
			std::string message="";
			message.append(m.getAtom(x)->getAbbrev());
			message.append(std::to_string(m.getAtom(x)->getID()));
			labels.emplace_back(message, 2, "../resources/fonts/arial.ttf", library, width, height, glm::vec2(0, 0));
			labels.at(x).setTextColor(glm::vec4(0.8, 0.8, 0.8, 1));
		}
	}

	double mousex=0, mousey=0;
	bool tkey=false, ckey=false, okey=false, bkey=false;


	do{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		t=glfwGetTime();
		f++;

		glfwGetCursorPos(window, &mousex, &mousey);

		if(glfwGetKey(window, GLFW_KEY_T)==GLFW_PRESS&&tkey!=true){
			tkey=true;
			for(auto&c:m.getConnections()){
				m.torsionals(c->getAtom1(), c->getAtom2());
				m.torsionals(c->getAtom2(), c->getAtom1());
			}
			m.setPos(glm::vec3(0, 0, 0));
		}
		else if(glfwGetKey(window, GLFW_KEY_T)==GLFW_RELEASE&&tkey!=false){tkey=false;}
		if(glfwGetKey(window, GLFW_KEY_C)==GLFW_PRESS&&ckey!=true){
			ckey=true;
			m.addAtom(new Atom(6, 0, atomverts, atomnorms));
			if(m.getAtoms().size()>1){
				m.getAtom(m.getAtoms().size()-1)->addConnection(new Connection(1, m.getAtom(m.getAtoms().size()-1), m.getAtom(m.getAtoms().size()-2)));
			}
		}
		else if(glfwGetKey(window, GLFW_KEY_C)==GLFW_RELEASE&&ckey!=false){ckey=false;}
		if(glfwGetKey(window, GLFW_KEY_O)==GLFW_PRESS&&okey!=true){
			okey=true;
			m.addAtom(new Atom(8, 0, atomverts, atomnorms));
			if(m.getAtoms().size()>1){
				m.getAtom(m.getAtoms().size()-1)->addConnection(new Connection(1, m.getAtom(m.getAtoms().size()-1), m.getAtom(m.getAtoms().size()-2)));
			}
		}
		else if(glfwGetKey(window, GLFW_KEY_O)==GLFW_RELEASE&&okey!=false){okey=false;}
		if(glfwGetKey(window, GLFW_KEY_B)==GLFW_PRESS&&bkey!=true&&m.getAtoms().size()>1){
			bkey=true;
			m.branch(new Atom());
			m.setPos(glm::vec3(0, 0, 0));
		}
		else if(glfwGetKey(window, GLFW_KEY_B)==GLFW_RELEASE&&bkey!=false){bkey=false;}

		v.draw(m);

		if(uselabels){
			for(int x=0;x<labels.size();x++){
				glm::vec4 temp=glm::vec4(m.getAtom(x)->getPosition().x, m.getAtom(x)->getPosition().y,
				                         m.getAtom(x)->getPosition().z, 1.0);
				glm::vec4 temp2=v.getCamera().getPerspective()*v.getCamera().getView()*temp;
				temp2.x/=temp2.w;
				temp2.y/=temp2.w;
				temp2.z/=temp2.w;
				if((temp2.x+1)*(width/2)>width||(temp2.x+1)*(width/2)<0||(temp2.y+1)*(height/2)>height||
				   (temp2.y+1)*(height/2)<0){continue;}
				if(temp2.z<0){continue;}
				labels.at(x).setPosition(glm::vec2((temp2.x+1)*(width/2), (temp2.y+1)*(height/2)));
				labels.at(x).draw(textShaderID);
			}
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS);
	return 0;
}