#include "Atom.h"
#include "Connection.h"


int Atom::newid=0;

Atom::Atom()
		: anum(0), name("unassigned"), abb("n/a"), electrons(0), velectrons(0), os(0), repositioned(false), polarrot(glm::vec2(0, 0)), Drawable("resources/models/atom.obj"){
	std::vector<Connection*> c;
	id=-1;
}
Atom::Atom(short an, short o)
		: anum(an), os(o), repositioned(false), polarrot(glm::vec2(0,0)), Drawable("resources/models/atom.obj"){
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
	if(anum==5){setClr(glm::vec3(1.0,0.6,0.5));}
	if(anum==6){setClr(glm::vec3(0.1,0.1,0.1));}
	if(anum==7){setClr(glm::vec3(0.1,0.1,0.9));}
	if(anum==8){setClr(glm::vec3(0.9,0.1,0.1));}
	if(anum==9){setClr(glm::vec3(0.1,0.9,0.1));}
	if(anum==16){setClr(glm::vec3(0.9,0.6,0.3));}
	id=newid;
	newid++;
}

Atom::Atom(Atom *a)
		: anum(a->getANum()), electrons(a->getElectrons()), name(a->getName()), abb(a->getAbbrev()), velectrons(a->getVE()), os(a->getOS()), polarrot(glm::vec2(0,0)), Drawable("resources/models/atom.obj"){
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
		//system DOES NOT WORK if bond is 90˚ upward
		con->setRot(glm::quat(cos((acos((y2-y1)/4)+1.57)/2),
		                      rotaxis.z*sin((acos((y2-y1)/4)+1.57)/2),
		                      0,
		                      rotaxis.x*sin((acos((y2-y1)/4)+1.57)/2))*con->getRotation());
//		con->setRot(glm::quat(cos(0.9/2),
//		                      rotaxis.x*sin(0.9/2),
//		                      0,
//		                      rotaxis.z*sin(0.9/2))*con->getRotation());
//		std::cout<<glm::normalize(glm::vec3(-(x2-x1),0,z2-z1)).z<<", "<<glm::normalize(-(x2-x1))<<'\n';
//		std::cout<<"Connection ("<<con->getAtom1()->getID()<<"-"<<con->getAtom2()->getID()<<") Rotation: ("<<glm::eulerAngles(con->getRotation()).x<<", "<<glm::eulerAngles(con->getRotation()).y<<", "<<glm::eulerAngles(con->getRotation()).z<<")\n";
//		std::cout<<"Connection ("<<con->getAtom1()->getID() <<"-"<<con->getAtom2()->getID()<<") Rotation: ("<<con->getRotation().w<<", "<<con->getRotation().x<<", "<<con->getRotation().y<<", "<<con->getRotation().z<<")\n";

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
		if(con->getNot(this)->repositioned==true){
			source=con->getNot(this);
		}
	}
	lonepairs/=2;
