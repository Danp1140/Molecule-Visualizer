#ifndef ATOM_H
#define ATOM_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "Drawable.h"

class Connection;

class Atom:public Drawable{
private:
	short anum, electrons, velectrons, os;
	std::string name, abb;
	std::vector<Connection*> c;
public:

	/*constructs default element (not a real element)*/
	Atom();
	/*constructs element with given atomic number, name, and electron configuration*/
	Atom(short an, std::string n, std::string a, short e, short ve, short o);

	Atom(short an, short o);

	bool equals(Atom a);

	/*prints information of atom*/
	void printAtom();

	void addConnection(Connection *con);

	/*getters*/
	short getANum(){return anum;}
	std::string getName(){return name;}
	std::string getAbbrev(){return abb;}
	short getElectrons(){return electrons;}
	short getVE(){return velectrons;}
	short getOS(){return os;}
	std::vector<Connection*> getConnections(){return c;}
};

#endif