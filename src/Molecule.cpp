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

void Molecule::setPos(glm::vec3 p){
	glm::vec3 p0=glm::vec3(0,0,0);
	for(auto&a:atoms){
		p0+=a->getPosition();
	}
	p0/=atoms.size();
	for(auto&a:atoms){
		a->setPos(a->getPosition()-p0+p);
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

bool Molecule::branch(Atom*s){
	//below if statement possibly more streamlineable?
//	std::cout<<"branch call from "<<s->getID()<<"\n";
	if(s->getName()=="unassigned"){
		for(auto&x:atoms){
			x->repositioned=false;
		}
		Atom*start=s;
		for(int x=2;x<10;x++){
			for(auto&a:atoms){
				if(a->getName()!="unassigned"&&a->getConnections().size()<x){
					start=a;
//					std::cout<<"Branch start identified: "<<start->getID()<<'\n';
					start->recomputePosition();
					start->repositioned=true;
//					start->setClr(glm::vec3(0.9, 0.1, 0.9));
//					std::cout<<"Operation executed on atom "<<start->getID()<<'\n';
					break;
				}
			}
			if(start->getName()!="unassigned"){break;}
		}
		for(auto&x:atoms){
//		std::cout<<x->getPosition().x<<" "<<x->getPosition().y<<" "<<x->getPosition().z<<'\n';
//			std::cout<<x->repositioned<<" ";
		}
		branch(start->getConnections().at(0)->getNot(start));
	}
	else{
		if(s->repositioned==false){
			s->recomputePosition();
//			std::cout<<"Operation executed on atom "<<s->getID()<<'\n';
			s->repositioned=true;
		}

		if(s->getConnections().size()==1){
			if(s->getConnections().at(0)->getNot(s)->repositioned==false){
				s->getConnections().at(0)->getNot(s)->recomputePosition();
				s->getConnections().at(0)->getNot(s)->repositioned=true;
//				std::cout<<"Operation executed on atom "<<s->getConnections().at(0)->getNot(s)->getID()<<'\n';
			}
		}
		else{
			for(auto&c:s->getConnections()){
				if(c->getNot(s)->repositioned==false){
					branch(c->getNot(s));
				}
			}
		}
		for(auto&x:atoms){
//		std::cout<<x->getPosition().x<<" "<<x->getPosition().y<<" "<<x->getPosition().z<<'\n';
//			std::cout<<x->repositioned<<" ";
		}
	}
//	delete s;
}

Molecule::~Molecule(){
	for(auto& a:atoms){
		delete a;
	}
	for(auto& c:connections){
		delete c;
	}
}