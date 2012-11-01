#include "Rock.h"

Rock::Rock(){
	
	
}


void Rock::updateThicknesses(const double & thickness1){
    thick = thickness1;
	num =5;
	
	dza[0]=2;
	dza[1]=4;
	dza[2]=8;
	dza[3]=16;
	dza[4]=20;
	
};


void Rock::initializeState( Layer* backl){
	Layer* currl = backl;
	
	int permf =1;
	
	 while(currl!=NULL){
	   	
	   	 if(currl->isRock()){
	   	 	currl->liq =0.;
	   	 	currl->ice=0.;
	   	 	currl->wat =0.;
	   	 	if(permf==0){
	   	 	  currl->tem=1;	
	   	 	 
	   	 	}else if(permf==1){
	   	 	  currl->tem=-1;
	   	 	 
	   	 	}
	   	 }else{
	   	   break;	
	   	 }
	   	  currl = currl->prevl;

	   }

};

void Rock::initializeState5restart( Layer* lstminl, RestartData * resin){
	
	double TSrock[MAX_ROC_LAY];
	for (int i=0; i<MAX_ROC_LAY; i++){
		TSrock[i]=resin->TSrock[i]; //resin->getTSrock(TSrock, ed->cd->reschtid);
	}
	
	Layer* currl = lstminl;
	 
	int rcind =-1;
	while(currl!=NULL){
		if(currl->isRock()){
		  rcind ++;
		
		  currl->tem = TSrock[rcind];
          currl->liq =0;
          currl->ice =0;
          currl->wat =0;
          currl->age =0;
          currl->poro=0;
          
			
		}
		currl = currl->nextl;
	};
	
};

void Rock::setEnvData(EnvData* edp){
	ed = edp;
	
};


