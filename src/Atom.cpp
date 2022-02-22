#include "Atom.h"
#include "Connection.h"


int Atom::newid=0;

Atom::Atom():
	anum(0),
	name("unassigned"),
	abb("n/a"),
	electrons(0),
	velectrons(0),
	os(0),
	repositioned(false),
	polarrot(glm::vec2(0)),
	Drawable(){
	std::vector<Connection*> c;
	id=-1;
}

Atom::Atom(short an,
		   short o,
		   std::vector<glm::vec3>&v,
		   std::vector<glm::vec3>&norm):
		   anum(an),
		   os(o),
		   repositioned(false),
		   polarrot(glm::vec2(0,0)),
		   Drawable(v, norm){
	loadData();
	id=newid;
	newid++;
}

Atom::Atom(std::string sym,
		   glm::vec3 pos,
		   const std::vector<glm::vec3>&v,
		   const std::vector<glm::vec3>&norm):
		   abb(sym),
		   repositioned(false),
		   polarrot(glm::vec2(0,0)),
		   Drawable(v, norm){
	loadData();
	setPos(pos);
	id=newid;
	newid++;
}

Atom::Atom(std::string sym,
		   glm::vec3 pos,
		   std::string n,
		   std::string res,
		   const std::vector<glm::vec3>&v,
		   const std::vector<glm::vec3>&norm):
		   Atom(sym, pos, v, norm){
	pdbname=n;
	residue=res;
}

Atom::Atom(Atom *a):
		   anum(a->getANum()),
		   electrons(a->getElectrons()),
		   name(a->getName()), abb(a->getAbbrev()),
		   velectrons(a->getVE()),
		   os(a->getOS()),
		   polarrot(glm::vec2(0,0)){
	std::vector<glm::vec3> verts=a->Drawable::getVerts(),
						   norms=a->Drawable::getNorms();
	Drawable(verts, norms);
	std::vector<Connection*> c;
}

void Atom::loadData(){
	char n[50], a[2];
	int e, ve;
	FILE*file=fopen("../resources/AtomicData.txt", "r");
	while(true){
		char lineheader[1024];
		int res=fscanf(file, "%s", lineheader);
		if(res==EOF){break;}
		fscanf(file, "%s %s %d %d", n, a, &e, &ve);
		if(a==abb||e==anum){
			electrons=e;
			name=std::string(n);
			abb=std::string(a);
			anum=e;
			velectrons=ve;
			break;
		}
	}
	fclose(file);
	std::vector<Connection*> c;
	switch (anum) {
		case 1:
			setClr(glm::vec3(1, 1, 1));
			break;
		case 2:
		case 10:
		case 18:
		case 54:
			setClr(glm::vec3(0, 1, 1));
			break;
		case 3:
		case 11:
		case 19:
			setClr(glm::vec3(0.5, 0, 1));
			break;
		case 4:
		case 12:
		case 20:
			setClr(glm::vec3(0, 0.5, 0));
			break;
		case 5:
			setClr(glm::vec3(1, 0.6, 0.5));
			break;
		case 6:
			setClr(glm::vec3(0.1, 0.1, 0.1));
			break;
		case 7:
			setClr(glm::vec3(0.1, 0.1, 0.9));
			break;
		case 8:
			setClr(glm::vec3(0.9, 0.1, 0.1));
			break;
		case 9:
		case 17:
			setClr(glm::vec3(0.1, 0.9, 0.1));
			break;
		case 15:
			setClr(glm::vec3(1, 0.6, 0));
			break;
		case 16:
			setClr(glm::vec3(1, 0.9, 0.1));
			break;
		case 35:
			setClr(glm::vec3(0.6, 0.1, 0));
			break;
		default:
			setClr(glm::vec3(0.9, 0.5, 1));
	}
}

void Atom::printAtom(){
	if(os!=0){
		std::cout<<"\tAbbreviation: "<<abb<<
				   "\n\tElectron Count: "<<electrons<<
				   "\n\tValence Electron Count: "<<velectrons<<'\n';
	}
	else{
		std::cout<<anum<<
				   "\nName: "<<name<<
				   "\nAbbreviation: "<<abb<<
				   "\nElectron Count: "<<electrons<<
				   "\nValence Electron Count: "<<velectrons<<'\n';
	}
}

