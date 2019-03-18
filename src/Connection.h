#ifndef CONNECTION_H_
#define CONNECTION_H_

#include "Drawable.h"

class Atom;

class Connection:public Drawable{
private:
	short bonds;
	Atom *a1, *a2;
public:
	Connection(short b, Atom *atom1, Atom *atom2);
	Connection(Connection *c);

	Atom* getNot(Atom* a);
	static bool numTest(Atom*one, Atom*two, int b);

	short getBonds(){return bonds;}
	Atom* getAtom1(){return a1;}
	Atom* getAtom2(){return a2;}
	
	void printConnection();
};

#endif