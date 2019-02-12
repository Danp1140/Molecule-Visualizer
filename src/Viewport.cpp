#include "Viewport.h"

Viewport::Viewport(Camera c, GLFWwindow*w, int wdth, int hght, GLuint shaders)
		:camera(c), window(w), width(wdth), height(hght), programID(shaders), test(Drawable()){
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void Viewport::draw(Molecule &molecule){
	camera.updatePos();
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)==GLFW_PRESS){
//		this->obbCheck(molecule.getAtom(0));
//		for(auto& a:molecule.getAtoms()){
////			if(this->obbCheck(a)){std::cout<<"yes\n";}
//		}
//		for(auto& c:molecule.getConnections()){
////			if(this->obbCheck(c)){std::cout<<"sey\n";}
//		}
//	}
	for(auto& atom:molecule.getAtoms()){
		atom->draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
	}
	for(auto& connection:molecule.getConnections()){
		connection->draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
	}
	test.draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
}

bool Viewport::obbCheck(Drawable *d){
//	double xpos, ypos, xmax, xmin, ymax, ymin, zmax, zmin;
//	glm::mat4 m=glm::translate(d->getPosition());
//	glm::mat4 m=glm::translate(glm::vec3(0, 0, 0));
//	glfwGetCursorPos(window, &xpos, &ypos);
//	xpos-=width/2; ypos-=height/2;
//	ypos=-ypos;
//	ypos=abs(ypos-width-1);
//	glm::vec4 viewport=glm::vec4(0, 0, width, height);
//	glm::vec3 screenPos=glm::vec3(xpos, ypos, 1.0);
//	glm::vec3 worldPos=glm::unProject(screenPos, camera.getView(), camera.getPerspective(), viewport);
//	worldPos/=worldPos.z*-1;
//	glm::vec3 near=glm::vec3(xpos/10000, ypos/10000, camera.getNClip());
//	glm::vec3 far=glm::vec3(xpos/100, ypos/100, camera.getFClip()/100);
//	glm::vec3 worldPos=far-near;
//	xpos=0; ypos=0;
//	GLfloat *z=new GLfloat[1];
//	GLfloat z[3];
//	GLfloat z[width*height*4];
//	glReadPixels(xpos, ypos, 1, 1, GL_RGB, GL_FLOAT, &z);
//	glm::vec3 worldPos=glm::unProject(glm::vec3(xpos, ypos, *z), m, camera.getPerspective(), glm::vec4(0, 0, width, height));
//	std::cout<<z[0]<<"   "<<z[1]<<"   "<<z[2]<<'\n';
//	*z=0.0;
//	delete[] z;
//	worldPos*=glm::vec3(-3, -3, -3);
//	test.setPos(worldPos);
//	std::cout<<worldPos.x<<"   "<<worldPos.y<<"   "<<worldPos.z<<'\n';
//	std::cout<<xpos<<"   "<<ypos<<'\n';

	return false;
}

GLuint Viewport::loadShaders(const char*vertex_shader_filepath, const char*fragment_shader_filepath){
	GLuint VertexShaderID=glCreateShader(GL_VERTEX_SHADER);
	GLuint FragmentShaderID=glCreateShader(GL_FRAGMENT_SHADER);
	std::string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_filepath, std::ios::in);
	if(VertexShaderStream.is_open()){
		std::stringstream sstr;
		sstr<<VertexShaderStream.rdbuf();
		VertexShaderCode=sstr.str();
		VertexShaderStream.close();
	}else{
		std::cout<<"Vertex Shader File Initialization Failure ("<<vertex_shader_filepath<<")\n";
		getchar();
		return 0;
	}
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_filepath, std::ios::in);
	if(FragmentShaderStream.is_open()){
		std::stringstream sstr;
		sstr<<FragmentShaderStream.rdbuf();
		FragmentShaderCode=sstr.str();
		FragmentShaderStream.close();
	}
	GLint Result=GL_FALSE;
	int InfoLogLength;
	const char*VertexSourcePointer=VertexShaderCode.c_str();
	glShaderSource(VertexShaderID, 1, &VertexSourcePointer, nullptr);
	glCompileShader(VertexShaderID);
	glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(VertexShaderID, InfoLogLength, nullptr, &VertexShaderErrorMessage[0]);
		std::cout<<&VertexShaderErrorMessage[0]<<'\n';
	}
	const char*FragmentSourcePointer=FragmentShaderCode.c_str();
	glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, nullptr);
	glCompileShader(FragmentShaderID);
	glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
	glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
		glGetShaderInfoLog(FragmentShaderID, InfoLogLength, nullptr, &FragmentShaderErrorMessage[0]);
		std::cout<<&FragmentShaderErrorMessage[0]<<'\n';
	}
	GLuint ProgramID=glCreateProgram();
	glAttachShader(ProgramID, VertexShaderID);
	glAttachShader(ProgramID, FragmentShaderID);
	glLinkProgram(ProgramID);
	glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
	glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
	if(InfoLogLength>0){
		std::vector<char> ProgramErrorMessage(InfoLogLength+1);
		glGetProgramInfoLog(ProgramID, InfoLogLength, nullptr, &ProgramErrorMessage[0]);
		std::cout<<&ProgramErrorMessage[0]<<'\n';
	}
	glDetachShader(ProgramID, VertexShaderID);
	glDetachShader(ProgramID, FragmentShaderID);
	glDeleteShader(VertexShaderID);
	glDeleteShader(FragmentShaderID);
	return ProgramID;
}