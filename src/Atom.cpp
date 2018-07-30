#include "Atom.h"
#include "Connection.h"


int Atom::newid=0;

Atom::Atom()
		: anum(0), name("unassigned"), abb("n/a"), electrons(0), velectrons(0), os(0), Drawable("resources/models/atom.obj"){
	std::vector<Connection*> c;
	id=-1;
}
Atom::Atom(short an, short o)
		: anum(an), os(o), Drawable("resources/models/atom.obj"){
	char n[50], a[2];
//	NO SUPPORT FOR VARIED OXIDATION STATE
	int e, ve;
	FILE*file=fopen("resources/AtomicData.txt", "r");
	while(true){
		char lineheader[1024];//128?
		int res=fscanf(file, "%s", lineheader);
		if(res==EOF){break;}
		fscanf(file, "%s %s %d %d", n, a, &e, &ve);
//		std::cout<<"Name: "<<n<<"   Abbreviation: "<<a<<"   Electrons: "<<e<<"   Valence Electrons: "<<ve<<"\n";
		if(e==an){
//			std::cout<<"here";
			electrons=e;
//			std::cout<<electrons;
			name=std::string(n);
			abb=std::string(a);
			velectrons=ve;
			break;
		}
	}
	std::vector<Connection*> c;
//	std::vector<glm::vec3> vtemp, ntemp;
//	loadOBJ("resources/models/atom.obj", vtemp, ntemp);
//	setVN(vtemp, ntemp);
	if(anum==1){setClr(glm::vec3(1,1,1));}
	if(anum==6){setClr(glm::vec3(0.1,0.1,0.1));}
	if(anum==7){setClr(glm::vec3(0.1,0.1,0.9));}
	if(anum==8){setClr(glm::vec3(0.9,0.1,0.1));}
	id=newid;
	newid++;
}

Atom::Atom(Atom *a)
		: anum(a->getANum()), electrons(a->getElectrons()), name(a->getName()), abb(a->getAbbrev()), velectrons(a->getVE()), os(a->getOS()), Drawable("resources/models/atom.obj"){
	std::vector<Connection*> c;
}

void Atom::printAtom(){
	if(os!=0){
		std::cout<<"\tAbbreviation: "<<abb<<"\n\tElectron Count: "<<electrons<<"\n\tValence Electron Count: "<<velectrons<<'\n';
	}
	else{
		std::cout<<anum<<"\nName: "<<name<<"\nAbbreviation: "<<abb<<"\nElectron Count: "<<electrons<<"\nValence Electron Count: "<<velectrons<<'\n';
	}
}

void Atom::setPos(glm::vec3 pos){
	Drawable::setPos(pos);
	for(auto& con:c){
		float x1=con->getAtom1()->getPosition().x, x2=con->getAtom2()->getPosition().x,
				y1=con->getAtom1()->getPosition().y, y2=con->getAtom2()->getPosition().y,
				z1=con->getAtom1()->getPosition().z, z2=con->getAtom2()->getPosition().z;
		con->setPos(glm::vec3((x1+x2)/2,
		                      (y1+y2)/2,
		                      (z1+z2)/2));
		con->setRot(glm::quat(cos(atan((x2-x1)/(z2-z1))/2),
		                      0,
		                      sin(atan((x2-x1)/(z2-z1))/2),
		                      0));
		glm::vec3 rotaxis=glm::normalize(glm::vec3(-(x2-x1), 0, z2-z1));
		//switch rotaxis.z and rotaxis.x?
		con->setRot(glm::quat(cos((acos((y2-y1)/4)+1.57)/2),
		                      rotaxis.z*sin((acos((y2-y1)/4)+1.57)/2),
		                      0,
		                      rotaxis.x*sin((acos((y2-y1)/4)+1.57)/2))*con->getRotation());
//		con->setRot(glm::quat(cos(0.9/2),
//		                      rotaxis.x*sin(0.9/2),
//		                      0,
//		                      rotaxis.z*sin(0.9/2))*con->getRotation());
		std::cout<<glm::normalize(glm::vec3(-(x2-x1),0,z2-z1)).z<<", "<<glm::normalize(-(x2-x1))<<'\n';
		std::cout<<"Connection ("<<con->getAtom1()->getID()<<"-"<<con->getAtom2()->getID()<<") Rotation: ("<<glm::eulerAngles(con->getRotation()).x<<", "<<glm::eulerAngles(con->getRotation()).y<<", "<<glm::eulerAngles(con->getRotation()).z<<")\n";
		std::cout<<"Connection ("<<con->getAtom1()->getID() <<"-"<<con->getAtom2()->getID()<<") Rotation: ("<<con->getRotation().w<<", "<<con->getRotation().x<<", "<<con->getRotation().y<<", "<<con->getRotation().z<<")\n";

	}
}

void Atom::addConnection(Connection *con){
	c.push_back(con);
}