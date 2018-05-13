#include "PeriodicTable.h"
#include "Connection.h"


class Molecule{
private:
	int freeelectrons;
	std::vector<Atom> atoms;
	std::vector<Connection> connections;
public:
	Molecule();
	Molecule(std::vector<Atom> a, std::vector<Connection> c);

	void addAtom(Atom a);
	void removeAtom(Atom *a);
	void addConnection(Connection c);
	void removeConnection(Connection *c);

	void updateFE();

	void printMolecule();

	Molecule subMol(Atom a);

	int getFE(){return freeelectrons;}
	Atom getAtom(short index){return atoms.at(index);}
	Connection getConnection(short index){return connections.at(index);}
};