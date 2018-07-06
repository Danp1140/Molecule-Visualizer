#include "Drawable.h"
#include "Viewport.h"

Drawable::Drawable()
		:positionvar(glm::vec3(0,0,0)), rotationvar(glm::vec3(0,0,0)), scalevar(glm::vec3(1,1,1)), color(glm::vec3(0.95,0.95,0.95)){
	std::vector<glm::vec3> verttemp, normtemp;
	Viewport::loadOBJ("resources/models/test.obj", verttemp, normtemp);
	setVN(verttemp, normtemp);
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

//Drawable::Drawable(std::vector<glm::vec3> v, std::vector<glm::vec3> n, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl, glm::vec3 clr)
//		:verticies(v), normals(n), positionvar(pos), rotationvar(glm::quat(rot)), scalevar(scl), color(clr){
//	GLuint vb;
//	glGenBuffers(1, &vb);
//	vertexbuffer=vb;
//	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//	glBufferData(GL_ARRAY_BUFFER, verticies.size()*sizeof(glm::vec3), verticies.data(), GL_STATIC_DRAW);
//	GLuint nb;
//	glGenBuffers(1, &nb);
//	normalbuffer=nb;
//	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
//	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
//}

Drawable::Drawable(const char* modelfilepath)
		:positionvar(glm::vec3(0,0,0)), rotationvar(glm::vec3(0,0,0)), scalevar(glm::vec3(1,1,1)), color(glm::vec3(0.95,0.95,0.95)){
	std::vector<glm::vec3> verttemp, normtemp;
	Viewport::loadOBJ(modelfilepath, verttemp, normtemp);
	setVN(verttemp, normtemp);
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


void Drawable::draw(glm::mat4 viewmat, glm::mat4 projectmat, GLuint shader, glm::vec3 camPos){
	glUseProgram(shader);

	//glm::mat4 mvp=projectmat*viewmat*(glm::translate(positionvar)*glm::toMat4(rotationvar)*glm::scale(scalevar));
	glm::mat4 m=glm::translate(positionvar)*glm::toMat4(rotationvar)*glm::scale(scalevar);
	glm::mat4 vp=projectmat*viewmat;
	//glm::mat4 mvp=glm::perspective(glm::radians(45.0f), 1440.0f/900.0f, 100.0f, 0.1f)*glm::lookAt(glm::vec3(3,3,4), glm::vec3(0,0,0), glm::vec3(0,1,0))*(glm::translate(positionvar)*glm::toMat4(rotationvar)*glm::scale(scalevar));
	//std::cout<<"Scale x: "<<scalevar.x<<" Scale y: "<<scalevar.y<<" Scale z: "<<scalevar.z<<'\n';
	//std::cout<<"Rotation x: "<<glm::eulerAngles(rotationvar).x<<" Rotation y: "<<glm::eulerAngles(rotationvar).y<<" Rotation z: "<<glm::eulerAngles(rotationvar).z<<'\n';
//    std::cout<<"Position x: "<<positionvar.x<<" Position y: "<<positionvar.y<<" Position z: "<<positionvar.z<<'\n';

	GLuint mID=glGetUniformLocation(shader, "M");
	GLuint vpID=glGetUniformLocation(shader, "VP");
	glUniformMatrix4fv(mID, 1, GL_FALSE, &m[0][0]);
	glUniformMatrix4fv(vpID, 1, GL_FALSE, &vp[0][0]);
	//Sends for VertexShader.glsl and FragmentShader.glsl
	GLuint tintID=glGetUniformLocation(shader, "tint");
	GLuint viewPosID=glGetUniformLocation(shader, "viewPos");
	GLuint shininessID=glGetUniformLocation(shader, "shininess");
	glUniform3fv(tintID, 1, &color[0]);
	glUniform3fv(viewPosID, 1, &camPos[0]);
	glUniform1f(shininessID, 0.9f);
//	std::cout<<"Tint:   R: "<<color.r<<"   G: "<<color.g<<"   B: "<<color.b<<'\n';
//	std::cout<<"View Position:   X: "<<camPos.x<<"   Y: "<<camPos.y<<"   Z: "<<camPos.z<<'\n';


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

void Drawable::setPos(glm::vec3 pos){
	positionvar=pos;
}
void Drawable::setRot(glm::vec3 angles){
	rotationvar=glm::quat(angles);
}
void Drawable::setScl(glm::vec3 scl){
	scalevar=scl;
}
void Drawable::setVN(std::vector<glm::vec3> v, std::vector<glm::vec3> n){
	verticies=v;
	normals=n;
}
void Drawable::setClr(glm::vec3 clr){color=clr;}

Drawable::~Drawable(){
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &normalbuffer);
}
