#include "Viewport.h"

Viewport::Viewport(Camera c, GLFWwindow*w, int wdth, int hght, GLuint shaders)
		:camera(c), window(w), width(wdth), height(hght), programID(shaders), test(Drawable()){
	textID=Viewport::loadShaders("../resources/shaders/2DVertexShader.glsl", "../resources/shaders/2DFragmentShader.glsl");
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
//	test.draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
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

GLuint Viewport::loadBMP(const char* imagepath){
	unsigned char header[54];
	unsigned int dataPos, width, height, imageSize;
	unsigned char*data;

	FILE*file=fopen(imagepath, "rb");
	if(!file){std::cout<<"Error in BMP file initialization"<<std::endl; return 0;}
	if(fread(header, 1, 54, file)!=54){std::cout<<"Incorrect BMP format"<<std::endl; return 0;}

	dataPos=*(int*)&(header[0x0a]);
	imageSize=*(int*)&(header[0x22]);
	width=*(int*)&(header[0x12]);
	height=*(int*)&(header[0x16]);
	if(imageSize==0){imageSize=width*height*3;}
	if(dataPos==0){dataPos=54;}

	data=new unsigned char[imageSize];
	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}