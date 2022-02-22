#include "Connection.h"
#include "Atom.h"

Connection::Connection(short b, Atom *atom1, Atom *atom2)
		: bonds(b), a1(atom1), a2(atom2),
		  Drawable(){
	//rid procedures for increased efficiency
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
	if(b==1) loadOBJ("../resources/models/singlebond.obj", verttemp, normtemp);
	else if(b==2) loadOBJ("../resources/models/doublebond.obj", verttemp, normtemp);
	else loadOBJ("../resources/models/triplebond.obj", verttemp, normtemp);
	setVN(verttemp, normtemp);
	setClr(glm::vec3(0.5, 0.5, 0.5));
}

Connection::Connection(Connection *c)
		: bonds(c->getBonds()), a1(c->getAtom1()), a2(c->getAtom2()), Drawable(){}

Atom* Connection::getNot(Atom *a){
	if(a->getID()==a1->getID()){
		return a2;
	}
	return a1;
}

bool Connection::numTest(Atom*one, Atom*two, int b){
	short n=one->getVE(), m=two->getVE();
	for(int x=0;x<one->getConnections().size();x++){
		n-=one->getConnections().at(x)->getBonds();
	}
	for(int y=0;y<two->getConnections().size();y++){
		m-=two->getConnections().at(y)->getBonds();
	}
	if(b<1||b>3||b>n||b>m){
		std::cout<<n<<" "<<m<<std::endl;
		std::cout<<"Too many or too little bonds: "<<b<<'\n';
		return false;
	}
	return true;
}

void Connection::printConnection(){
	if(bonds==1){std::cout<<a1->getAbbrev()<<" - "<<a2->getAbbrev()<<'\n';}
	else if(bonds==2){std::cout<<a1->getAbbrev()<<" = "<<a2->getAbbrev()<<'\n';}
	else if(bonds==3){std::cout<<a1->getAbbrev()<<" ≡ "<<a2->getAbbrev()<<'\n';}
	else{std::cout<<a1->getAbbrev()<<"   "<<a2->getAbbrev()<<'\n';}
}