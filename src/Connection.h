class Atom;

class Connection{
private:
	short bonds;
	Atom *a1, *a2;
public:
	Connection();
	Connection(short b, Atom *atom1, Atom *atom2);

	short getBonds(){return bonds;}
	Atom* getAtom1(){return a1;}
	Atom* getAtom2(){return a2;}
	
	void printConnection();
};