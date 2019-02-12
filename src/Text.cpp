#include "Text.h"

Text::Text(){
	message="Unassigned";
	texture="resources/testtext.png";
	x=0; y=0; size=50;
	this->init();
}

Text::Text(std::string m, std::string tex, int xpos, int ypos, int s)
	: message(m), texture(tex), x(xpos), y(ypos), size(s){
	this->init();
}

GLuint Text::loadBMP(const char*imagepath){
	unsigned char header[54];
	unsigned int dataPos, width, height, imageSize;
	unsigned char*data;
	FILE * file = fopen(imagepath,"rb");
	if(!file){printf("Image opening failure\n"); return 0;}
	if(fread(header, 1, 54, file)!=54){printf("Image formatting not standard BMP\n"); return 0;}
	if(header[0]!='B'||header[1]!='M'){printf("Image formatting not standard BMP\n"); return 0;}
	dataPos=*(int*)&(header[0x0A]);
	imageSize=*(int*)&(header[0x22]);
	width=*(int*)&(header[0x12]);
	height=*(int*)&(header[0x16]);
	if(imageSize==0)imageSize=width*height*3;
	if(dataPos==0)dataPos=54;
	data = new unsigned char [imageSize];
	fread(data,1,imageSize,file);
	fclose(file);

	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	delete[] data;

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	return textureID;

}

void Text::init(){
//	GLuint VertexArrayID;
//	glGenVertexArrays(1, &VertexArrayID);
//	glBindVertexArray(VertexArrayID);

//	vertices.push_back(glm::vec3(1, 0, 0));
//	vertices.push_back(glm::vec3(-1, 0, 0));
//	vertices.push_back(glm::vec3(0, 1, 0));
//	vertices.push_back(glm::vec3(0, 1, 0));
//	vertices.push_back(glm::vec3(0, -1, 0));
//	vertices.push_back(glm::vec3(1, 0, 0));

//	std::cout<<vertices.at(0).x<<", "<<vertices.at(0).y<<'\n';
//	std::cout<<vertices.at(1).x<<", "<<vertices.at(1).y<<'\n';
//	std::cout<<vertices.at(2).x<<", "<<vertices.at(2).y<<'\n';
//	for(int i=0;i<message.size();i++){
//		glm::vec3 vul=glm::vec3(x+i*size, y+size, 0);
//		glm::vec3 vur=glm::vec3(x+i*size+size, y+size, 0);
//		glm::vec3 vdr=glm::vec3(x+i*size+size, y, 0);
//		glm::vec3 vdl=glm::vec3(x+i*size, y, 0);
//
////		glm::vec2 vul=glm::vec2(x+i*size, y+size);
////		glm::vec2 vur=glm::vec2(x+i*size+size, y+size);
////		glm::vec2 vdr=glm::vec2(x+i*size+size, y);
////		glm::vec2 vdl=glm::vec2(x+i*size, y);
//
//		vertices.push_back(vul);
//		vertices.push_back(vdl);
//		vertices.push_back(vur);
//		vertices.push_back(vdr);
//		vertices.push_back(vur);
//		vertices.push_back(vdl);
//
//		char character=message[i];
//		float uvx=(character%16)/16.0;
//		float uvy=(character/16)/16.0;
//
//		glm::vec2 uul=glm::vec2(uvx, 1.0f-uvy);
//		glm::vec2 uur=glm::vec2(uvx+1.0/16.0, 1.0-uvy);
//		glm::vec2 udr=glm::vec2(uvx+1.0/16.0, 1.0-(uvy+1.0/16.0));
//		glm::vec2 udl=glm::vec2(uvx, 1.0-(uvy+1.0/16.0));
//
//		UVs.push_back(uul);
//		UVs.push_back(udl);
//		UVs.push_back(uur);
//		UVs.push_back(udr);
//		UVs.push_back(uur);
//		UVs.push_back(udl);
//	}

	GLuint vb;
	glGenBuffers(1, &vb);
	vertexbuffer=vb;
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	GLuint uvb;
	glGenBuffers(1, &uvb);
	uvbuffer=vb;
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size()*sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);
}
void Text::draw(GLuint shader){
	glUseProgram(shader);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

//	std::cout<<vertices.at(0).x<<", "<<vertices.at(0).y<<'\n';
//	std::cout<<vertices.at(1).x<<", "<<vertices.at(1).y<<'\n';
//	std::cout<<vertices.at(2).x<<", "<<vertices.at(2).y<<'\n';
}