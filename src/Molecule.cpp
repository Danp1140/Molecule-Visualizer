#include "Molecule.h"

Molecule::Molecule(){
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
}

Molecule::Molecule(const char* pdbfilepath){
	std::cout<<"Loading PDB"<<std::endl;
	float percent=0.0;
	std::vector<Atom*> atoms;
	std::vector<Connection*> connections;
	std::vector<glm::vec3> verts, norms;
	Drawable::loadOBJ("../resources/models/atomsmooth.obj", verts, norms);
	char temp[128];
	FILE*file=fopen(pdbfilepath, "r");
	while(true){
		if(fgets(temp, sizeof(temp), file)==nullptr){break;}
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
		std::cout<<'\r'<<percent*100<<"% complete";
	}
	std::cout<<std::endl;
	float z=abs(sqrt(pow(this->getAtom(1)->getPosition().x-this->getAtom(0)->getPosition().x, 2)+pow(this->getAtom(1)->getPosition().y-this->getAtom(0)->getPosition().y, 2)+pow(this->getAtom(1)->getPosition().z-this->getAtom(0)->getPosition().z, 2)));
	fclose(file);
}

void Molecule::addAtom(Atom* a){
	atoms.emplace_back(a);
}

void Molecule::removeAtom(Atom *a){
	for(short x=0;x<atoms.size();x++){
		if(atoms.at(x)==a){
			atoms.erase(atoms.begin()-1+x);
		}
	}
}

