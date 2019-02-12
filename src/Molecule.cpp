#include "Molecule.h"

Molecule::Molecule(){
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
}
Molecule::Molecule(std::vector<Atom*> a, std::vector<Connection*> c)
		: atoms(std::move(a)), connections(std::move(c)){
	//need brackets???
}
Molecule::Molecule(const char* pdbfilepath){
	std::cout<<"Loading PDB"<<std::endl;
	float percent=0.0;
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
	std::vector<glm::vec3> verts, norms;
	Drawable::loadOBJ("resources/models/atomsmooth.obj", verts, norms);
	char temp[128];
	FILE*file=fopen(pdbfilepath, "r");
	while(true){
		if(fgets(temp, sizeof(temp), file)==NULL){break;}
		std::string str=(temp);
		std::string rectype=str.substr(0, 6);
		std::string sernum=str.substr(6, 5);
		std::string name=str.substr(13, 4);
		std::string altlocind=str.substr(16, 1);
		std::string resname=str.substr(17, 3);
		std::string chainid=str.substr(21, 1);
		std::string resseqnum=str.substr(22, 4);
		std::string cfior=str.substr(26, 1);
		std::string xcoord=str.substr(30, 8);
		std::string ycoord=str.substr(38, 8);
		std::string zcoord=str.substr(46, 8);
		std::string occupancy=str.substr(54, 6);
		std::string tempfac=str.substr(60, 6);
		std::string segid=str.substr(72, 4);
		std::string esym=str.substr(76, 2);
		if(rectype=="ATOM  "){
			if(name[3]=='A'){name[3]=' ';}
			if(name[3]!='A'&&name[3]!=' '){continue;}
			float x=std::stof(xcoord), y=std::stof(ycoord), z=std::stof(zcoord);
			for(int x=0;x<esym.length();x++){
				if(esym.at(x)==' '){esym.erase(x, 1);}
			}
			this->addAtom(new Atom(esym, glm::vec3(x*2.76, y*2.76, z*2.76), name, resname, verts, norms));
		}

	}
	for(int x=0;x<this->getAtoms().size();x++){
		for(int y=0;y<this->getAtoms().size();y++){
			if(x!=y){
				bool dupe=false;
				for(auto&c:this->getAtom(x)->getConnections()){
					if(c->getNot(this->getAtom(x))==this->getAtom(y)){dupe=true;}
				}
				if(!dupe){
					Atom*a1=this->getAtom(x), *a2=this->getAtom(y);
					float z=abs(sqrt(pow(a2->getPosition().x-a1->getPosition().x, 2)+
					                 pow(a2->getPosition().y-a1->getPosition().y, 2)+
					                 pow(a2->getPosition().z-a1->getPosition().z, 2)));
					if(a1->getResidue()=="GLY"&&a2->getResidue()=="GLY"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="LYS"&&a2->getResidue()=="LYS"&&z<6.0){
						if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")||(a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="CE  ")||(a1->getPDBName()=="CE  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="NZ  "&&a2->getPDBName()=="CE  ")||(a1->getPDBName()=="CE  "&&a2->getPDBName()=="NZ  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="CYS"&&a2->getResidue()=="CYS"&&z<6.0){
						if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")||(a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="SG  ")||(a1->getPDBName()=="SG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")||(a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if(a1->getPDBName()=="SG  "&&a2->getPDBName()=="SG  "){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="GLU"&&a2->getResidue()=="GLU"&&z<6.0){
						if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")||(a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD  ")||(a1->getPDBName()=="CD  "&&a2->getPDBName()=="CG  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")||(a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="OE1 ")||(a1->getPDBName()=="OE1 "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="OE2 ")||(a1->getPDBName()=="OE2 "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="TYR"&&a2->getResidue()=="TYR"&&z<6.0){
						if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")||(a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CE1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="CE1 "&&a2->getPDBName()=="CZ  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CZ  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="OH  ")||(a1->getPDBName()=="OH  "&&a2->getPDBName()=="CZ  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="ARG"&&a2->getResidue()=="ARG"&&z<6.0){
						if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")||(a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")||(a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="NE  ")||(a1->getPDBName()=="NE  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="NE  ")||(a1->getPDBName()=="CZ  "&&a2->getPDBName()=="NE  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="NH1 ")||(a1->getPDBName()=="CH1 "&&a2->getPDBName()=="NE  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="NH2 ")||(a1->getPDBName()=="CH2 "&&a2->getPDBName()=="NE  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="VAL"&&a2->getResidue()=="VAL"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG1 ")||(a1->getPDBName()=="CG1 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG2 ")||(a1->getPDBName()=="CG2 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="LEU"&&a2->getResidue()=="LEU"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}

					else if(a1->getResidue()=="ALA"&&a2->getResidue()=="ALA"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(
									glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(
									glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(
									glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(
									glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="PHE"&&a2->getResidue()=="PHE"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="CE1 "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="CE1 "&&a2->getPDBName()=="CZ  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ  "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CZ  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="ASP"&&a2->getResidue()=="ASP"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="OD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="OD1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="OD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="OD2 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="PRO"&&a2->getResidue()=="PRO"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="N   ")||(a1->getPDBName()=="N   "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="SER"&&a2->getResidue()=="SER"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="OG  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="OG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="HIS"&&a2->getResidue()=="HIS"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="ND1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="ND1 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="NE2 ")||(a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CE2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="ND1 "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="ND1 "&&a2->getPDBName()=="CE1 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="NE2 "&&a2->getPDBName()=="CE1 ")||(a1->getPDBName()=="NE2 "&&a2->getPDBName()=="CE1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="GLN"&&a2->getResidue()=="GLN"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="OE1 ")||(a1->getPDBName()=="OE1 "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD  "&&a2->getPDBName()=="NE2 ")||(a1->getPDBName()=="NE2 "&&a2->getPDBName()=="CD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="ASN"&&a2->getResidue()=="ASN"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="OD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="OD1 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="ND2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="ND2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="ILE"&&a2->getResidue()=="ILE"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG1 ")||(a1->getPDBName()=="CG1 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG2 ")||(a1->getPDBName()=="CG2 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CG1 ")||(a1->getPDBName()=="CG1 "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="THR"&&a2->getResidue()=="THR"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="OG1 ")||(a1->getPDBName()=="OG1 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG2 ")||(a1->getPDBName()=="CG2 "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="TRP"&&a2->getResidue()=="TRP"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD1 "&&a2->getPDBName()=="NE1 ")||(a1->getPDBName()=="NE1 "&&a2->getPDBName()=="CD1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CD2 "&&a2->getPDBName()=="CE3 ")||(a1->getPDBName()=="CE3 "&&a2->getPDBName()=="CD2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CE2 "&&a2->getPDBName()=="NE1 ")||(a1->getPDBName()=="NE2 "&&a2->getPDBName()=="CE1 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ2 "&&a2->getPDBName()=="CE2 ")||(a1->getPDBName()=="CE2 "&&a2->getPDBName()=="CZ2 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ3 "&&a2->getPDBName()=="CE3 ")||(a1->getPDBName()=="CE3 "&&a2->getPDBName()=="CZ3 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ2 "&&a2->getPDBName()=="CH2 ")||(a1->getPDBName()=="CH2 "&&a2->getPDBName()=="CZ2 ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CZ3 "&&a2->getPDBName()=="CH2 ")||(a1->getPDBName()=="CH2 "&&a2->getPDBName()=="CZ3 ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(a1->getResidue()=="MET"&&a2->getResidue()=="MET"&&z<6.0){
						if((a1->getPDBName()=="N   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="N   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="C   "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="C   ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="O   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="O   ")){
							this->addConnection(new Connection(2, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CA  ")||(a1->getPDBName()=="CA  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="CB  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="CB  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="SD  "&&a2->getPDBName()=="CG  ")||(a1->getPDBName()=="CG  "&&a2->getPDBName()=="SD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
						else if((a1->getPDBName()=="SD  "&&a2->getPDBName()=="CE  ")||(a1->getPDBName()=="CE  "&&a2->getPDBName()=="SD  ")){
							this->addConnection(new Connection(1, a1, a2));
							this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
						}
					}
					else if(((a1->getPDBName()=="N   "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="N   "))&&a1->getResidue()!=a2->getResidue()&&z<6.0){
						this->addConnection(new Connection(1, a1, a2));
						this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
					}
					if(((a1->getPDBName()=="OXT "&&a2->getPDBName()=="C   ")||(a1->getPDBName()=="C   "&&a2->getPDBName()=="OXT "))&&a1->getResidue()==a2->getResidue()&&z<6.0){
						this->addConnection(new Connection(1, a1, a2));
						this->getConnection(this->getConnections().size()-1)->setScl(glm::vec3(1, 1, (z-2.00)/2.00));
					}
				}
			}
		}
		percent=(float)x/(float)this->getAtoms().size();
		std::cout<<percent*100<<"% complete"<<std::endl;
	}
	float z=abs(sqrt(pow(this->getAtom(1)->getPosition().x-this->getAtom(0)->getPosition().x, 2)+pow(this->getAtom(1)->getPosition().y-this->getAtom(0)->getPosition().y, 2)+pow(this->getAtom(1)->getPosition().z-this->getAtom(0)->getPosition().z, 2)));
}

void Molecule::addAtom(Atom* a){
//	a->setPos(glm::vec3(a->getID()*4-2, 0, 0));
	atoms.emplace_back(std::move(a));
//	std::vector<glm::vec3> vtemp, ntemp;
//	Drawable::loadOBJ("resources/models/atom.obj", vtemp, ntemp);
//	//temp fix for deleted buffers: regen buffers...find alternate permenant fix?
//	atoms.at(atoms.size()-1).setVN(vtemp, ntemp);
//	recomputePositions();
}
void Molecule::removeAtom(Atom *a){
	for(short x=0;x<atoms.size();x++){
		if(atoms.at(x)==a){
			atoms.erase(atoms.begin()-1+x);
		}
	}
}
void Molecule::addConnection(Connection* c){
	connections.emplace_back(std::move(c));
//	std::vector<glm::vec3> vtemp, ntemp;
//	if(connections.at(connections.size()-1).getBonds()==1){Drawable::loadOBJ("resources/models/singlebond.obj", vtemp, ntemp);}
//	else if(connections.at(connections.size()-1).getBonds()==2){Drawable::loadOBJ("resources/models/doublebond.obj", vtemp, ntemp);}
//	else{Drawable::loadOBJ("resources/models/triplebond.obj", vtemp, ntemp);}
//	connections.at(connections.size()-1).setVN(vtemp, ntemp);
//	recomputePositions();
}
void Molecule::removeConnection(Connection *c){
	for(short x=0;x<connections.size();x++){
		if(connections.at(x)==c){
			connections.erase(connections.begin()-1+x);
		}
	}
}

void Molecule::setPos(glm::vec3 p){
	glm::vec3 p0=glm::vec3(0,0,0);
	for(auto&a:atoms){
		p0+=a->getPosition();
	}
	p0/=atoms.size();
	for(auto&a:atoms){
		a->setPos(a->getPosition()-p0+p);
	}
}

void Molecule::printMolecule(){
	std::cout<<"ATOMS:\n______________________________________________\n";
	for(auto& atom:atoms){
		atom->printAtom();
	}
	std::cout<<"CONNECTIONS:\n______________________________________________\n";
	for(auto& connection:connections){
		connection->printConnection();
	}
}

Molecule Molecule::subMol(Atom *a){
	//perhaps unneccesary?
	Molecule m;
	m.addAtom(new Atom(a));
	for(auto& x:a->getConnections()){
		m.addConnection(new Connection(x));
		m.addAtom(new Atom(x->getNot(a)));
	}
	return m;
}

bool Molecule::branch(Atom*s){
	//below if statement possibly more streamlineable?
//	std::cout<<"branch call from "<<s->getID()<<"\n";
	if(s->getName()=="unassigned"){
		for(auto&x:atoms){
			x->repositioned=false;
		}
		Atom*start=s;
		for(int x=2;x<10;x++){
			for(auto&a:atoms){
				if(a->getName()!="unassigned"&&a->getConnections().size()<x){
					start=a;
//					std::cout<<"Branch start identified: "<<start->getID()<<'\n';
					start->recomputePosition();
					start->repositioned=true;
//					start->setClr(glm::vec3(0.9, 0.1, 0.9));
//					std::cout<<"Operation executed on atom "<<start->getID()<<'\n';
					break;
				}
			}
			if(start->getName()!="unassigned"){break;}
		}
		for(auto&x:atoms){
//		std::cout<<x->getPosition().x<<" "<<x->getPosition().y<<" "<<x->getPosition().z<<'\n';
//			std::cout<<x->repositioned<<" ";
		}
		branch(start->getConnections().at(0)->getNot(start));
	}
	else{
//		std::cout<<"Operation executd on atom "<<s->getID()<<'\n';
		if(s->repositioned==false){
			s->recomputePosition();
//			std::cout<<"Operation executd on atom "<<s->getID()<<'\n';
			s->repositioned=true;
		}

		if(s->getConnections().size()==1){
			if(s->getConnections().at(0)->getNot(s)->repositioned==false){
				s->getConnections().at(0)->getNot(s)->recomputePosition();
				s->getConnections().at(0)->getNot(s)->repositioned=true;
//				std::cout<<"Operation executed on atom "<<s->getConnections().at(0)->getNot(s)->getID()<<'\n';
			}
		}
		else{
			for(auto&c:s->getConnections()){
				if(c->getNot(s)->repositioned==false){
					branch(c->getNot(s));
				}
			}
		}
		for(auto&x:atoms){
//		std::cout<<x->getPosition().x<<" "<<x->getPosition().y<<" "<<x->getPosition().z<<'\n';
//			std::cout<<x->repositioned<<" ";
		}
	}
	//bond between atom 5 and atom 6, rotating atom 5



}

bool Molecule::torsionals(float rot){
	float distscore=0;
	for(int x=0;x<atoms.size();x++){
		for(int y=0;y<atoms.size();y++){
			if(x!=y){
//				distscore+=abs(
//						sqrt(pow(atoms.at(x)->getPosition().x, 2)+pow(atoms.at(x)->getPosition().y, 2))+pow(atoms.at(x)->getPosition().z, 2)-
//						sqrt(pow(atoms.at(y)->getPosition().x, 2)+pow(atoms.at(y)->getPosition().y, 2))+pow(atoms.at(y)->getPosition().z, 2)
						distscore+=abs(
						sqrt(pow(atoms.at(x)->getPosition().x-atoms.at(y)->getPosition().x, 2)
						+pow(atoms.at(x)->getPosition().y-atoms.at(y)->getPosition().y, 2)
						+pow(atoms.at(x)->getPosition().z-atoms.at(y)->getPosition().z, 2)));
//				std::cout<<atoms.at(x)->getName()<<"-"<<atoms.at(y)->getName()<<" "<<distscore<<std::endl;
			}
		}
	}
//	std::cout<<distscore<<'\n';

	float theta1, phi1;
	glm::vec3 a1=atoms.at(6)->getPosition(), a2=atoms.at(7)->getPosition();
//	theta1=atan2(a2.x-a1.x, a2.z-a1.z)-4.71;
////	phi1=acos(a2.y-a1.y/4);
//	phi1=atan2(a2.y-a1.y,
//			sqrt(pow(a2.x-a1.x, 2)+pow(a2.z-a1.z, 2)))+1.57;
////	std::cout<<glm::degrees(theta1)<<"   "<<glm::degrees(phi1)<<std::endl;
//	glm::vec3 rotAxis=glm::normalize(glm::vec3(
//			4*cos(theta1)*sin(phi1),
//			4*cos(phi1),
//			4*sin(theta1)*sin(phi1)));
	glm::vec3 rotAxis=glm::normalize(a2-a1);
//	std::cout<<rotAxis.x<<"   "<<rotAxis.y<<"   "<<rotAxis.z<<std::endl;
	for(int x=7;x<atoms.size();x++){
		glm::vec3 a=atoms.at(x)->getPosition();

		glm::vec3 rdir=glm::vec3((a.x+(rotAxis.z/rotAxis.x)*a.z)/(1+(pow(rotAxis.z, 2)/pow(rotAxis.x, 2))), 0, 0);
		rdir.z=(rotAxis.z/rotAxis.x)*rdir.x;
		rdir.y=(rotAxis.y/rotAxis.x)*rdir.x;
		float rmag=sqrt(pow(a.x-rdir.x, 2)+pow(a.y-rdir.y, 2)+pow(a.z-rdir.z, 2));
		float locrot=atan2(rdir.y-a.y, rdir.x-a.x)-3.14;
//		this->getAtom(x)->setPos(rdir);
//		std::cout<<locrot<<std::endl;

//		std::cout<<"("<<rdir.x<<", "<<rdir.y<<", "<<rdir.z<<")"<<std::endl;
		this->getAtom(x)->setPos(glm::vec3(rmag*cos(rot+locrot), rmag*sin(rot+locrot), rdir.z));



		this->getAtom(x)->Drawable::setRot(
				glm::quat(rotAxis.z*sin(-rot/2), rotAxis.y*sin(-rot/2), rotAxis.x*sin(-rot/2),
				          cos(-rot/2)));
	}

	return true;
}

Molecule::~Molecule(){
	for(auto& a:atoms){
		delete a;
	}
	for(auto& c:connections){
		delete c;
	}
}