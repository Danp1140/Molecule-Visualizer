#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Drawable.h"
#include "Viewport.h"

class Atom;

class Connection:public Drawable{
private:
	short bonds;
	Atom *a1, *a2;
public:
	Connection();
	Connection(short b, Atom *atom1, Atom *atom2);
//	Connection(short b, Atom *atom1, Atom *atom2, glm::vec3 pos, glm::vec3 rot, glm::vec3 scl);

	short getBonds(){return bonds;}
	Atom* getAtom1(){return a1;}
	Atom* getAtom2(){return a2;}
	
	void printConnection();
};

#endif