void Atom::setPos(glm::vec3 pos){
	Drawable::setPos(pos);
	for(auto& con:c){
		float x1=con->getAtom1()->getPosition().x, x2=con->getAtom2()->getPosition().x,
				y1=con->getAtom1()->getPosition().y, y2=con->getAtom2()->getPosition().y,
				z1=con->getAtom1()->getPosition().z, z2=con->getAtom2()->getPosition().z;

		float rot;
		glm::vec3 rotaxis;

		rot=-atan2(y2-y1, sqrt(pow(x2-x1, 2)+pow(z2-z1, 2)));
		rotaxis=glm::normalize(glm::vec3(0, 0, 1));
		con->setRot(glm::quat(rotaxis.x*sin(rot/2), rotaxis.y*sin(rot/2), rotaxis.z*sin(rot/2), cos(rot/2)));

		rot=atan2(x2-x1, z2-z1);
		rotaxis=glm::normalize(glm::vec3(0, 1, 0));
		con->setRot(glm::quat(rotaxis.x*sin(rot/2), rotaxis.y*sin(rot/2), rotaxis.z*sin(rot/2), cos(rot/2))*con->getRotation());

		con->setPos(glm::vec3((x1+x2)/2, (y1+y2)/2, (z1+z2)/2));
	}
}

void Atom::setRot(glm::vec2 rot){
	polarrot=rot;
}

void Atom::addConnection(Connection *con){
	c.push_back(con);
}

