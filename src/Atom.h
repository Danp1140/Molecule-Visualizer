#ifndef ATOM_H
#define ATOM_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

#include "Drawable.h"

class Connection;

class Atom:public Drawable{
private:
	short anum, electrons, velectrons, os;
	std::string name, abb;
	std::vector<Connection*> c;
	static int newid;
	int id;
public:

	Atom();
	Atom(short an, short o);
	Atom(Atom *a);

	void printAtom();

	virtual void setPos(glm::vec3 pos);

	void addConnection(Connection *con);

	short getANum(){return anum;}
	std::string getName(){return name;}
	std::string getAbbrev(){return abb;}
	short getElectrons(){return electrons;}
	short getVE(){return velectrons;}
	short getOS(){return os;}
	std::vector<Connection*> getConnections(){return c;}
	int getID(){return id;}
};

#endif