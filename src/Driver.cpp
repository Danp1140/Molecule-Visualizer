#include "Viewport.h"
#include <btBulletDynamicsCommon.h>
#include <chrono>

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


	btBroadphaseInterface*broadphase=new btDbvtBroadphase();
	btDefaultCollisionConfiguration*collisionConfiguration=new btDefaultCollisionConfiguration();
	btCollisionDispatcher*dispatcher=new btCollisionDispatcher(collisionConfiguration);
	btSequentialImpulseConstraintSolver*solver=new btSequentialImpulseConstraintSolver;
	btDiscreteDynamicsWorld*dynamicsWorld=new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -9.81, 0));


	std::cout<<"OpenGL version: "<<glGetString(GL_VERSION)<<"\n";
	std::cout<<"GLSL version: "<<glGetString(GL_SHADING_LANGUAGE_VERSION)<<"\n";
	std::cout<<"GLFW version: "<<glfwGetVersionString()<<'\n';
	std::cout<<"BulletPhysics verion: "<<BT_BULLET_VERSION<<'\n';

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	width/=2;
	height/=2;
	glfwPollEvents();

	FT_Library library;
	auto error=FT_Init_FreeType(&library);
	if(error){std::cout<<"FreeType Failure ("<<error<<')'<<std::endl;}

	std::vector<Text> labels;


	std::vector<glm::vec3> atomverts, atomnorms, c1verts, c1norms, c2verts, c2norms, c3verts, c3norms;
	Drawable::loadOBJ("resources/models/atomsmooth.obj", atomverts, atomnorms);
	Drawable::loadOBJ("resources/models/singlebond.obj", c1verts, c1norms);
	Drawable::loadOBJ("resources/models/doublebond.obj", c2verts, c2norms);
	Drawable::loadOBJ("resources/models/triplebond.obj", c3verts, c3norms);

	bool temp;
	Molecule m;
	std::cout<<"Load from PDB (0), or create molecule (1)?"<<std::endl;
	std::cin>>temp;
	if(temp){m=Molecule();}
	else{
		std::string input;
		std::cout<<"Input filepath for pdb"<<std::endl;
		std::cin>>input;
		const char*temp=input.std::string::c_str();
		std::cout<<"\""<<temp<<"\""<<std::endl;
		m=Molecule(temp);
//		m=Molecule("resources/pdbs/insulin.pdb");
	}

	for(auto&a:m.getAtoms()){
		std::cout<<a->getPDBName()<<"\n\t"<<a->getResidue()<<std::endl;
	}

//	Molecule m=Molecule("resources/pdbs/insulin.pdb");
	m.setPos(glm::vec3(0, 0, 0));
//	Molecule m=Molecule();

//	===| | = x
//	====== = z
//	=====> = y
		//Ethanol
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(6, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(6, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(8, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(1, 0, atomverts, atomnorms));
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
//	m.addAtom(new Atom(15, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(17, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(17, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(17, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(17, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(17, 0, atomverts, atomnorms));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(2)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(5)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));
		//Sulfur Tetrafluoride
//	m.addAtom(new Atom(16, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(9, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(9, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(9, 0, atomverts, atomnorms));
//	m.addAtom(new Atom(9, 0, atomverts, atomnorms));
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
//	m.setPos(glm::vec3(0,0,0));
		//Lysine
	for(int x=0;x<14;x++){
		m.addAtom(new Atom(1, 0, atomverts, atomnorms));
	}
	m.addAtom(new Atom(7, 0, atomverts, atomnorms));
	m.addAtom(new Atom(7, 0, atomverts, atomnorms));
	m.addAtom(new Atom(8, 0, atomverts, atomnorms));
	m.addAtom(new Atom(8, 0, atomverts, atomnorms));
	for(int x=0;x<6;x++){
		m.addAtom(new Atom(6, 0, atomverts, atomnorms));
	}
	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(14)));
	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(14)));
	m.addConnection(new Connection(1, m.getAtom(18), m.getAtom(14)));
	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(18)));
	m.addConnection(new Connection(1, m.getAtom(13), m.getAtom(18)));
	m.addConnection(new Connection(1, m.getAtom(19), m.getAtom(18)));
	m.addConnection(new Connection(1, m.getAtom(3), m.getAtom(19)));
	m.addConnection(new Connection(1, m.getAtom(12), m.getAtom(19)));
	m.addConnection(new Connection(1, m.getAtom(20), m.getAtom(19)));
	m.addConnection(new Connection(1, m.getAtom(4), m.getAtom(20)));
	m.addConnection(new Connection(1, m.getAtom(11), m.getAtom(20)));
	m.addConnection(new Connection(1, m.getAtom(21), m.getAtom(20)));
	m.addConnection(new Connection(1, m.getAtom(5), m.getAtom(21)));
	m.addConnection(new Connection(1, m.getAtom(10), m.getAtom(21)));
	m.addConnection(new Connection(1, m.getAtom(22), m.getAtom(21)));
	m.addConnection(new Connection(1, m.getAtom(6), m.getAtom(22)));
	m.addConnection(new Connection(1, m.getAtom(15), m.getAtom(22)));
	m.addConnection(new Connection(1, m.getAtom(23), m.getAtom(22)));
	m.addConnection(new Connection(1, m.getAtom(8), m.getAtom(15)));
	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(15)));
	m.addConnection(new Connection(2, m.getAtom(16), m.getAtom(23)));
	m.addConnection(new Connection(1, m.getAtom(7), m.getAtom(17)));
	m.addConnection(new Connection(1, m.getAtom(17), m.getAtom(23)));
	m.branch(new Atom());
	m.setPos(glm::vec3(0,0,0));
		//Benzene Ring