//	std::cout<<"Source: "<<source->getID()<<", "<<source->repositioned;
	//trying new system out on B2L2 and B2L1
	//check why source cant be deleted
	if(bonding==1){
		if(c.at(0)->getNot(this)->repositioned==false){
//			this->setRot(glm::quat(cos(glm::radians(1.0)/2), 0, sin(glm::radians(1.0)/2), 0)*this->getRotation());
			//tidy up atom's polar rotation system
//			this->Atom::setRot(glm::vec2(glm::radians(45.0), glm::radians(45.0)));
			float theta=this->Atom::getRotation().x-4.71, phi=-(this->Atom::getRotation().y)+1.57;
			c.at(0)->getNot(this)->setPos(this->getPosition()+glm::vec3(
					4*cos(theta)*sin(phi),
					4*cos(phi),
					4*sin(theta)*sin(phi)));
			c.at(0)->getNot(this)->setRot(this->getRotation());
//			c.at(0)->getNot(this)->Atom::setRot(c.at(0)->getNot(this)->Atom::getRotation()+glm::vec2(3.14, 0));
//			c.at(0)->getNot(this)->setRot(glm::quat(cos(3.14/2), this->getPosition().x*sin(3.14/2), this->getPosition().y*sin(3.14/2), this->getPosition().z*sin(3.14/2))*this->getRotation());
//			std::cout<<glm::eulerAngles(this->getRotation()).x<<", "<<glm::eulerAngles(this->getRotation()).y<<", "<<glm::eulerAngles(this->getRotation()).z<<'\n';
//			double sinx=2*(this->getRotation().w*this->getRotation().y-this->getRotation().z*this->getRotation().x);
//			std::cout<<asin(sinx)<<", ";
//			double siny=2*(this->getRotation().w*this->getRotation().z+this->getRotation().x*this->getRotation().y),
//					cosy=1-2*(this->getRotation().y*this->getRotation().y+this->getRotation().z*this->getRotation().z);
//			std::cout<<atan(siny/cosy)<<", \n";
		}
	}
	else if(bonding==2&&lonepairs==2){
		//check behaviour if middle atom is the source, and for other options (just make every atom the source and make sure it works)
		//perhaps use isRepositioned instead of sourceID
		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
//				this->Atom::setRot(glm::vec2(glm::radians(x*104.45), 0));
				float theta=glm::radians(104.45*x)+this->Atom::getRotation().x-4.71, phi=-(this->Atom::getRotation().y)+1.57;
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						4*cos(theta)*sin(phi),
						4*cos(phi),
						4*sin(theta)*sin(phi)));
				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(glm::radians(104.45*x), 0));
			}
		}
	}
	else if(bonding==3&&lonepairs==0){
		for(int x=0;x<3;x++){
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
				float theta=glm::radians(120.0*x)+this->Atom::getRotation().x+4.71, phi=-(this->Atom::getRotation().y+1.57);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						4*cos(theta)*sin(phi),
						4*cos(phi),
						4*sin(theta)*sin(phi)));
				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(glm::radians(120.0*x), 0));
			}
		}
	}
	else if(bonding==4&&lonepairs==0){
//		std::cout<<"xpos: "<<c.at(2)->getNot(this)->getPosition().x<<'\n';
		for(int x=0;x<4;x++){
//			float theta=this->Atom::getRotation().x-4.71, phi=-(this->Atom::getRotation().y)+1.57;
			if(c.at(x)->getNot(this)->getID()!=source->getID()){
				//SPHERICAL
//				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
//						3.77*sin(glm::radians(120.0*x)),
//						3.77*cos(glm::radians(120.0*x)),
//						-1.34));
				//no effect when theta=0.0, some effect otherwise
				//xpos stays ±3.26, zpos and ypos change in a circle of radius
//				float theta=this->getRotation().x-4.71, phi=-(this->getRotation().y)+1.57;
//				std::cout<<"theta: "<<glm::degrees(theta)<<" phi: "<<glm::degrees(phi)<<'\n';
//				if(x==2){phi+=this->getRotation().y;}
//				if(x==1||x==3){phi+=this->getRotation().y;}
//				theta=1.57-theta;
//				if(x==2){phi+=this->getRotation().y;}

//				std::cout<<glm::degrees(this->getRotation().y)<<'\n';
//				theta+=glm::radians(20.0*x); phi+=0;
//				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
//						4*cos(theta)*sin(phi),
//						4*cos(phi),
//						4*sin(theta)*sin(phi)));
//				theta=glm::radians(30.0)-4.71; phi=1.57;
//				c.at(x)->getNot(this)->setPos(c.at(x)->getNot(this)->getPosition()+glm::vec3(
//						4*cos(theta)*sin(phi),
//						4*cos(phi),
//						4*sin(theta)*sin(phi)));
				//make tetrahedron as added angles on direction of central atom
//				theta=1.18*x-2.36+3.14; phi=-(3.74*sin(x-0.43)-4.08)+1.57;
//				c.at(x)->getNot(this)->setPos(c.at(x)->getNot(this)->getPosition()+glm::vec3(
//						4*cos(theta)*sin(phi),
//						4*cos(phi),
//						4*sin(theta)*sin(phi)));
//				c.at(x)->getNot(this)->setPos(c.at(x)->getNot(this)->getPosition()+glm::vec3(
//						4*cos(this->getRotation().x)*sin(this->getRotation().y),
//						4*cos(this->getRotation().y),
//						4*sin(this->getRotation().x)*sin(this->getRotation().y)));
//				if(x!=2){c.at(x)->getNot(this)->setPos(c.at(x)->getNot(this)->getPosition()+glm::vec3(0, 2.31*sin(this->getRotation().y-0.96)+1.89, -2.31*sin(this->getRotation().y+0.62)+1.34));}
//				c.at(1)->getNot(this)->setPos(this->getPosition()+glm::vec3(3.26, -0.39, -2.28));
//				c.at(2)->getNot(this)->setPos(this->getPosition()+glm::vec3(0, 3.61, 1.72));
//				c.at(3)->getNot(this)->setPos(this->getPosition()+glm::vec3(-3.26, -0.39, -2.28));
				//
				//Cylindrical around x, Spherical around y, combine angles as spherical
				//
//				float r=3.65*sin(x+5.85)+0.35, phic=4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71, z=-3.26*x+6.52,
//						thetas=1.18*x-2.36+3.14+this->getRotation().x-4.71, phis=3.74*sin(x-0.43)-4.08;
//				glm::vec3 xposc=glm::vec3(r, phic, z), xposs, yposs=glm::vec3(4, thetas, phis),
//						xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y)), yposv=glm::vec3(yposs.x*cos(yposs.y)*sin(yposs.z), yposs.x*cos(yposs.z), yposs.x*sin(yposs.y)*sin(yposs.z));
//
//				xposs.x=4;
//				xposs.y=atan2(xposc.z, (xposc.x*sin(xposc.y)))-4.71;
//				xposs.z=acos((xposc.x*sin(xposc.y))/4);
//
//
//				float finaltheta=atan2(xposv.x, xposv.z)+atan2(yposv.x, yposv.z), finalphi=acos(xposv.y/4)+acos(yposv.y/4);
////				finaltheta=atan2(yposv.x, yposv.z); finalphi=acos(yposv.y/4);
////				finaltheta=atan2(xposv.x, xposv.z); finalphi=acos(xposv.y/4);
//				glm::vec3 finalpos=glm::vec3(4*sin(finaltheta)*sin(finalphi), 4*cos(finalphi), 4*cos(finaltheta)*sin(finalphi));
//				std::cout<<finaltheta<<"   "<<finalphi<<'\n';
//				std::cout<<finalpos.x<<"   "<<finalpos.y<<"   "<<finalpos.z<<'\n';
//
////				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(yposs.x*cos(yposs.y)*sin(yposs.z), yposs.x*cos(yposs.z), yposs.x*sin(yposs.y)*sin(yposs.z)));
////				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y)));
////				std::cout<<"1  x: "<<c.at(x)->getNot(this)->getPosition().x-this->getPosition().x<<" y: "<<c.at(x)->getNot(this)->getPosition().y-this->getPosition().y<<" z: "<<c.at(x)->getNot(this)->getPosition().z-this->getPosition().z<<'\n';
////				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(xposs.x*cos(xposs.y)*sin(xposs.z), xposs.x*cos(xposs.z), xposs.x*sin(xposs.y)*sin(xposs.z)));
////				std::cout<<"2  x: "<<c.at(x)->getNot(this)->getPosition().x-this->getPosition().x<<" y: "<<c.at(x)->getNot(this)->getPosition().y-this->getPosition().y<<" z: "<<c.at(x)->getNot(this)->getPosition().z-this->getPosition().z<<'\n';
//				c.at(x)->getNot(this)->setPos(this->getPosition()+finalpos);
//
//
////				if(x==2){std::cout<<"1  x: "<<cpos.x<<" y: "<<cpos.y<<" z: "<<cpos.z<<'\n';}
////
////				if(x==1){std::cout<<theta<<"   "<<phi<<'\n';}
////
////				if(x==2){std::cout<<"2  x: "<<c.at(x)->getNot(this)->getPosition().x-this->getPosition().x<<" y: "<<c.at(x)->getNot(this)->getPosition().y-this->getPosition().y<<" z: "<<c.at(x)->getNot(this)->getPosition().z-this->getPosition().z<<'\n';}
				//
				//Cylindrical around x, Spherical around y, both with radius of 2, then apply both
				//
//				float r=(3.65*sin(x+5.85)+0.35)/2, phic=4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71, z=(-3.26*x+6.52)/2,
//						thetas=1.18*x-2.36+3.14+this->getRotation().x-4.71, phis=3.74*sin(x-0.43)-4.08;
//				glm::vec3 xposc=glm::vec3(r, phic, z), yposs=glm::vec3(2, thetas, phis);
//				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y)));
//				c.at(x)->getNot(this)->setPos(c.at(x)->getNot(this)->getPosition()+glm::vec3(yposs.x*cos(yposs.y)*sin(yposs.z), yposs.x*cos(yposs.z), yposs.x*sin(yposs.y)*sin(yposs.z)));
				//
				//Cylindrial around x, modify so entire system rotates around y
				//
				float r=3.65*sin(x+5.85)+0.35, phic=4.02*sin(x+2.71)+4.36+this->getRotation().y+4.71, z=
						-3.26*x+6.52, thetac=this->getRotation().x, theta,
						radiusxz;
				glm::vec3 xposc=glm::vec3(r, phic, z);
				glm::vec3 xposv=glm::vec3(xposc.z, xposc.x*sin(xposc.y), xposc.x*cos(xposc.y));
				//				if(x==3){std::cout<<"1   x: "<<xposv.x<<" y: "<<xposv.y<<" z: "<<xposv.z<<'\n';}
				radiusxz=sqrt(16-pow(xposv.y, 2.0));
//				theta=asin(xposv.x/radiusxz);
				theta=atan2(xposv.x, xposv.z);
//				std::cout<<glm::degrees(theta-thetac)<<'\n';
				//				std::cout<<radiusxz<<", "<<c.at(x)->getNot(this)->getPosition().y<<'\n';
				if(x==3){std::cout<<radiusxz<<"   "<<theta<<'\n';}
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						radiusxz*sin(theta-thetac),
						xposv.y,
						radiusxz*cos(theta-thetac)));
				//ISSUE IS WITH Z
//				if(x==3){std::cout<<"2   x: "<<c.at(x)->getNot(this)->getPosition().x-this->getPosition().x<<" y: "<<c.at(x)->getNot(this)->getPosition().y-this->getPosition().y<<" z: "<<c.at(x)->getNot(this)->getPosition().z-this->getPosition().z<<'\n';}
//				if(x==2){std::cout<<"theta: "<<thetac<<" | x: "<<radiusxz*sin(thetac)<<" | z: "<<-(sin(thetac)*(c.at(x)->getNot(this)->getPosition().z-this->getPosition().z))<<'\n';}
//				if(x==2){std::cout<<r-r*cos(thetac)<<'\n';}
				//google it (rotating around common origin)
//				if(x==2){std::cout<<"x: "a<<c.at(x)->getNot(this)->getPosition().x-this->getPosition().x<<" y: "<<c.at(x)->getNot(this)->getPosition().y-this->getPosition().y<<" z: "<<c.at(x)->getNot(this)->getPosition().z-this->getPosition().z<<'\n';}
			}
		}
	}
	else if(bonding==3&&lonepairs==1){
		//perhaps change source to repositioned==true
		for(int x=0;x<3;x++){
//			if(c.at(x)->getNot(this)->getID()!=source->getID()){
			if(c.at(x)->getNot(this)->repositioned==false){
//				this->Atom::setRot(glm::vec2(glm::radians(x*120.0), glm::radians(338.43)));
//				float phi=-(this->Atom::getRotation().y)+1.57, theta=this->Atom::getRotation().x+4.71;
//				this->Atom::setRot(this->Atom::getRotation()+glm::vec2(0, glm::radians(21.57)));
//				this->Atom::setRot(this->Atom::getRotation()+glm::vec2(0, glm::radians(1.0)));
				float theta=glm::radians(120.0*x)-4.71, phi=-glm::radians(-55.3886878)+1.57;
//				float theta=glm::radians(120.0*x)-4.71, phi=-glm::radians(-34.58)+1.57;
				//-34.6113122,
				//-55.3886878

				//34.58, 124.58, 214.58, 304.58
				//55.42, 145.42, 235.42, 325.42
				//39.44, 129.44, 219.44, 309.44
				//50.56, 140.56, 230.56, 320.56
				//124.58, so close! (7 deg. off)
				//39.44, so close! (5 deg. off)
//				c.at(x)->getNot(this)->setClr(glm::vec3(0.5, 0.5*x, 0.5));
//				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
//						4*cos(theta)*sin(phi),
//				        4*cos(phi),
//				        4*sin(theta)*sin(phi)));
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						3.72*sin(glm::radians(120.0*x)),
						-1.47,
						3.72*cos(glm::radians(120.0*x))));
				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(glm::radians(120.0*x), 0));
