#include "Atom.h"
#include "Connection.h"

Atom::Atom(){
	anum=0;
	name="unassigned";
	abb="n/a";
	electrons=0;
	velectrons=0;
	os=0;
	std::vector<Connection*> c;
}
Atom::Atom(short an, std::string n, std::string a, short e, short ve, short o){
	anum=an;
	name=n;
	abb=a;
	electrons=e;
	velectrons=ve;
	os=o;
	std::vector<Connection*> c;
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