//	for(int x=0;x<6;x++){
//		m.addAtom(new Atom(6, 0, atomverts, atomnorms));
//		m.addAtom(new Atom(1, 0, atomverts, atomnorms));
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
//  m.setPos(glm::vec3(0, 0, 0));
		//Pyrrole
//	for(int x=0;x<4;x++){m.addAtom(new Atom(6, 0, atomverts, atomnorms));}
//	for(int x=0;x<5;x++){m.addAtom(new Atom(1, 0, atomverts, atomnorms));}
//	m.addAtom(new Atom(7, 0, atomverts, atomnorms));
//	m.addConnection(new Connection(1, m.getAtom(0), m.getAtom(4)));
//	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(5)));
//	m.addConnection(new Connection(1, m.getAtom(2), m.getAtom(6)));
//	m.addConnection(new Connection(1, m.getAtom(3), m.getAtom(7)));
//	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(8)));
//	m.addConnection(new Connection(2, m.getAtom(0), m.getAtom(1)));
//	m.addConnection(new Connection(1, m.getAtom(1), m.getAtom(2)));
//	m.addConnection(new Connection(2, m.getAtom(2), m.getAtom(3)));
//	m.addConnection(new Connection(1, m.getAtom(3), m.getAtom(9)));
//	m.addConnection(new Connection(1, m.getAtom(9), m.getAtom(0)));
//	m.branch(new Atom());
//	m.setPos(glm::vec3(0, 0, 0));

	//possible torsional calculator: closer atoms repel, further atoms attract, run for a hot second

	Camera c=Camera(window, glm::vec3(15, 15, 15), glm::vec3(0, 0, 0), ROTATE_CONTROLS);
	//fix orbital camera
	Viewport v=Viewport(c, window, width, height, Viewport::loadShaders("resources/shaders/VertexShader.glsl",
	                                                                    "resources/shaders/FragmentShader.glsl"));

	glClearColor(0, 0, 0.1, 1);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

//	GLuint textshades=Viewport::loadShaders("resources/shaders/2DVertexShader.glsl", "resources/shaders/2DFragmentShader.glsl");

	int f=0, selectid=0;
	float t=0.0;
	bool right;
//	GLuint texture=Viewport::loadBMP("resources/texture.bmp");
	GLuint textShaderID=Viewport::loadShaders("resources/shaders/2DVertexShader.glsl", "resources/shaders/2DFragmentShader.glsl");
	std::vector<glm::vec2> vertices, uvs;
//	for(int x=0;x<10;x++){
//		std::string message="";
//		message.append("Atom:\n");
//		message.append(m.getAtom(x+14)->getAbbrev());
//		message.append(" ");
//		message.append(std::to_string(m.getAtom(x+14)->getID()));
//		labels.push_back(Text(message, 2, "resources/fonts/arial.ttf", library, width, height, glm::vec2(0, 0)));
//		labels.at(x).setTextColor(glm::vec4(0.8, 0.8, 0.8, 1));
//	}
//
//	Text label;
//	std::string message="";
//	message.append("Atom:\n");
//	message.append(m.getAtom(0)->getAbbrev());
//	message.append(" ");
//	message.append(std::to_string(m.getAtom(0)->getID()));
//	label=Text(message, 2, "resources/fonts/arial.ttf", library, width, height, glm::vec2(0, 0));
//	label.setTextColor(glm::vec4(0.8, 0.8, 0.8, 1));

	double mousex=0, mousey=0;

	btCollisionShape*sphereTest=new btSphereShape(btScalar(100.0f));

	btDefaultMotionState*ms=new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(0, ms, sphereTest, btVector3(0, 0, 0));
	btRigidBody*testRB=new btRigidBody(rigidBodyCI);
	dynamicsWorld->addRigidBody(testRB);

