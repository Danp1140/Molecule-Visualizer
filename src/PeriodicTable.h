#ifndef PERIODICTABLE_H_
#define PERIODICTABLE_H_

#include "Atom.h"

class PeriodicTable{
private:
	Atom elements[4][3];
public:
	PeriodicTable();


	Atom getAtom(short anum, short os);
	//Atom getAtom(std::string n);

	void printTable();

};

#endif