void Molecule::addConnection(Connection* c){
	connections.emplace_back(c);
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

bool Molecule::branch(Atom*s){
	// starting case, null-initialized Atom has name initialized to "unassigned"
	if(s->getName()=="unassigned"){
		for(auto&x:atoms){
			x->repositioned=false;
		}
		// determines starting atom by finding any atom with minimal bonds
		Atom*start=s;
		for(int x=2;x<10;x++){
			for(auto&a:atoms){
				if(a->getName()!="unassigned"&&a->getConnections().size()<x){
					start=a;
					start->recomputePosition();
					start->repositioned=true;
					break;
				}
			}
			if(start->getName()!="unassigned"){break;}
		}
		branch(start->getConnections().at(0)->getNot(start));
	}
	else{
		if(!s->repositioned){
			s->recomputePosition();
			s->repositioned=true;
		}
		// indicates the end of the branch
		// never actually get inside second if layer tho
		// kinda makes sense
//		if(s->getConnections().size()==1){
//			if(!s->getConnections().at(0)->getNot(s)->repositioned){
//				s->getConnections().at(0)->getNot(s)->recomputePosition();
//				s->getConnections().at(0)->getNot(s)->repositioned=true;
//				s->getConnections()[0]->getNot(s)->setClr(glm::vec3(1., 0, 1.));
//			}
//		}
//		else{
			for(auto&c:s->getConnections()){
				if(!c->getNot(s)->repositioned){
					branch(c->getNot(s));
				}
			}
//		}
	}
}

bool Molecule::torsionals(Atom*a1, Atom*a2){
	glm::vec3 sub=a1->getPosition();
	for(auto&a:atoms){a->setPos(glm::vec3(a->getPosition().x-sub.x, a->getPosition().y-sub.y, a->getPosition().z-sub.z));}

	float r, phi, theta;
	r=sqrt(pow(a2->getPosition().x, 2)+pow(a2->getPosition().y, 2)+pow(a2->getPosition().z, 2));
	theta=atan2(a2->getPosition().x, a2->getPosition().z);
//	phi=acos(a2->getPosition().y/r);

//	phi=atan2(a2->getPosition().x, a2->getPosition().y);

	for(auto&a:atoms){
		if(a!=a1){
			float rtemp=sqrt(pow(a->getPosition().x, 2)+(pow(a->getPosition().y, 2)+pow(a->getPosition().z, 2)));
			float thetatemp=atan2(a->getPosition().x, a->getPosition().z);
			float phitemp=acos(a->getPosition().y/rtemp);
			thetatemp+=1.57-theta;
			a->setPos(glm::vec3(
					rtemp*sin(thetatemp)*sin(phitemp),
					rtemp*cos(phitemp),
					rtemp*cos(thetatemp)*sin(phitemp)
			));
		}
	}
	phi=atan2(a2->getPosition().x, a2->getPosition().y);
	for(auto&a:atoms){
		if(a!=a1){
			float rtemp=sqrt(pow(a->getPosition().x, 2)+(pow(a->getPosition().y, 2)+pow(a->getPosition().z, 2)));
			float phitemp2=atan2(a->getPosition().x, a->getPosition().y);
			float thetatemp2=asin(a->getPosition().z/rtemp);
			phitemp2-=phi-1.57;
			a->setPos(glm::vec3(
					rtemp*cos(thetatemp2)*sin(phitemp2),
					rtemp*cos(thetatemp2)*cos(phitemp2),
					rtemp*sin(thetatemp2)
					));
		}
	}

	std::vector<Atom*> subatom;

	subatom=torsionalBranching(a1, a2);

//	for(auto&a:subatom){std::cout<<a->getID();}

	//start
//	float distscore=0.0, distscoremin, minangle=0.0;
//	for(auto&a:atoms){
//		for(auto&at:atoms){
//			if(a!=at){
//				distscoremin+=sqrt(pow(a->getPosition().x-at->getPosition().x, 2)+pow(a->getPosition().y-at->getPosition().y, 2)+pow(a->getPosition().z-at->getPosition().z, 2));
//			}
//		}
//	}
//	std::vector<float> originalThetas;
//	for(auto&a:subatom){originalThetas.push_back(atan2(a->getPosition().y, a->getPosition().z));}
//	float addition=0.00;
//	for(int x=0;x<628;x++){
//		addition+=0.01;
//		for(auto&a:subatom){
//			if(a!=a1){
//				r=sqrt(pow(a->getPosition().y, 2)+pow(a->getPosition().z, 2));
//				theta=atan2(a->getPosition().y, a->getPosition().z)+addition;
//				std::cout<<theta<<std::endl;
////				theta+=temp;
////				theta+=0.01;
//				a->setPos(glm::vec3(
//						a->getPosition().x,
//						r*sin(theta),
//						r*cos(theta)
//				));
//			}
//		}
//		for(auto&a:atoms){
//			for(auto&at:atoms){
//				if(a!=at){
//					distscore+=sqrt(pow(a->getPosition().x-at->getPosition().x, 2)+pow(a->getPosition().y-at->getPosition().y, 2)+pow(a->getPosition().z-at->getPosition().z, 2));
//				}
//			}
//		}
//		if(distscore<distscoremin){
//			distscoremin=distscore;
//			minangle=theta;
//		}
//	}
	//end
	float distance=0.0, maxDistance=0.0, maxAngle=0.0;
	std::vector<float> originalThetas;
	for(auto&a:subatom){
		originalThetas.push_back(atan2(a->getPosition().y, a->getPosition().z));
	}
	for(float x=0;x<6.28;x+=0.01){
		distance=0.0;
		for(auto&a:subatom){
			if(a!=a1){
				r=sqrt(pow(a->getPosition().y, 2)+pow(a->getPosition().z, 2));
				theta=atan2(a->getPosition().y, a->getPosition().z)+x;
				a->setPos(glm::vec3(
						a->getPosition().x,
						r*sin(theta),
						r*cos(theta)
				));
			}
		}
		for(auto&a:atoms){
			for(auto&at:atoms){
				distance+=sqrt(pow(a->getPosition().x-at->getPosition().x, 2)+pow(a->getPosition().y-at->getPosition().y, 2)+pow(a->getPosition().z-at->getPosition().z, 2));
			}
		}
		if(distance>maxDistance){
			maxDistance=distance;
			maxAngle=x;
		}
	}

	//below repositioning is creating issues
	int counter=0;
	for(auto&a:subatom){
		r=sqrt(pow(a->getPosition().y, 2)+pow(a->getPosition().z, 2));
		theta=originalThetas[counter]+maxAngle;
//		theta=atan2(a->getPosition().y, a->getPosition().z)+maxAngle;
//		std::cout<<r<<", "<<theta<<std::endl;
		a->setPos(glm::vec3(
				a->getPosition().x,
				r*sin(theta),
				r*cos(theta)
		));
		counter++;
	}


	return true;
}

std::vector<Atom*> Molecule::torsionalBranching(Atom*a1, Atom*a2){
	std::vector<Atom*> result, subresult;
	result.push_back(a2);
	if(a2->getConnections().size()<2){return result;}
	else{
		for(auto&c:a2->getConnections()){
			if(c->getNot(a2)!=a1){
				subresult=torsionalBranching(a2, c->getNot(a2));
				for(auto&a:subresult) result.push_back(a);
			}
		}
	}
	return result;
}

Molecule::~Molecule(){
	for(auto& a:atoms){
		delete a;
	}
	for(auto& c:connections){
		delete c;
	}
}