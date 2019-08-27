#ifndef MOLECULE_H_
#define MOLECULE_H_

#include <vector>
#include <utility>

#include "Connection.h"
#include "Atom.h"

class Molecule{
private:
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
public:
	Molecule();
	Molecule(std::vector<Atom*> a, std::vector<Connection*> c);
	Molecule(const char* pdbfilepath);

	void addAtom(Atom *a);
	void removeAtom(Atom *a);
	void addConnection(Connection *c);
	void removeConnection(Connection *c);

	void setPos(glm::vec3 p);

	void printMolecule();

	Molecule subMol(Atom *a);

	bool branch(Atom*s);
	bool torsionals(Atom*a1, Atom*a2);
	std::vector<Atom*> torsionalBranching(Atom*a1, Atom*a2);
	void recursiveTorsionals(Atom*s, bool starting);

	Atom* getAtom(short index){return atoms.at(index);}
	std::vector<Atom*>& getAtoms(){return atoms;}
	Connection* getConnection(short index){return connections.at(index);}
	std::vector<Connection*>& getConnections(){return connections;}

	virtual ~Molecule();
};

#endif