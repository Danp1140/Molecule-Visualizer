#include "Connection.h"
#include "Atom.h"

Connection::Connection(){
	bonds=0;
	Atom temp1=Atom();
	Atom temp2=Atom();
	a1=&temp1;
	a2=&temp2;
}
Connection::Connection(short b, Atom *atom1, Atom *atom2){
	bonds=b;
	a1=atom1;
	a2=atom2;
	short n=a1->getVE(), m=a2->getVE();
	for(int x=0;x<a1->getConnections().size();x++){
		n-=a1->getConnections().at(x)->getBonds();
	}
	for(int y=0;y<a2->getConnections().size();y++){
		m-=a2->getConnections().at(y)->getBonds();
	}
	if(b<1||b>3||b>n||b>m){
		std::cout<<"Too many or too little bonds: "<<b<<'\n';
		bonds=0;
	}
	atom1->addConnection(this);
	atom2->addConnection(this);
}

void Connection::printConnection(){
	if(bonds==1){std::cout<<a1->getAbbrev()<<" - "<<a2->getAbbrev()<<'\n';}
	else if(bonds==2){std::cout<<a1->getAbbrev()<<" = "<<a2->getAbbrev()<<'\n';}
	else if(bonds==3){std::cout<<a1->getAbbrev()<<" ≡ "<<a2->getAbbrev()<<'\n';}
	else{std::cout<<a1->getAbbrev()<<"   "<<a2->getAbbrev()<<'\n';}
}