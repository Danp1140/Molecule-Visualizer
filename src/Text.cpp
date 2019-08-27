//
// Created by Daniel Paavola on 2019-04-11.
//

#include "Text.h"

Text::Text():size(1), dispwidth(800), dispheight(600), position(glm::vec2(0, 0)), textColor(glm::vec4(1, 1, 1, 1)){
	FT_Library library=FT_Library();
	FT_New_Face(library, "resources/fonts/arial.ttf", 0, &face);
	FT_Set_Char_Size(face, size*64*0.6, size*64, 800, 600);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

Text::Text(std::string m, int s, const char*fontfilepath, FT_Library library, int dw, int dh, glm::vec2 pos): size(s),
		dispwidth(dw), dispheight(dh), position(pos), textColor(glm::vec4(1, 1, 1, 1)){
	for(char c:m){message.push_back(c);}
	FT_New_Face(library, fontfilepath, 0, &face);
	FT_Set_Char_Size(face, size*64*0.6, size*64, dw, dh);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void Text::draw(GLuint shader){
	int linepos=0, maxlinepos=0;
	float rowpos=0;
	for(int x=0;x<message.size();x++){
		if(message[x]=='\n'){
			rowpos+=face->glyph->metrics.height/64+5;
			if(linepos>maxlinepos){maxlinepos=linepos;}
			linepos=0;
			continue;
		}


		FT_UInt glyph_index=FT_Get_Char_Index(face, message[x]);
		FT_Load_Glyph(face, glyph_index, FT_LOAD_RENDER);
		FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		std::vector<glm::vec2> vertices, uvs;

		FT_Glyph_Metrics m=face->glyph->metrics;

		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64+m.width/64, m.horiBearingY/64));
		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64, m.horiBearingY/64));
		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64, m.horiBearingY/64-m.height/64));

		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64, m.horiBearingY/64-m.height/64));
		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64+m.width/64, m.horiBearingY/64-m.height/64));
		vertices.push_back(position+glm::vec2(linepos, -rowpos)+glm::vec2(m.horiBearingX/64+m.width/64, m.horiBearingY/64));

		uvs.push_back(glm::vec2(1, 0));
		uvs.push_back(glm::vec2(0, 0));
		uvs.push_back(glm::vec2(0, 1));

		uvs.push_back(glm::vec2(0, 1));
		uvs.push_back(glm::vec2(1, 1));
		uvs.push_back(glm::vec2(1, 0));


		linepos+=m.horiAdvance/64;

//		std::cout<<"Width: "<<face->glyph->metrics.width/64<<"     Height: "<<face->glyph->metrics.height/64<<std::endl;
//		std::cout<<"Bearing X: "<<face->glyph->metrics.horiBearingX/64<<"     Bearing Y: "<<face->glyph->metrics.horiBearingY/64<<std::endl;
//		std::cout<<"Advance: "<<m.horiAdvance/64<<std::endl;


		glUseProgram(shader);

		GLint widthID=glGetUniformLocation(shader, "width");
		GLint heightID=glGetUniformLocation(shader, "height");
		GLint inColorID=glGetUniformLocation(shader, "inColor");
		GLint typeID=glGetUniformLocation(shader, "type");
		glUniform1i(widthID, dispwidth);
		glUniform1i(heightID, dispheight);
		glUniform4fv(inColorID, 1, &textColor[0]);
		glUniform1i(typeID, 2);


		GLuint textureID;
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		GLuint vertexbuffer, uvbuffer;
		glGenBuffers(1, &vertexbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec2), &vertices[0], GL_STATIC_DRAW);
		glGenBuffers(1, &uvbuffer);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

		glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertices.size()));

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteBuffers(1, &uvbuffer);
		glDeleteTextures(1, &textureID);
	}


}

void Text::setMessage(std::string m){
	std::vector<char> temp;
	for(char c:message){temp.push_back(c);}
	message=temp;
}