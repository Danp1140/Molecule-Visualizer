#include "Molecule.h"

Molecule::Molecule(){
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
}
Molecule::Molecule(std::vector<Atom*> a, std::vector<Connection*> c)
		: atoms(std::move(a)), connections(std::move(c)){
	//need brackets???
}

void Molecule::addAtom(Atom* a){
//	a->setPos(glm::vec3(a->getID()*4-2, 0, 0));
	atoms.emplace_back(std::move(a));
//	std::vector<glm::vec3> vtemp, ntemp;
//	Drawable::loadOBJ("resources/models/atom.obj", vtemp, ntemp);
//	//temp fix for deleted buffers: regen buffers...find alternate permenant fix?
//	atoms.at(atoms.size()-1).setVN(vtemp, ntemp);
//	recomputePositions();
}
void Molecule::removeAtom(Atom *a){
	for(short x=0;x<atoms.size();x++){
		if(atoms.at(x)==a){
			atoms.erase(atoms.begin()-1+x);
		}
	}
}
void Molecule::addConnection(Connection* c){
	connections.emplace_back(std::move(c));
//	std::vector<glm::vec3> vtemp, ntemp;
//	if(connections.at(connections.size()-1).getBonds()==1){Drawable::loadOBJ("resources/models/singlebond.obj", vtemp, ntemp);}
//	else if(connections.at(connections.size()-1).getBonds()==2){Drawable::loadOBJ("resources/models/doublebond.obj", vtemp, ntemp);}
//	else{Drawable::loadOBJ("resources/models/triplebond.obj", vtemp, ntemp);}
//	connections.at(connections.size()-1).setVN(vtemp, ntemp);
//	recomputePositions();
}
void Molecule::removeConnection(Connection *c){
	for(short x=0;x<connections.size();x++){
		if(connections.at(x)==c){
			connections.erase(connections.begin()-1+x);
		}
	}
}

void Molecule::printMolecule(){
	std::cout<<"ATOMS:\n______________________________________________\n";
	for(auto& atom:atoms){
		atom->printAtom();
	}
	std::cout<<"CONNECTIONS:\n______________________________________________\n";
	for(auto& connection:connections){
		connection->printConnection();
	}
}

Molecule Molecule::subMol(Atom *a){
	//perhaps unneccesary?
	Molecule m;
	m.addAtom(new Atom(a));
	for(auto& x:a->getConnections()){
		m.addConnection(new Connection(x));
		m.addAtom(new Atom(x->getNot(a)));
	}
	return m;
}

void Molecule::recomputePositions(){
	Atom* start;
	for(int x=2;x<10;x++){
		for(auto& a:atoms){
			if(a->getConnections().size()<x){
				start=a;
				break;
			}
		}
		if(start->getName()!="unassigned"){break;}
	}
	std::cout<<"                 "<<start->getName()<<"                 \n";
	for(auto& root:atoms){
		int bonding=root->getConnections().size(), lonepairs=root->getVE();
		for(auto& c:root->getConnections()){
			lonepairs-=c->getBonds();
		}
		lonepairs/=2;
		std::cout<<root->getID()<<" ("<<root->getName()<<"):   Submolecule Bonding: "<<bonding<<"   Lone Pairs in Submolecule: "<<lonepairs<<'\n';
		//MAKE ATOM MOVE MOVE CONNECTIONS TO PROPER POSITION AS WELL
		//perhaps change order of how rotation and position are applied?
		if(bonding==2&&lonepairs==2){
			root->getConnections().at(0)->getNot(root)->setPos(root->getPosition()+glm::vec3(0, 0, 4));
			root->getConnections().at(1)->getNot(root)->setPos(root->getPosition()+glm::vec3(sin(52.225)*4, 0, cos(52.225)*4));
		}
		if(bonding==4&&lonepairs==0){
//			root->getConnections().at(0)->getNot(root)->setPos(root->getPosition()+glm::vec3(0, 4, 0));
//			root->getConnections().at(1)->getNot(root)->setPos(root->getPosition()+glm::vec3(sin(54.75)*4, -0.3328594706*4, (sin(30)*(sin(54.75)/sin(60)))*4));
////			std::cout<<sqrt(pow(cos(54.75), 2)-pow(sin(54.75)/sqrt(3.0), 2));
////			std::cout<<
//			root->getConnections().at(2)->getNot(root)->setPos(root->getPosition()+glm::vec3(sin(109.5)*4, /*gotta figure this one out*/0, cos(109.5)*4));
//			root->getConnections().at(3)->getNot(root)->setPos(root->getPosition()+glm::vec3(sin(164.25)*4, /*gotta figure this one out*/0, cos(164.25)*4));
//			root->getConnections().at(0)->getNot(root)->setPos(root->getPosition()+glm::vec3(2*(sqrt(6)/2), 0, -2/sqrt(2)*(sqrt(6)/2)));
//			root->getConnections().at(1)->getNot(root)->setPos(root->getPosition()+glm::vec3(-2*(sqrt(6)/2), 0, -2/sqrt(2)*(sqrt(6)/2)));
//			root->getConnections().at(2)->getNot(root)->setPos(root->getPosition()+glm::vec3(0, 2*(sqrt(6)/2), 2/sqrt(2)*(sqrt(6)/2)));
//			root->getConnections().at(3)->getNot(root)->setPos(root->getPosition()+glm::vec3(0, -2*(sqrt(6)/2), 2/sqrt(2)*(sqrt(6)/2)));
			root->getConnections().at(0)->getNot(root)->setPos(root->getPosition()+glm::vec3(4/sqrt(3), 4/sqrt(3), 4/sqrt(3)));
			root->getConnections().at(1)->getNot(root)->setPos(root->getPosition()+glm::vec3(-4/sqrt(3), 4/sqrt(3), -4/sqrt(3)));
			root->getConnections().at(2)->getNot(root)->setPos(root->getPosition()+glm::vec3(4/sqrt(3), -4/sqrt(3), -4/sqrt(3)));
			root->getConnections().at(3)->getNot(root)->setPos(root->getPosition()+glm::vec3(-4/sqrt(3), -4/sqrt(3), 4/sqrt(3)));
			if(root->getConnections().at(3)->getNot(root)->getID()==18){root->getConnections().at(3)->getNot(root)->setClr(glm::vec3(1, 0, 0.75));}
		}
	}
}

int Molecule::findLongestBranch(Atom* a, int length){
	int longest=0, temp=0, x=0;
	std::cout<<a->getName()<<" ("<<a->getConnections().size()<<") : \n";
	if(length>0){x=1;}
	for(auto& c:a->getConnections()){
		if(c->getAtom1()->getID()==a->getID()){
			if(c->getAtom2()->getConnections().size()>1+x){
				std::cout<<"Branch ";
				temp+=findLongestBranch(c->getAtom2(), length++)+1;
				std::cout<<"Cascading result: "<<temp<<'\n';
			}
			else{
				temp+=length+1;
				std::cout<<"EOB result: "<<temp<<'\n';
			}
		}
		else{
			if(c->getAtom1()->getConnections().size()>1+x){
				std::cout<<"Branch ";
				temp+=findLongestBranch(c->getAtom1(), length++)+1;
				std::cout<<"Cascading result: "<<temp<<'\n';
			}
			else{
				temp+=length+1;
				std::cout<<"EOB result: "<<temp<<'\n';
			}
		}
		if(temp>longest){
			longest=temp;
		}
		temp=0;
	}
	return longest;
}

Molecule::~Molecule(){
	for(auto& a:atoms){
		delete a;
	}
	for(auto& c:connections){
		delete c;
	}
}