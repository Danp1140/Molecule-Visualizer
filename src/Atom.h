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
#include <glm/gtx/perpendicular.hpp>

#include "Drawable.h"

class Connection;

class Atom:public Drawable{
private:
	short anum, electrons, velectrons, os;
	std::string name, abb, pdbname, residue;
	std::vector<Connection*> c;
	glm::vec2 polarrot;
	static int newid;
	int id;

	void loadData();
public:
	bool repositioned;

	Atom();
	Atom(short an, short o, std::vector<glm::vec3>&v, std::vector<glm::vec3>&norm);
	Atom(std::string sym, glm::vec3 pos, const std::vector<glm::vec3>&v, const std::vector<glm::vec3>&norm);
	Atom(std::string sym, glm::vec3 pos, std::string n, std::string res, const std::vector<glm::vec3>&v, const std::vector<glm::vec3>&norm);
	Atom(Atom *a);

	void printAtom();

	virtual void setPos(glm::vec3 pos);
	virtual void setRot(glm::vec2 rot);

	void addConnection(Connection *con);

	void recomputePosition();

	void refreshPosition();

	short getANum(){return anum;}
	std::string getName(){return name;}
	std::string getAbbrev(){return abb;}
	std::string getPDBName(){return pdbname;}
	std::string getResidue(){return residue;}
	short getElectrons(){return electrons;}
	short getVE(){return velectrons;}
	short getOS(){return os;}
	std::vector<Connection*> getConnections(){return c;}
	int getID(){return id;}
	glm::vec3 getColor(){return color;}
	virtual glm::vec2 getRotation(){return polarrot;}
};

#endif