//	m.torsionals(m.getAtom(6), m.getAtom(7), 0.0f);
//	m.torsionals(m.getAtom(5), m.getAtom(6), 0.0f);

//	m.torsionals(m.getAtom(20), m.getAtom(19), t*0.001);
//	m.torsionals(m.getAtom(21), m.getAtom(20), t*0.001);

	bool tkey=false, ckey=false, okey=false, bkey=false;

	glClearColor(0, 0, 0.1, 1);

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


//		glm::vec4 raystart=glm::vec4(((float)mousex/(float)width-0.5)*2, ((float)mousey/(float)height-0.5)*2, -1, 1);
//		glm::vec4 rayend=glm::vec4(((float)mousex/(float)width-0.5)*2, ((float)mousey/(float)height-0.5)*2, 0, 1);
//
//		glm::vec4 raystartc=glm::inverse(c.getPerspective())*raystart; raystartc/=raystartc.w;
//		glm::vec4 raystartw=glm::inverse(c.getView())*raystartc; raystartw/=raystartw.w;
//		glm::vec4 rayendc=glm::inverse(c.getPerspective())*rayend; rayendc/=rayendc.w;
//		glm::vec4 rayendw=glm::inverse(c.getView())*rayendc; rayendw/=rayendw.w;

//		glm::vec3 raydirection=glm::vec3(rayendw-raystartw);
//		raydirection=glm::normalize(raydirection);

//		std::cout<<"Raycast Direction:\n\tx: "<<raydirection.x<<"\n\ty: "<<raydirection.y<<"\n\tz: "<<raydirection.z<<std::endl;

//		glm::vec3 origin=glm::vec3(raystartw);
//		glm::vec3 direction=glm::normalize(raydirection);
//`
//		btCollisionWorld::ClosestRayResultCallback RayCallback(btVector3(origin.x, origin.y, origin.z), btVector3(outend.x, outend.y, outend.z));
//		dynamicsWorld->rayTest(btVector3(origin.x, origin.y, origin.z), btVector3(outend.x, outend.y, outend.z), RayCallback);
//		if(RayCallback.hasHit()){glClearColor(1, 1, 1, 1); std::cout<<"hit"<<std::endl;}
//		m.getAtom(0)->setPos(outend);

//		if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_PRESS&&right!=true){
//			right=true;
//			selectid++;
//
//			std::string message="";
//			message.append("Atom:\n");
//			message.append(m.getAtom(selectid)->getAbbrev());
//			message.append(" ");
//			message.append(std::to_string(m.getAtom(selectid)->getID()));
//			label.setMessage(message);
//		}
//		else if(glfwGetKey(window, GLFW_KEY_RIGHT)==GLFW_RELEASE&&right!=false){
//			right=false;
//		}

//		m.torsionals(m.getAtom(6), m.getAtom(7), t*0.001);
//		m.torsionals(m.getAtom(21), m.getAtom(20), t*0.001);

		v.draw(m);

//		for(int x=0;x<10;x++){
//			glm::vec4 temp=glm::vec4(m.getAtom(x+14)->getPosition().x, m.getAtom(x+14)->getPosition().y, m.getAtom(x+14)->getPosition().z, 1.0);
//			glm::vec4 temp2=v.getCamera().getPerspective()*v.getCamera().getView()*temp;
//			temp2.x/=temp2.w;
//			temp2.y/=temp2.w;
//			temp2.z/=temp2.w;
//			if((temp2.x+1)*(width/2)>width||(temp2.x+1)*(width/2)<0||(temp2.y+1)*(height/2)>height||(temp2.y+1)*(height/2)<0){continue;}
//			if(temp2.z<0){continue;}
//			labels.at(x).setPosition(glm::vec2((temp2.x+1)*(width/2), (temp2.y+1)*(height/2)));
//			labels.at(x).draw(textShaderID);
//		}

//		std::cout<<f<<"  "<<t<<std::endl;
//		std::cout<<(f/t)<<std::endl;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}while(!glfwWindowShouldClose(window)&&glfwGetKey(window, GLFW_KEY_ESCAPE)!=GLFW_PRESS);
	return 0;
}