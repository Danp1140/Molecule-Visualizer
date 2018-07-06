#include "Connection.h"
#include "Atom.h"

Connection::Connection()
		: bonds(1),
		  Drawable("resources/models/singlebond.obj"){
	Atom temp1=Atom();
	Atom temp2=Atom();
	a1=&temp1;
	a2=&temp2;
}
Connection::Connection(short b, Atom *atom1, Atom *atom2)
		: bonds(b), a1(atom1), a2(atom2),
		  Drawable(){
	short n=a1->getVE(), m=a2->getVE();
	for(int x=0;x<a1->getConnections().size();x++){
		n-=a1->getConnections().at(x)->getBonds();
	}
	for(int y=0;y<a2->getConnections().size();y++){
		m-=a2->getConnections().at(y)->getBonds();
	}
	if(b<1||b>3||b>n||b>m){
		std::cout<<"Too many or too little bonds: "<<b<<'\n';
		bonds=1;
	}
	atom1->addConnection(this);
	atom2->addConnection(this);
	std::vector<glm::vec3> verttemp, normtemp;
	if(b==1){Viewport::loadOBJ("resources/models/singlebond.obj", verttemp, normtemp);}
	else if(b==2){Viewport::loadOBJ("resources/models/doublebond.obj", verttemp, normtemp);}
	else{Viewport::loadOBJ("resources/models/triplebond.obj", verttemp, normtemp);}
	setVN(verttemp, normtemp);
	setClr(glm::vec3(0.5, 0.5, 0.5));
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
//Connection::Connection(short b, Atom *atom1, Atom *atom2, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl)
//		:Drawable(){
//	bonds=b;
//	a1=atom1;
//	a2=atom2;
//	short n=a1->getVE(), m=a2->getVE();
//	for(int x=0;x<a1->getConnections().size();x++){
//		n-=a1->getConnections().at(x)->getBonds();
//	}
//	for(int y=0;y<a2->getConnections().size();y++) {
//		m -= a2->getConnections().at(y)->getBonds();
//	}
//	if(b<1||b>3||b>n||b>m) {
//		std::cout<<"Too many or too little bonds: "<<b<<'\n';
//		bonds=1;
//	}
//	atom1->addConnection(this);
//	atom2->addConnection(this);
//	std::vector<glm::vec3> vert, norm;
//	if(b==1){Viewport::loadOBJ("resources/models/singlebond.obj", vert, norm);}
//	else if(b==2){Viewport::loadOBJ("resources/models/doublebond.obj", vert, norm);}
//	else{Viewport::loadOBJ("resources/models/triplebond.obj", vert, norm);}
//	setVN(vert, norm);
//	setPos(pos);
//	setRot(rot);
//	setScl(scl);
//}

void Connection::printConnection(){
	if(bonds==1){std::cout<<a1->getAbbrev()<<" - "<<a2->getAbbrev()<<'\n';}
	else if(bonds==2){std::cout<<a1->getAbbrev()<<" = "<<a2->getAbbrev()<<'\n';}
	else if(bonds==3){std::cout<<a1->getAbbrev()<<" ≡ "<<a2->getAbbrev()<<'\n';}
	else{std::cout<<a1->getAbbrev()<<"   "<<a2->getAbbrev()<<'\n';}
}