//				float x1=c.at(x)->getNot(this)->getPosition().x-this->getPosition().x, x2=source->getPosition().x-this->getPosition().x,
//						y1=c.at(x)->getNot(this)->getPosition().y-this->getPosition().y, y2=source->getPosition().y-this->getPosition().y,
//						z1=c.at(x)->getNot(this)->getPosition().z-this->getPosition().z, z2=source->getPosition().z-this->getPosition().z;
//				std::cout/*<<"x1: "<<x1<<" x2: "<<x2<<" z1: "<<z1<<" z2: "<<z2<<"   "*/<<glm::degrees(acos(((x1*x2)+(y1*y2)+(z1*z2))/16))<<'\n';
//				std::cout<<glm::degrees(glm::angle(source->getPosition()+this->getPosition(), c.at(0)->getNot(this)->getPosition()+this->getPosition()))<<'\n';
			}
		}
	}
	else if(bonding==2&&lonepairs==1){
		for(int x=0;x<2;x++){
			if(c.at(x)->getNot(this)->repositioned==false){
				float theta=glm::radians(x*120.0)+this->Atom::getRotation().x+4.71, phi=-(this->getRotation().y+1.57);
				c.at(x)->getNot(this)->setPos(this->getPosition()+glm::vec3(
						4*cos(theta)*sin(phi),
						4*cos(phi),
						4*sin(theta)*sin(phi)));
				c.at(x)->getNot(this)->setRot(this->getRotation()+glm::vec2(glm::radians(120.0*x), 0));
			}
		}
	}
	else{this->setPos(glm::vec3(4, 0, 0));}
//	std::cout<<"B: "<<bonding<<" LP: "<<lonepairs<<"\n";
//	delete source;                     
}