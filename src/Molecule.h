#ifndef MOLECULE_H_
#define MOLECULE_H_

#include "Connection.h"
#include "Atom.h"

class Molecule:public Drawable{
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

	virtual void draw(glm::mat4 viewmat, glm::mat4 projectmat, GLuint shader, glm::vec3 camPos) override;

	Molecule subMol(Atom a);

	int getFE(){return freeelectrons;}
	Atom getAtom(short index){return atoms.at(index);}
	Connection getConnection(short index){return connections.at(index);}
};

#endif