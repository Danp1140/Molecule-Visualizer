#include "Atom.h"
#include "Connection.h"
#include "PeriodicTable.h"

Atom::Atom()
		: anum(0), name("unassigned"), abb("n/a"), electrons(0), velectrons(0), os(0), Drawable("resources/models/atom.obj"){
	std::vector<Connection*> c;
}
Atom::Atom(short an, std::string n, std::string a, short e, short ve, short o)
		: anum(an), name(n), abb(a), electrons(e), velectrons(ve), os(o), Drawable("resources/models/atom.obj"){
	std::vector<Connection*> c;
	if(anum==1){color=glm::vec3(1,1,1);}
	if(anum==6){color=glm::vec3(0.1,0.1,0.1);}
	if(anum==7){color=glm::vec3(0.1,0.1,0.9);}
	if(anum==8){color=glm::vec3(0.9,0.1,0.1);}
}
Atom::Atom(short an, short o)
		: anum(an), os(o), Drawable("resources/models/atom.obj"){
	PeriodicTable pt=PeriodicTable();
	name=pt.getAtom(an, o).getName();
	abb=pt.getAtom(an, o).getAbbrev();
	electrons=pt.getAtom(an, o).getElectrons();
	velectrons=pt.getAtom(an, o).getVE();
	std::vector<Connection*> c;
	if(anum==1){color=glm::vec3(1,1,1);}
	if(anum==6){color=glm::vec3(0.1,0.1,0.1);}
	if(anum==7){color=glm::vec3(0.1,0.1,0.9);}
	if(anum==8){color=glm::vec3(0.9,0.1,0.1);}
}

bool Atom::equals(Atom a){
	if(abb!=a.getAbbrev()){
		return false;
	}
	return true;
}

void Atom::printAtom(){
	if(os!=0){
		std::cout<<"\tAbbreviation: "<<abb<<"\n\tElectron Count: "<<electrons<<"\n\tValence Electron Count: "<<velectrons<<'\n';
	}
	else{
		std::cout<<anum<<"\nName: "<<name<<"\nAbbreviation: "<<abb<<"\nElectron Count: "<<electrons<<"\nValence Electron Count: "<<velectrons<<'\n';
	}
}

void Atom::addConnection(Connection *con){
	c.push_back(con);
}