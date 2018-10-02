#include "Viewport.h"

Viewport::Viewport(Camera c, GLFWwindow*w, int wdth, int hght, GLuint shaders)
		:camera(c), window(w), width(wdth), height(hght), programID(shaders), test(Drawable("resources/models/test.obj")){
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void Viewport::draw(Molecule &molecule){
	camera.updatePos();
	for(auto& atom:molecule.getAtoms()){
		atom->draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
	}
	for(auto& connection:molecule.getConnections()){
		connection->draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
	}
	test.draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
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