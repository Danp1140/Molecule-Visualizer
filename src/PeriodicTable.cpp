#include "PeriodicTable.h"

PeriodicTable::PeriodicTable(){
	std::ifstream adata("resources/AtomicDataNew.xml");
	std::string temp="", anum="", name="", abbrev="", ve="", e="", os="";
	short y=0;
	std::getline(adata,temp);
	std::getline(adata,temp);
	for(short x=0;x<sizeof(elements)/sizeof(*elements);x++){
		std::getline(adata,temp);
		if(temp.at(0)=='\t'){
			y++;
			x--;
			for(short z=1;z<temp.length();z++){
				name=elements[x][0].getName();
				anum=std::to_string(elements[x][0].getANum());
				e=anum;
				if(temp.at(z)=='~'){
					if(abbrev==""){
						abbrev=temp.substr(1,z-1);
					}
					else if(os==""){
						os=temp.substr(abbrev.length()+2,z-abbrev.length()-2);
					}
					else{
						ve=temp.substr(abbrev.length()+e.length()+3,z-abbrev.length()-e.length()-3);
					}
				}
			}
		}
		else{
			y=0;
			os="0";
			for(short z=0;z<temp.length();z++){
				if(temp.at(z)=='~'){
					if(name==""){
						name=temp.substr(0,z);
					}
					else if(abbrev==""){
						abbrev=temp.substr(name.length()+1,z-name.length()-1);
					}
					else if(anum==""){
						anum=temp.substr(name.length()+abbrev.length()+2,z-name.length()-abbrev.length()-2);
						e=anum;
					}
					else{
						ve=temp.substr(name.length()+abbrev.length()+anum.length()+3,z-name.length()-abbrev.length()-anum.length()-3);
					}
				}
			}
		}
		elements[x][y]=Atom(std::stoi(anum),name,abbrev,std::stoi(e),std::stoi(ve),std::stoi(os));
		anum=""; name=""; abbrev=""; ve=""; e="", os="";
	}
}

Atom PeriodicTable::getAtom(short anum, short os){
	for(short x=0;x<sizeof(elements)/sizeof(*elements);x++){
		if(elements[x][0].getANum()==anum){
			for(short y=0;y<sizeof(elements[0])/sizeof(*elements[0]);y++){
				if(elements[x][y].getOS()==os){return elements[x][y];}
			}
		}
	}
	return Atom();
}
void PeriodicTable::printTable(){
	for(short x=0;x<sizeof(elements)/sizeof(*elements);x++){
		elements[x][0].printAtom();
		std::cout<<"Ions:\n";
		if(elements[x][1].getANum()==0){std::cout<<"\tNone\n";}
		for(short y=1;y<sizeof(elements[0])/sizeof(*elements[0]);y++){
			if(elements[x][y].getANum()!=0){elements[x][y].printAtom();}
			else{break;}
		}
	}
}