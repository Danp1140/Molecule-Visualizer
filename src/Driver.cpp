#include "Molecule.h"
#include "GL/glew.h"
#define GLFW_INCLUDE_GL_3
#include "GLFW/glfw3.h"

int main()
{
	PeriodicTable pt=PeriodicTable();
	std::vector<Atom> a;
	std::vector<Connection> c;
	
	a.push_back(Atom(pt.getAtom(1,0)));
	a.push_back(Atom(pt.getAtom(1,0)));
	a.push_back(Atom(pt.getAtom(8,0)));

	c.push_back(Connection(1,&a.at(0),&a.at(2)));
	c.push_back(Connection(1,&a.at(1),&a.at(2)));

	Molecule m=Molecule(a,c);
	Molecule ms=Molecule(m.subMol(m.getAtom(1)));

	ms.printMolecule();

    GLFWwindow* window = glfwCreateWindow(640, 480, "My Title", NULL, NULL);

	return 0;
}