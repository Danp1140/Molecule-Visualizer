#include "Viewport.h"
#include <chrono>
//#include "libDrawText/drawtext.h"

//struct dtx_font *font;

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
	GLFWwindow*window=glfwCreateWindow(mode->width, mode->height, "Molecule Visualizer", nullptr,
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
	glfwPollEvents();

	std::vector<glm::vec3> atomverts, atomnorms, c1verts, c1norms, c2verts, c2norms, c3verts, c3norms;
	Drawable::loadOBJ("resources/models/atomsmooth.obj", atomverts, atomnorms);
	Drawable::loadOBJ("resources/models/singlebond.obj", c1verts, c1norms);
	Drawable::loadOBJ("resources/models/doublebond.obj", c2verts, c2norms);
	Drawable::loadOBJ("resources/models/triplebond.obj", c3verts, c3norms);


//	std::ofstream file;
//	file.open("OBJMiddleman.txt");
//	file<<"std::vector<glm::vec3>{\n";
//	for(int x=0;x<c2norms.size();x++){
//		file<<"    glm::vec3("<<c2norms.at(x).x<<", "<<c2norms.at(x).y<<", "<<c2norms.at(x).z<<"),\n";
//	}
//	file<<"}";
//	file.close();

//	std::cout<<"Type filepath for imported PDB"<<std::endl;
//	std::string strtemp;
//	std::cin>>strtemp;
//	Molecule m=Molecule(const_cast<char*>(strtemp));
	Molecule m=Molecule("resources/pdbs/insulin.pdb");
	m.setPos(glm::vec3(0, 0, 0));

//	Molecule m=Molecule();
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.branch(new Atom());
//	auto start=std::chrono::high_resolution_clock::now();
//	Molecule m=Molecule("resources/pdbs/insulin.pdb");
//	auto end=std::chrono::high_resolution_clock::now();
//	m.setPos(glm::vec3(0,0,0));
//	std::cout<<"Time elapsed importing pdb: "<<std::chrono::duration_cast<std::chrono::seconds>(end-start).count()<<" seconds ("<<
//	std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count()<<" milliseconds)"<<std::endl;

//	===| | = x
//	====== = z
//	=====> = y
//	m.addAtom(new Atom("N", glm::vec3(0,0,0)));
		//Ethanol
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(6, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(6, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(5)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(6)));
//	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(7)));
//	m.addConnection(new Connection(1, m.getAtom(7), m.getAtom(8)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Hydrogen
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
////	m.getAtom(0)->setRot(glm::vec2(glm::radians(45.0), 0.0));
//	m.branch(new Atom());
//	m.torsionals();
//	m.setPos(glm::vec3(0,0,0));
		//Water
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(8, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(1)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Beryllium Chloride
//	m.addAtom(new Atom(4, 0));
//	m.addAtom(new Atom(17, 0));
////	m.getAtom(1)->setRot(glm::vec2(45.0, 0.0));
//	m.addAtom(new Atom(17, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
		//Methane
//	m.addAtom(new Atom(6, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addAtom(new Atom(1, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0,0,0));
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
		//Sulphur Dioxide
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
		//Phosphorus Pentachloride
//	m.addAtom(new Atom(15, 0));
//	m.addAtom(new Atom(17, 0));
//	m.addAtom(new Atom(17, 0));
//	m.addAtom(new Atom(17, 0));
//	m.addAtom(new Atom(17, 0));
//	m.addAtom(new Atom(17, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(5)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Sulfur Tetrafluoride
//	m.addAtom(new Atom(16, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Chlorine Trifluoride
//	m.addAtom(new Atom(17, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Xenon Difluoride
//	m.addAtom(new Atom(54, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Sulfur Hexafluoride
//	m.addAtom(new Atom(16, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(5)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(6)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Bromine Pentafluoride
//	m.addAtom(new Atom(35, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(5)));
//	m.branch(new Atom());
		//Xenon Tetrafluoride
//	m.addAtom(new Atom(54, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addAtom(new Atom(9, 0));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.branch(new Atom());
		//Glycine
//	for(int x=0;x<5;x++){
//		m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	}
//	m.addAtom(new Atom(7, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(6, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(6, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(8, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(8, 0, atomverts, atomnorms));
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
//	m.torsionals(0.0);
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
//	m.addConnection(new Connection(2, m.getAtom(10), m.getAtom(0)));
//	m.branch(new Atom());

	//possible torsional calculator: closer atoms repel, further atoms attract, run for a hot second

	Camera c=Camera(window, glm::vec3(15, 15, 15), glm::vec3(0, 0, 0), FLY_CONTROLS);
	//fix orbital camera
	Viewport v=Viewport(c, window, width, height, Viewport::loadShaders("resources/shaders/VertexShader.glsl",
	                                                                    "resources/shaders/FragmentShader.glsl"));

	glClearColor(0, 0, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
//	glDepthFunc(GL_ALWAYS);
	glDepthFunc(GL_LESS);

//	m.addAtom(new Atom(8, 0));

	//1 WORLD UNIT=74pm (standard bond model size applies to O2 covalent bond)
	//1 PDB UNIT=2.76 WORLD UNITS

//	GLuint textshades=Viewport::loadShaders("resources/shaders/TextVertexShader.glsl", "resources/shaders/TextFragmentShader.glsl");

//	if(!(font = dtx_open_font_glyphmap("resources/serif_s24.glyphmap"))) {
//		std::cout<<"failed to open font\n";
//		return 1;
//	}
//	dtx_use_font(font, 24);
//	float t;
	int f=0, selectid=0;
	float t=0.0;
	do{
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		t=glfwGetTime();
		f++;

		if(glfwGetKey(window, GLFW_KEY_O)==GLFW_PRESS){
			Atom*atemp=new Atom(8, 0, atomverts, atomnorms);
			if(Connection::numTest(m.getAtom(selectid), atemp, 1)){
				m.addAtom(atemp);
				m.addConnection(new Connection(1, m.getAtom(selectid), m.getAtom(m.getAtoms().size()-1)));
			}
			m.branch(new Atom());
		}
		if(glfwGetKey(window, GLFW_KEY_C)==GLFW_PRESS){
			Atom*atemp=new Atom(6, 0, atomverts, atomnorms);
			if(Connection::numTest(m.getAtom(selectid), atemp, 1)){
				m.addAtom(atemp);
				m.addConnection(new Connection(1, m.getAtom(selectid), m.getAtom(m.getAtoms().size()-1)));
			}
			m.branch(new Atom());
		}
		if(glfwGetKey(window, GLFW_KEY_H)==GLFW_PRESS){
			Atom*atemp=new Atom(1, 0, atomverts, atomnorms);
			if(Connection::numTest(m.getAtom(selectid), atemp, 1)){
				m.addAtom(atemp);
				m.addConnection(new Connection(1, m.getAtom(selectid), m.getAtom(m.getAtoms().size()-1)));
			}
			m.branch(new Atom());
		}
		if(glfwGetKey(window, GLFW_KEY_N)==GLFW_PRESS){
			Atom*atemp=new Atom(7, 0, atomverts, atomnorms);
			if(Connection::numTest(m.getAtom(selectid), atemp, 1)){
				m.addAtom(atemp);
				m.addConnection(new Connection(1, m.getAtom(selectid), m.getAtom(m.getAtoms().size()-1)));
			}
			m.branch(new Atom());
		}
//		std::cout<<"here"<<std::endl;
		if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS){
			selectid++;
			if(selectid>m.getAtoms().size()-1){selectid=0;}
//			std::cout<<selectid<<std::endl;
			m.getAtom(selectid)->setClr(m.getAtom(selectid)->getColor()+glm::vec3(0.2, 0.2, 0.2));
			if(selectid==0){m.getAtom(m.getAtoms().size()-1)->setClr(m.getAtom(m.getAtoms().size()-1)->getColor()-glm::vec3(0.2, 0.2, 0.2));}
			else{m.getAtom(selectid-1)->setClr(m.getAtom(selectid-1)->getColor()-glm::vec3(0.2, 0.2, 0.2));}
		}
//		std::cout<<"there"<<std::endl;
		if(glfwGetKey(window, GLFW_KEY_LEFT)==GLFW_PRESS){
			selectid--;
			if(selectid<0){selectid=m.getAtoms().size()-1;}
//			std::cout<<selectid<<std::endl;
			m.getAtom(selectid)->setClr(m.getAtom(selectid)->getColor()+glm::vec3(0.2, 0.2, 0.2));
			if(selectid==m.getAtoms().size()-1){m.getAtom(0)->setClr(m.getAtom(0)->getColor()-glm::vec3(0.2, 0.2, 0.2));}
			else{m.getAtom(selectid+1)->setClr(m.getAtom(selectid+1)->getColor()-glm::vec3(0.2, 0.2, 0.2));}
		}

//		m.getAtom(1)->Atom::setRot(m.getAtom(1)->Atom::getRotation()+glm::vec2(glm::radians(1.0), glm::radians(1.0)));
//		m.branch(new Atom());
//		m.setPos(glm::vec3(0,0,0));

//		m.branch(new Atom());
//		m.torsionals(t);
//		m.setPos(glm::vec3(0, 0, 0));

		v.draw(m);

//		std::cout<<f<<"  "<<t<<std::endl;
//		std::cout<<(f/t)<<std::endl;

		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS);

	return 0;
}