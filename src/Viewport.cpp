#include "Viewport.h"

Viewport::Viewport(Camera c, GLFWwindow*w, int wdth, int hght, GLuint shaders)
		:camera(c), window(w), width(wdth), height(hght), programID(shaders){
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void Viewport::draw(){
	camera.updatePos();
	//std::cout<<"CamPosition x: "<<camera.getPosition().x<<" CamPosition y: "<<camera.getPosition().y<<" CamPosition z: "<<camera.getPosition().z<<'\n';
	//std::cout<<"CamFocus x: "<<camera.getFocus().x<<" CamFocus y: "<<camera.getFocus().y<<" CamFocus z: "<<camera.getFocus().z<<'\n';
	for(auto&object : objects){
		object->draw(camera.getView(), camera.getPerspective(), programID, camera.getPosition());
		//std::cout<<"Position x: "<<objects.at(x)->getPosition().x<<" Position y: "<<objects.at(x)->getPosition().y<<" Position z: "<<objects.at(x)->getPosition().z<<'\n';
	}
}

void Viewport::addDrawable(Drawable*object){
	objects.emplace_back(object);
}

//note: loadOBJ doesn't work with texture maps
bool Viewport::loadOBJ(const char*obj_filepath, std::vector<glm::vec3>&vertices, std::vector<glm::vec3>&normals){
	std::vector<unsigned int> vertIndicies, normIndicies;
	std::vector<glm::vec3> verttemps, normtemps;
	FILE*file=fopen(obj_filepath, "r");
	if(file==nullptr){
		std::cout<<"Loading OBJ Failure ("<<obj_filepath<<")\n";
		return false;
	}
	while(true){
		char lineheader[1024];//128?
		int res=fscanf(file, "%s", lineheader);
		if(res==EOF){break;}
		if(strcmp(lineheader, "v")==0){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			verttemps.push_back(vertex);
		}else if(strcmp(lineheader, "vn")==0){
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			normtemps.push_back(normal);
		}else if(strcmp(lineheader, "f")==0){
			std::string vert1, vert2, vert3;
			unsigned int vertidx[3], normidx[3];
			int matches=fscanf(file, "%d//%d %d//%d %d//%d", &vertidx[0], &normidx[0], &vertidx[1], &normidx[1],
			                   &vertidx[2], &normidx[2]);
			if(matches!=6){
				std::cout<<"OBJ Format Failure ("<<obj_filepath<<"), remember not to include UV maps)\n";
				return false;
			}
			vertIndicies.push_back(vertidx[0]);
			vertIndicies.push_back(vertidx[1]);
			vertIndicies.push_back(vertidx[2]);
			normIndicies.push_back(normidx[0]);
			normIndicies.push_back(normidx[1]);
			normIndicies.push_back(normidx[2]);
		}
	}
//	std::cout<<"Vertex Indicies: "<<vertIndicies.size()<<'\n';
	for(unsigned int x=0;x<vertIndicies.size();x++){
		vertices.push_back(verttemps[vertIndicies[x]-1]);
//		std::cout<<"Vertex "<<x<<": "<<verttemps[vertIndicies[x]-1].x<<", "<<verttemps[vertIndicies[x]-1].y<<", "<<verttemps[vertIndicies[x]-1].z<<"\n";
	}
//	std::cout<<"Normal Indicies: "<<normIndicies.size()<<'\n';
	for(unsigned int x=0;x<normIndicies.size();x++){
		normals.push_back(normtemps[normIndicies[x]-1]);
//		std::cout<<"Normal "<<x<<": "<<normtemps[normIndicies[x]-1].x<<", "<<normtemps[normIndicies[x]-1].y<<", "<<normtemps[normIndicies[x]-1].z<<"\n";
	}
	return true;
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