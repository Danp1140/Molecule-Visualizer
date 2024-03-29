#include "Drawable.h"
#include <utility>

Drawable::Drawable()
		:positionvar(glm::vec3(0,0,0)), rotationvar(glm::vec3(0,0,0)), scalevar(glm::vec3(1,1,1)), color(glm::vec3(0.95,0.95,0.95)){
	std::vector<glm::vec3> verttemp, normtemp;
	loadOBJ("../resources/models/test.obj", verttemp, normtemp);
	setVN(verttemp, normtemp);
}

Drawable::Drawable(const std::vector<glm::vec3>&verts, const std::vector<glm::vec3>&norms)
		:positionvar(glm::vec3(0,0,0)), rotationvar(glm::vec3(0,0,0)), scalevar(glm::vec3(1,1,1)), color(glm::vec3(0.95,0.95,0.95)){
	setVN(verts, norms);
}


void Drawable::draw(glm::mat4 viewmat, glm::mat4 projectmat, GLuint shader, glm::vec3 camPos){
	glUseProgram(shader);

	glm::mat4 m=glm::translate(positionvar)*glm::toMat4(rotationvar)*glm::scale(scalevar);
	glm::mat4 vp=projectmat*viewmat;

	GLint mID=glGetUniformLocation(shader, "M");
	GLint vpID=glGetUniformLocation(shader, "VP");
	glUniformMatrix4fv(mID, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(vpID, 1, GL_FALSE, &vp[0][0]);
	GLint tintID=glGetUniformLocation(shader, "tint");
	GLint viewPosID=glGetUniformLocation(shader, "viewPos");
	GLint shininessID=glGetUniformLocation(shader, "shininess");
	glUniform3fv(tintID, 1, &color[0]);
	glUniform3fv(viewPosID, 1, &camPos[0]);
	glUniform1f(shininessID, 0.9f);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(verticies.size()));

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

bool Drawable::loadOBJ(const char*obj_filepath, std::vector<glm::vec3>&vertices, std::vector<glm::vec3>&normals){
	std::vector<unsigned int> vertIndicies, normIndicies;
	std::vector<glm::vec3> verttemps, normtemps;
	FILE*file=fopen(obj_filepath, "r");
	if(file==nullptr){
		std::cout<<"Loading OBJ Failure ("<<obj_filepath<<")\n";
		return false;
	}
	while(true){
		char lineheader[1024];
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
	for(unsigned int x=0;x<vertIndicies.size();x++){
		vertices.push_back(verttemps[vertIndicies[x]-1]);
	}
	for(unsigned int x=0;x<normIndicies.size();x++){
		normals.push_back(normtemps[normIndicies[x]-1]);
	}
	fclose(file);
	return true;
}

void Drawable::setPos(glm::vec3 pos){
	positionvar=pos;
}

void Drawable::setRot(glm::quat angles){
	rotationvar=angles;
}

void Drawable::setScl(glm::vec3 scl){
	scalevar=scl;
}

void Drawable::setVN(const std::vector<glm::vec3>&v, const std::vector<glm::vec3>&n){
	verticies=std::vector<glm::vec3>(v);
	normals=std::vector<glm::vec3>(v);
	GLuint vb;
	glGenBuffers(1, &vb);
	vertexbuffer=vb;
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, verticies.size()*sizeof(glm::vec3), &verticies[0], GL_STATIC_DRAW);
	GLuint nb;
	glGenBuffers(1, &nb);
	normalbuffer=nb;
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}

void Drawable::setClr(glm::vec3 clr){color=clr;}

Drawable::~Drawable(){
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
}
