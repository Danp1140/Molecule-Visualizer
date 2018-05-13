#include "Molecule.h"

Molecule::Molecule(){
	std::vector<Atom> atoms;
	std::vector<Connection> connections;
	updateFE();
}
Molecule::Molecule(std::vector<Atom> a, std::vector<Connection> c){
	atoms=a;
	connections=c;
	updateFE();
}

void Molecule::addAtom(Atom a){
	atoms.push_back(a);
}
void Molecule::removeAtom(Atom *a){
	for(short x=0;x<atoms.size();x++){
		if(&atoms.at(x)==a){
			atoms.erase(atoms.begin()-1+x);
		}
	}
}
void Molecule::addConnection(Connection c){
	connections.push_back(c);
}
void Molecule::removeConnection(Connection *c){
	for(short x=0;x<connections.size();x++){
		if(&connections.at(x)==c){
			connections.erase(connections.begin()-1+x);
		}
	}
}

void Molecule::updateFE(){
	freeelectrons=0;
	for(short x=0;x<atoms.size();x++){
		freeelectrons+=atoms.at(x).getVE();
	}
	for(short y=0;y<connections.size();y++){
		freeelectrons-=connections.at(y).getBonds()*2;
	}
}


void Molecule::printMolecule(){
	std::cout<<"ATOMS:\n______________________________________________\n";
	for(short x=0;x<atoms.size();x++){
		atoms.at(x).printAtom();
	}
	std::cout<<"CONNECTIONS:\n______________________________________________\n";
	for(short y=0;y<connections.size();y++){
		connections.at(y).printConnection();
	}
}

Molecule Molecule::subMol(Atom a){
	std::vector<Atom> atomvect;
	std::vector<Connection> connvect;
	atomvect.push_back(a);
	for(int x=0;x<a.getConnections().size();x++){
		if(a.getConnections().at(x)->getAtom1()->equals(a)){
			atomvect.push_back(*(a.getConnections().at(x)->getAtom2()));
		}
		else{
			atomvect.push_back(*(a.getConnections().at(x)->getAtom1()));
		}
		connvect.push_back(*(a.getConnections().at(x)));
	}
	return Molecule(atomvect,connvect);
}