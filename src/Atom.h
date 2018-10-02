#ifndef ATOM_H
#define ATOM_H


#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <utility>

#include <glm/gtx/polar_coordinates.hpp>
#include <glm/gtx/vector_angle.hpp>

#include "Drawable.h"

class Connection;

class Atom:public Drawable{
private:
	short anum, electrons, velectrons, os;
	std::string name, abb;
	std::vector<Connection*> c;
	glm::vec2 polarrot;
	static int newid;
	int id;
	//check level of innefficiency, change possibly required
public:
	bool repositioned;

	Atom();
	Atom(short an, short o);
	Atom(Atom *a);

	void printAtom();

	virtual void setPos(glm::vec3 pos);
	virtual void setRot(glm::vec2 rot);

	void addConnection(Connection *con);

	void recomputePosition();

	short getANum(){return anum;}
	std::string getName(){return name;}
	std::string getAbbrev(){return abb;}
	short getElectrons(){return electrons;}
	short getVE(){return velectrons;}
	short getOS(){return os;}
	std::vector<Connection*> getConnections(){return c;}
	int getID(){return id;}
	glm::vec3 getColor(){return color;}
	virtual glm::vec2 getRotation(){return polarrot;}
};

#endif