void Atom::recomputePosition(){
	int bonding=c.size(), lonepairs=velectrons;
	Atom*source=new Atom();
	for(auto& con:c){
		lonepairs-=con->getBonds();
		if(con->getNot(this)->repositioned){
			source=con->getNot(this);
		}
	}
	lonepairs/=2;
	// trying new system out on B2L2 and B2L1
	if(bonding==1){
		if(!c.at(0)->getNot(this)->repositioned){
			float theta=-this->Atom::getRotation().x-4.71, phi=this->Atom::getRotation().y+1.57;
			c.at(0)->getNot(this)->setPos(this->getPosition()+glm::vec3(
					4*cos(theta)*sin(phi),
					4*cos(phi),
					4*sin(theta)*sin(phi)));
			c.at(0)->getNot(this)->setRot((this->getRotation()+glm::vec2(3.14, 0))*glm::vec2(1.0, -1.0));
		}
	}
	else if(bonding==2&&lonepairs==0){
		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
				float theta=-this->Atom::getRotation().x-4.71+(3.14*x), phi=-this->Atom::getRotation().y+1.57;
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						4*cos(theta)*sin(phi),
						4*cos(phi),
						4*sin(theta)*sin(phi)));
				c.at(x)->getNot(this)->setRot(this->getRotation());
			}
		}
	}
	else if(bonding==2&&lonepairs==2){
		int n=0;
		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
				float r=4*cos(glm::radians(104.5*x+180)),
					  phic=this->getRotation().y,
					  z=4*sin(glm::radians(104.5*x+180)),
					  thetac=-this->getRotation().x,
					  theta,
					  radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
//				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac+3.14, phic));
				c.at(x)->getNot(this)->setRot(
						glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
						                              sqrt(pow(c.at(x)->getNot(this)->getPosition().z-
						                                       this->getPosition().z, 2)+
						                                   pow(c.at(x)->getNot(this)->getPosition().x-
						                                       this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==3&&lonepairs==0){
		int n=0;
		int sources=0;
		for(int x=0;x<3;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()&&c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(glm::radians(-60.0+(120.0*n))), phic=this->getRotation().y, z=
						4*sin(glm::radians(-60.0+(120.0*n))), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
//				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac+3.14, phic));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                                 sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
//				std::cout<<abb<<id<<": \n\tPlacing: "<<c.at(x)->getNot(this)->getAbbrev()<<c.at(x)->getNot(this)->getID()<<"\n\tBonds: "<<bonding<<"\n\tLone Pairs: "<<lonepairs<<"\n\tr: "<<r<<"\n\tphic: "<<phic<<"\n\tz: "<<z<<"\n\tthetac: "<<thetac<<"\n\ttheta: "<<theta<<"\n\tradiusxz: "<<radiusxz<<std::endl;
//				c.at(x)->getNot(this)->setRot(glm::vec2(
//						atan2(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, c.at(x)->getNot(this)->getPosition().y-this->getPosition().y),
//						atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y, c.at(x)->getNot(this)->getPosition().x-this->getPosition().x)
//						));
//				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(atan2(c.at(x)->getNot(this)->getPosition().x, c.at(x)->getNot(this)->getPosition().z), atan2(c.at(x)->getNot(this)->getPosition().x, c.at(x)->getNot(this)->getPosition().y)));
//				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(glm::radians(60+(-120.0*n)), phic));
//				std::cout<<60+(-120.0*n)<<", "<<glm::degrees(phic)<<'\n';
//				c.at(x)->getNot(this)->setClr(glm::vec3(0, n, 0));
//				std::cout<<glm::degrees(this->getRotation().x)<<"    "<<glm::degrees(this->getRotation().y)<<'\n';
//				std::cout<<glm::degrees(c.at(x)->getNot(this)->getRotation().x)<<"    "<<glm::degrees(c.at(x)->getNot(this)->getRotation().y)<<'\n';
				n++;
			}
			else{sources++;}
		}
//		if(sources>1){
//			std::cout<<"here";
//			glm::vec3 tempPos;
//			for(auto& b:c){
//				tempPos+=b->getNot(this)->getPosition();
//			}
//			tempPos/=c.size();
//			this->setPos(tempPos);
//		}
	}
	else if(bonding==4&&lonepairs==0){

		for(int x=0;x<4;x++){
//			float theta=this->Atom::getRotation().x-4.71, phi=-(this->Atom::getRotation().y)+1.57;
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
				//
				//Cylindrial around x, modify so entire system rotates around y
				//
				float r=(3.65*sin(x+5.85)+0.35), phic=(4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71), z=
						(-3.26*x+6.52), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin((theta-thetac-3.14)),
						xposv.y,
						radiusxz*cos((theta-thetac-3.14))));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==3&&lonepairs==1){
		for(int x=0;x<3;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()&&c.at(x)->getNot(this)->repositioned==false){
//			if(c.at(x)->getNot(this)->repositioned==false){
				float r=3.65*sin(x+5.85)+0.35, phic=(4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71), z=
						-3.26*x+6.52, thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
//				c.at(x)->getNot(this)->setRot(glm::vec2(atan2(xposv.x, xposv.z), acos(xposv.y/4)+1.57));
//				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac+3.14, phic));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                                 sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
//				std::cout<<abb<<id<<": \n\tPlacing: "<<c.at(x)->getNot(this)->getAbbrev()<<c.at(x)->getNot(this)->getID()<<"\n\tBonds: "<<bonding<<"\n\tLone Pairs: "<<lonepairs<<"\n\tr: "<<r<<"\n\tphic: "<<phic<<"\n\tz: "<<z<<"\n\tthetac: "<<thetac<<"\n\ttheta: "<<theta<<"\n\tradiusxz: "<<radiusxz<<std::endl;
			}
		}
	}
	else if(bonding==2&&lonepairs==1){
		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=3.65*sin(x+5.85)+0.35, phic=(4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71), z=
						-3.26*x+6.52, thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==5&&lonepairs==0){

		for(int x=0;x<3;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(glm::radians(120.0*x)+60.0), phic=this->getRotation().y, z=
						4*sin(glm::radians(120.0*x)+60.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
		for(int x=3;x<5;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+3.14*x+1.57, z=
						4*sin(0.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==4&&lonepairs==1){

		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(glm::radians(0.0)), phic=this->getRotation().y, z=
						4*sin(glm::radians(0.0)), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
		for(int x=2;x<4;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+glm::radians(120.0*x-30.0), z=
						4*sin(0.0), thetac=-this->getRotation().x-1.57, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==3&&lonepairs==2){
		for(int x=0;x<3;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+glm::radians(90.0+180.0*x), z=
						4*sin(0.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==2&&lonepairs==3){

		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+glm::radians(180+180.0*x), z=
						4*sin(0.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==6&&lonepairs==0){
		for(int x=0;x<4;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(1.57*x+3.141), phic=this->getRotation().y, z=
						4*sin(1.57*x+3.14), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
		for(int x=4;x<6;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+3.14*x+1.57, z=
						4*sin(0.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==5&&lonepairs==1){
		for(int x=0;x<4;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(1.57*x+3.141), phic=this->getRotation().y, z=
						4*sin(1.57*x+3.14), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
		for(int x=4;x<5;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(0.0), phic=this->getRotation().y+3.14*x+1.57, z=
						4*sin(0.0), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else if(bonding==4&&lonepairs==2){
		for(int x=0;x<4;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float r=4*cos(1.57*x+3.141), phic=this->getRotation().y, z=
						4*sin(1.57*x+3.14), thetac=-this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
				theta=atan2(xposv.x, xposv.z);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac-3.14),
						xposv.y,
						radiusxz*cos(theta-thetac-3.14)));
				c.at(x)->getNot(this)->setRot(glm::vec2(theta-thetac, atan2(c.at(x)->getNot(this)->getPosition().y-this->getPosition().y,
				                                                            sqrt(pow(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, 2)+pow(c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, 2)))));
			}
		}
	}
	else{this->setPos(glm::vec3(4, 4, 4));}
	this->Drawable::setRot(glm::vec3(this->Atom::getRotation().y, this->Atom::getRotation().x, 0));
}

void Atom::refreshPosition(){this->setPos(this->getPosition());}